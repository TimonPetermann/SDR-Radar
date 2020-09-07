/* -*- c++ -*- */
/*
 * Copyright 2020 Dominik Pearson.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "signal_corr_estimator_cf_impl.h"
#include <vector>
#include <numeric>

namespace gr
{
  namespace lab_radar
  {

    signal_corr_estimator_cf::sptr
    signal_corr_estimator_cf::make(int sample_rate_rx, int sample_fac, int code_length, int sps_rx, int avg_length, int skip_data, float v_max)
    {
      return gnuradio::get_initial_sptr(new signal_corr_estimator_cf_impl(sample_rate_rx, sample_fac, code_length, sps_rx, avg_length, skip_data, v_max));
    }

    /*
     * The private constructor
     */
    signal_corr_estimator_cf_impl::signal_corr_estimator_cf_impl(int sample_rate_rx, int sample_fac, int code_length, int sps_rx, int avg_length, int skip_data, float v_max)
        : gr::block("signal_corr_estimator_cf",
                    gr::io_signature::make(2, 2, sizeof(gr_complex)),
                    gr::io_signature::make(1, 3, sizeof(float))),
          avg_length(avg_length), skip_data(skip_data)
    {
      nelements_rx = sps_rx * code_length;
      nelements_tx = sps_rx * code_length * sample_fac;
      factor = sample_fac;
      dist_factor = 299792458. / ((float)(sample_rate_rx * factor * 2));
      corr_results = std::vector<float>(avg_length);
      offsets = std::vector<float>(avg_length);
      sum_corr = 0;
      sum_offset = 0;
      locked = false;
      int indices = std::ceil(((float)nelements_tx / (float)(sample_rate_rx * factor)) / dist_factor);
      ncheckindices = std::max(2, indices);
      i_corr_results = 0;
    }

    /*
     * Our virtual destructor.
     */
    signal_corr_estimator_cf_impl::~signal_corr_estimator_cf_impl()
    {
    }

    void signal_corr_estimator_cf_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items * nelements_rx * skip_data;
      ninput_items_required[1] = noutput_items * nelements_tx * skip_data;
    }

    void signal_corr_estimator_cf_impl::findCorrelationPeak(std::tuple<float, float> &result, gr_complex *arr1, gr_complex *arr2)
    {
      float &peak = std::get<0>(result);
      float &offset = std::get<1>(result);
      gr_complex corr_integrator(0, 0);
      float abs_corr = 0;
      if (locked)
      {
        int curoffset = std::round(sum_offset / (float)avg_length);

        for (int i = -ncheckindices; i <= ncheckindices; i++)
        {
          corr_integrator = 0;
          for (int j = 0; j < nelements_rx; j++)
          {
            corr_integrator += std::conj(arr1[j]) * arr2[(-curoffset - i + j * factor) % nelements_tx];
          }
          abs_corr = std::abs(corr_integrator);
          if (abs_corr > peak)
          {
            peak = abs_corr;
            offset = curoffset + i;
          }
        }
      }
      else
      {
        for (int i = 0; i < nelements_tx; i++)
        {
          corr_integrator = 0;
          for (int j = 0; j < nelements_rx; j++)
          {
            corr_integrator += std::conj(arr1[j]) * arr2[(-i + j * factor) % nelements_tx];
          }
          abs_corr = std::abs(corr_integrator);
          if (abs_corr > peak)
          {
            peak = abs_corr;
            offset = i;
          }
        }
      }
      sum_corr -= corr_results[i_corr_results];
      sum_offset -= offsets[i_corr_results];
      corr_results[i_corr_results] = peak;
      offsets[i_corr_results] = offset;
      sum_corr += peak;
      sum_offset += offset;
      i_corr_results = (i_corr_results + 1) % avg_length;
      if (abs(sum_corr - peak * avg_length) / sum_corr < 0.1)
      {
        locked = true;
      }
      else
      {
        locked = false;
      }
      offset = sum_offset / (float)avg_length;
      peak = sum_corr / (float)avg_length;
    }

    int signal_corr_estimator_cf_impl::general_work(int noutput_items,
                                                    gr_vector_int &ninput_items,
                                                    gr_vector_const_void_star &input_items,
                                                    gr_vector_void_star &output_items)
    {
      gr_complex *rx = (gr_complex *)input_items[0];
      gr_complex *tx = (gr_complex *)input_items[1];
      float *dist = (float *)output_items[0];
      float *peak = (float *)output_items[1];
      float *offset = (float *)output_items[2];

      int num_rx = ninput_items[0];
      int num_tx = ninput_items[1];

//      noutput_items = std::min(noutput_items, std::min(num_rx / nelements_rx, num_tx / nelements_tx));
      //signal processing (complex correlation)
      std::tuple<float, float> corr_res = std::make_tuple<float, float>(0.0, 0.0);
      int outindex = 0;
      for (int i = 0; i < noutput_items*skip_data; i++)
      {
        if (i % skip_data == 0)
        {
          findCorrelationPeak(corr_res, rx + i * nelements_rx, tx + i * nelements_tx);
          peak[outindex] = std::get<0>(corr_res);
          offset[outindex] = std::get<1>(corr_res);
          dist[outindex] = offset[outindex] * dist_factor;
          outindex++;
        }
      }
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume(0, noutput_items * nelements_rx * skip_data);
      consume(1, noutput_items * nelements_tx * skip_data);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace lab_radar */
} /* namespace gr */