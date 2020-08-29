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

#ifndef INCLUDED_LAB_RADAR_CORR_DIST_ESTIMATOR_BFI_IMPL_H
#define INCLUDED_LAB_RADAR_CORR_DIST_ESTIMATOR_BFI_IMPL_H

#include <lab_radar/corr_dist_estimator_bfi.h>
#include <fstream>



namespace gr {
  namespace lab_radar {

    class corr_dist_estimator_bfi_impl : public corr_dist_estimator_bfi
    {
     private:
      int code_length;
      std::ofstream output_stream;

      void n_shifts_array (uint8_t * arr, int length, int n, int & start_byte);
      uint8_t get_mask (int bit_shifts );

      float correlation (uint8_t * arr1, uint8_t * arr2, int length);
      std::tuple<float,int> find_max_peak(uint8_t * arr1, uint8_t * arr2, int length, int prediction);
     public:
      corr_dist_estimator_bfi_impl(int code_length);
      ~corr_dist_estimator_bfi_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace lab_radar
} // namespace gr

#endif /* INCLUDED_LAB_RADAR_CORR_DIST_ESTIMATOR_BFI_IMPL_H */

