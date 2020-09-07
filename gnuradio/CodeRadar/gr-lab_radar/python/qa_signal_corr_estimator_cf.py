#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 Dominik Pearson.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
from gnuradio import digital
from gnuradio import filter
import lab_radar_swig as lab_radar


class qa_signal_corr_estimator_cf(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        # set up variables
        sps = 2
        samp_rate_rx = 4000000
        divider = 50
        delay = 6
        v_max = 10
        bpsk = digital.constellation_bpsk().base()

        # generate blocks
        lab_radar_simple_decimator = lab_radar.simple_decimator_cc(decimation = divider)
        lab_radar_signal_corr_estimator_cf_0 = lab_radar.signal_corr_estimator_cf(
            samp_rate_rx, divider, 8, sps, v_max)
        digital_constellation_modulator_0 = digital.generic_mod(
            constellation=bpsk, differential=False, samples_per_symbol=sps*divider, pre_diff_code=True, excess_bw=0.35, verbose=False, log=False)
        blocks_vector_source_x_0 = blocks.vector_source_b(
            (154, 154, 154, 154, 154, 154, 154, 154,154,154,154,154,154,154,154,154), False, 1, [])
        offsets = blocks.vector_sink_f(1, 1024)
        peaks = blocks.vector_sink_f(1, 1024)
        distances = blocks.vector_sink_f(1, 1024)
        blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate_rx/sps/8, True)
        blocks_delay_0 = blocks.delay(gr.sizeof_gr_complex*1, delay)

        # setup connections
        self.tb.connect((blocks_delay_0, 0), (lab_radar_simple_decimator, 0))
        self.tb.connect((blocks_throttle_0, 0), (digital_constellation_modulator_0, 0))
        self.tb.connect((blocks_vector_source_x_0, 0), (blocks_throttle_0, 0))
        self.tb.connect((digital_constellation_modulator_0, 0), (blocks_delay_0, 0))
        self.tb.connect((digital_constellation_modulator_0, 0), (lab_radar_signal_corr_estimator_cf_0, 1))
        self.tb.connect((lab_radar_signal_corr_estimator_cf_0, 0), (distances, 0))
        self.tb.connect((lab_radar_signal_corr_estimator_cf_0, 1), (peaks, 0))
        self.tb.connect((lab_radar_signal_corr_estimator_cf_0, 2), (offsets, 0))
        self.tb.connect((lab_radar_simple_decimator, 0), (lab_radar_signal_corr_estimator_cf_0, 0))
        # set up fg
        self.tb.run()

        print(distances.data())
        print(offsets.data())
        print(peaks.data())
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_signal_corr_estimator_cf)
