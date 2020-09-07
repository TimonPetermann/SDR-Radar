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
#include "simple_decimator_cc_impl.h"

namespace gr
{
  namespace lab_radar
  {

    simple_decimator_cc::sptr
    simple_decimator_cc::make(int decimation)
    {
      return gnuradio::get_initial_sptr(new simple_decimator_cc_impl(decimation));
    }

    /*
     * The private constructor
     */
    simple_decimator_cc_impl::simple_decimator_cc_impl(int decimation)
        : gr::sync_decimator("simple_decimator_cc",
                             gr::io_signature::make(1, 1, sizeof(gr_complex)),
                             gr::io_signature::make(1, 1, sizeof(gr_complex)), decimation),
          decimation(decimation)
    {
    }

    /*
     * Our virtual destructor.
     */
    simple_decimator_cc_impl::~simple_decimator_cc_impl()
    {
    }

    int
    simple_decimator_cc_impl::work(int noutput_items,
                                   gr_vector_const_void_star &input_items,
                                   gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *)input_items[0];
      gr_complex *out = (gr_complex *)output_items[0];

      // Do <+signal processing+>
      for (int i = 0; i < noutput_items; i++)
      {
        out[i] = in[i * decimation];
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace lab_radar */
} /* namespace gr */
