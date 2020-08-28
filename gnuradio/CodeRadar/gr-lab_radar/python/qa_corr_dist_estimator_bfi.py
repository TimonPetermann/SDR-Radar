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
import lab_radar_swig as lab_radar
import numpy as np

class qa_corr_dist_estimator_bfi(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):

        test_data = np.arange(0,6,dtype=np.uint8)

        #create the blocks
        source = blocks.vector_source_b(test_data)
        received = blocks.vector_source_b(test_data)
        s_dist = blocks.vector_sink_f()
        s_peak = blocks.vector_sink_f()
        s_offset = blocks.vector_sink_f()
        dut = lab_radar.corr_dist_estimator_bfi(6)

        # make connections
        self.tb.connect(source, (dut,0))
        self.tb.connect(source, (dut,1))
        self.tb.connect((dut,0), s_dist)
        self.tb.connect((dut,1), s_peak)
        self.tb.connect((dut,2), s_offset)

        # set up fg
        self.tb.run()
        distances = s_dist.data()
        print("distances:" + str(distances))
        peaks = s_peak.data()
        print("peaks:" + str(peaks))
        offsets = s_offset.data()
        print("offsets:" + str(offsets))

        # check data
        print("Hallo")


if __name__ == '__main__':
    gr_unittest.run(qa_corr_dist_estimator_bfi)
