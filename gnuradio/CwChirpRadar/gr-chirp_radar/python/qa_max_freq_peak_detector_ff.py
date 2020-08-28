#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 Timon Petermann, Lisa Elsner.
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
from max_freq_peak_detector_ff import max_freq_peak_detector_ff

import numpy as np

class qa_max_freq_peak_detector_ff(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def runningRndTest(self):
        # create random signal as input data for block
        num_signals = 5
        amp = np.arange(1, 10 * num_signals + 1, 10)
        freqs = np.random.uniform(1, 10, num_signals)
        f_samp = 50
        num_samp = 8192
        T_samp = 1/f_samp
        t = np.arange(0, num_samp*T_samp, T_samp)
        signal = np.zeros(len(t))
        for i in range(num_signals):
            signal = signal + amp[i] * np.cos(2*np.pi*freqs[i]*t)

        # expected result
        idx_expected = np.argmax(amp)
        expected_result = freqs[idx_expected]
        print("Expected: ", expected_result)

        # create blocks
        src = blocks.vector_source_f(signal, vlen=len(signal))
        dut = max_freq_peak_detector_ff(sampling_rate=f_samp, f_max = 5,f_min = 2, fft_size=len(signal))
        sink = blocks.vector_sink_f()

        #connect blocks
        self.tb.connect((src,0), (dut,0))
        self.tb.connect((dut,0), (sink,0))

        #run test
        self.tb.run()

        # check data
        result = sink.data()
        print(result)
        print("Result: ", result[0])
        if expected_result > 5:
            self.assertLessEqual(result[0], 5)
        elif expected_result < 2:
            self.assertGreaterEqual(result[0], 2)
        else:
            self.assertAlmostEqual(expected_result, result[0], places=1)

    def test_001_t(self):
        self.runningRndTest()
    def test_002_t(self):
        self.runningRndTest()
    def test_003_t(self):
        self.runningRndTest()
    def test_004_t(self):
        self.runningRndTest()
    def test_005_t(self):
        self.runningRndTest()




if __name__ == '__main__':
    gr_unittest.run(qa_max_freq_peak_detector_ff)
