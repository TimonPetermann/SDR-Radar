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

#ifndef INCLUDED_LAB_RADAR_CORR_DIST_ESTIMATOR_BFI_H
#define INCLUDED_LAB_RADAR_CORR_DIST_ESTIMATOR_BFI_H

#include <lab_radar/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace lab_radar {

    /*!
     * \brief <+description of block+>
     * \ingroup lab_radar
     *
     */
    class LAB_RADAR_API corr_dist_estimator_bfi : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<corr_dist_estimator_bfi> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of lab_radar::corr_dist_estimator_bfi.
       *
       * To avoid accidental use of raw pointers, lab_radar::corr_dist_estimator_bfi's
       * constructor is in a private implementation
       * class. lab_radar::corr_dist_estimator_bfi::make is the public interface for
       * creating new instances.
       */
      static sptr make(int code_length);
    };

  } // namespace lab_radar
} // namespace gr

#endif /* INCLUDED_LAB_RADAR_CORR_DIST_ESTIMATOR_BFI_H */

