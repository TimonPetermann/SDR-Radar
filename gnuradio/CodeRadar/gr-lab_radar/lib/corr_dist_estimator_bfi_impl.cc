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
#include "corr_dist_estimator_bfi_impl.h"
#include <iostream>
#include <vector>
#include <tuple>

namespace gr
{
  namespace lab_radar
  {
    const uint8_t u1 = 1;
    const uint8_t u2 = 2;
    const uint8_t u4 = 4;
    const uint8_t u8 = 8;
    const uint8_t u16 = 16;
    const uint8_t u32 = 32;
    const uint8_t u64 = 64;
    const uint8_t u128 = 128;

    corr_dist_estimator_bfi::sptr
    corr_dist_estimator_bfi::make(int code_length)
    {
      return gnuradio::get_initial_sptr(new corr_dist_estimator_bfi_impl(code_length));
    }

    /*
     * The private constructor
     */
    corr_dist_estimator_bfi_impl::corr_dist_estimator_bfi_impl(int code_length)
        : gr::sync_decimator("corr_dist_estimator_bfi",
                             gr::io_signature::make(2, 2, sizeof(char)),
                             gr::io_signature::make(1, 3, sizeof(float)), code_length),
          output_stream(std::string("../debug.txt")),
          code_length(code_length)
    {
    }

    /*
     * Our virtual destructor.
     */
    corr_dist_estimator_bfi_impl::~corr_dist_estimator_bfi_impl()
    {
    }

    void corr_dist_estimator_bfi_impl::n_shifts_array(uint8_t *arr, int length, int n, int &start_byte)
    {
      start_byte += n / 8;
      uint8_t bit_shifts = n % 8;
      uint8_t shift_overflow = 0;
      auto mask = get_mask(bit_shifts);
      for (int i = start_byte; i < start_byte + length; ++i)
      {
        uint8_t shift_overflow_temp = arr[i % length] & mask;
        arr[i % length] = (arr[i % length] >> bit_shifts);
        arr[(i) % length] = shift_overflow | arr[(i) % length];
        shift_overflow = shift_overflow_temp << (8 - bit_shifts);
      }
      arr[(start_byte) % length] = shift_overflow | arr[(start_byte) % length];
    }

    uint8_t corr_dist_estimator_bfi_impl::get_mask(int bit_shifts)
    {
      uint8_t mask = 0;
      switch (bit_shifts)
      {
      case 1:
        mask = 1;
        break;
      case 2:
        mask = 3;
        break;
      case 3:
        mask = 7;
        break;
      case 4:
        mask = 15;
        break;
      case 5:
        mask = 31;
        break;
      case 6:
        mask = 63;
        break;
      case 7:
        mask = 127;
        break;
      }
      return mask;
    }

    float corr_dist_estimator_bfi_impl::correlation(uint8_t *arr1, uint8_t *arr2, int length)
    {
      float cor_res = 0;
      for (int i = 0; i < length; ++i)
      {
        uint8_t val = (arr1[i] ^ arr2[i]);
        cor_res += 8 - 2 * ((u1 & val) + ((u2 & val) >> 1) + ((u4 & val) >> 2) + ((u8 & val) >> 3) + ((u16 & val) >> 4) + ((u32 & val) >> 5) + ((u64 & val) >> 6) + ((u128 & val) >> 7));
      }
      return cor_res / (8 * length);
    }

    std::tuple<float, int> corr_dist_estimator_bfi_impl::find_max_peak(uint8_t *arr1, uint8_t *arr2, int length, int prediction)
    {
      auto max_peak = std::make_tuple<float, int>(0.0, 0);
      auto &max_corr = std::get<0>(max_peak);
      auto &max_pos = std::get<1>(max_peak);
      for (int i = 0; i < length * 8; ++i)
      {
        int start_byte = 0;
        float curr_corr = correlation(arr1, arr2, length);
        if (curr_corr > max_corr)
        {
          max_corr = curr_corr;
          max_pos = i;
          if (max_corr > 0.75)
            break;
        }
        n_shifts_array(arr1, length, 1, start_byte);
      }
      return max_peak;
    }

    int
    corr_dist_estimator_bfi_impl::work(int noutput_items,
                                       gr_vector_const_void_star &input_items,
                                       gr_vector_void_star &output_items)
    {
      uint8_t *source = (uint8_t *)input_items[0];
      uint8_t *received = (uint8_t *)input_items[1];
      float *distance = (float *)output_items[0];
      float *peak = (float *)output_items[1];
      float *offset = (float *)output_items[2];

      // iterate over n output items
      // max peak detection
      // correlation
      // from peak to distance
      for (int i = 0; i < noutput_items; i++)
      {
        int startbyte = 0;
        auto result = find_max_peak(source+i*code_length, received+i*code_length, code_length, 0);
        distance[i]=0;
        peak[i]=std::get<0>(result);
        offset[i]=std::get<1>(result);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace lab_radar */
} /* namespace gr */
