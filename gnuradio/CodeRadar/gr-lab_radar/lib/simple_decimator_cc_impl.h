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

#ifndef INCLUDED_LAB_RADAR_SIMPLE_DECIMATOR_CC_IMPL_H
#define INCLUDED_LAB_RADAR_SIMPLE_DECIMATOR_CC_IMPL_H

#include <lab_radar/simple_decimator_cc.h>

namespace gr {
  namespace lab_radar {

    class simple_decimator_cc_impl : public simple_decimator_cc
    {
     private:
      int decimation;

     public:
      simple_decimator_cc_impl(int decimation);
      ~simple_decimator_cc_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace lab_radar
} // namespace gr

#endif /* INCLUDED_LAB_RADAR_SIMPLE_DECIMATOR_CC_IMPL_H */

