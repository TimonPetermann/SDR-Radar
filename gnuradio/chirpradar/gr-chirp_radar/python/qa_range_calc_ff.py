#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 Lisa Elsner.
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
from range_calc_ff import range_calc_ff

import numpy as np

class qa_range_calc_ff(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):

        speed_of_light = 300000000 # meter per seconds
        bandwidth = 1000 # hertz
        chirp_period = 0.000010 # seconds

        #create input and output data
        freqs = np.arange(0, 10000, 1000)

        #create output data (ranges)
        expected_result = np.arange(0, 10, 1)
        for i in range(10):
            expected_result[i] = (speed_of_light*freqs[i]*chirp_period) / (2*bandwidth)


        #create blocks
        src = blocks.vector_source_f(freqs)
        dut = range_calc_ff(1000, 0.000010)
        sink = blocks.vector_sink_f()

        #connections
        self.tb.connect(src, dut)
        self.tb.connect(dut, sink)

        #run test
        self.tb.run()

        #result
        result = sink.data()
        print(expected_result)
        print(result)

        #do a check
        self.assertFloatTuplesAlmostEqual(expected_result, result, places = 3)


if __name__ == '__main__':
    gr_unittest.run(qa_range_calc_ff)




