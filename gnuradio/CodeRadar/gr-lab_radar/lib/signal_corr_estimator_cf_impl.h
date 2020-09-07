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

#ifndef INCLUDED_LAB_RADAR_SIGNAL_CORR_ESTIMATOR_CF_IMPL_H
#define INCLUDED_LAB_RADAR_SIGNAL_CORR_ESTIMATOR_CF_IMPL_H

#include <lab_radar/signal_corr_estimator_cf.h>
#include <vector>

namespace gr
{
  namespace lab_radar
  {

    class signal_corr_estimator_cf_impl : public signal_corr_estimator_cf
    {
    private:
      int nelements_rx;
      int nelements_tx;
      int skip_data;
      float dist_factor;
      int factor;
      int ncheckindices;
      bool locked;
      float sum_corr;
      float sum_offset;
      std::vector<float> corr_results;
      std::vector<float> offsets;
      int avg_length;
      int i_corr_results;

      void findCorrelationPeak(std::tuple<float,float> &result, gr_complex *arr1,gr_complex *arr2);

    public:
      signal_corr_estimator_cf_impl(int sample_rate_rx, int sample_fac, int code_length, int sps_rx, int avg_length, int skip_data, float v_max);
      ~signal_corr_estimator_cf_impl();

      // Where all the action really happens
      void forecast(int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
    };

  } // namespace lab_radar
} // namespace gr

#endif /* INCLUDED_LAB_RADAR_SIGNAL_CORR_ESTIMATOR_CF_IMPL_H */
