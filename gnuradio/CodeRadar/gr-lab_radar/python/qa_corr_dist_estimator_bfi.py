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
import matplotlib.pyplot as plt


class qa_corr_dist_estimator_bfi(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def byte2bin(self,decimal,l,depth = 0):
        if decimal > 255:
            decimal = decimal % 255
            print ("ERROR: Byte bigger 255")

        if decimal > 1 :
            self.byte2bin(decimal // 2,l,depth+1)
        else :
            while depth < 7 : 
                l.append(0)
                depth = depth + 1

        if decimal%2 : 
            l.append(1)
        else :
            l.append(0)
        return l

    def bytes2bins(self,byte_list):
        l = []
        for byte in byte_list:
            l1 = []
            self.byte2bin(byte,l1)
            l = l +l1
        return l

    def rotate(self,l, n):
        return l[n:] + l[:n]

    def auto_correlation(self,source_signal, sink_signal):
        values = []
        for j in range(len(source_signal)):
            flag = True
            counter = 0
            for so,si in zip (source_signal, self.rotate(sink_signal,j)):
                if so^si :
                    counter = counter - 1
                else:
                    counter = counter + 1
            values.append(counter/len(source_signal))
        return max(values), values.index(max(values))

    def test_001_t(self):

        # simple test

        # arange data
        test_data = np.arange(0, 12, dtype=np.uint8)

        # create the blocks
        source = blocks.vector_source_b(test_data)
        received = blocks.vector_source_b(test_data)
        s_dist = blocks.vector_sink_f()
        s_peak = blocks.vector_sink_f()
        s_offset = blocks.vector_sink_f()
        dut = lab_radar.corr_dist_estimator_bfi(6)

        # make connections
        self.tb.connect(source, (dut, 0))
        self.tb.connect(received, (dut, 1))
        self.tb.connect((dut, 0), s_dist)
        self.tb.connect((dut, 1), s_peak)
        self.tb.connect((dut, 2), s_offset)

        # set up fg
        self.tb.run()

        # check data
        self.assertAlmostEqual(s_peak.data(), (1.0, 1.0))
        self.assertAlmostEqual(s_dist.data(), (0.0, 0.0))
        self.assertAlmostEqual(s_offset.data(), (0.0, 0.0))

    def test_002_t(self):
        path = "/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/python/"
        src_path = path + "source.txt"
        with open(src_path, "rb") as f:
            source_data = f.read()
        sink_path = path + "sink.txt"
        with open(sink_path, "rb") as f:
            sink_data = f.read(102400)
            sink_data = f.read(len(source_data))

        # create the blocks
        source = blocks.vector_source_b(source_data)
        received = blocks.vector_source_b(sink_data)
        s_dist = blocks.vector_sink_f()
        s_peak = blocks.vector_sink_f()
        s_offset = blocks.vector_sink_f()
        dut = lab_radar.corr_dist_estimator_bfi(len(source_data))

        # make connections
        self.tb.connect(source, (dut, 0))
        self.tb.connect(received, (dut, 1))
        self.tb.connect((dut, 0), s_dist)
        self.tb.connect((dut, 1), s_peak)
        self.tb.connect((dut, 2), s_offset)

        # set up fg
        self.tb.run()
        distances = s_dist.data()
        print("distances:" + str(distances))
        peaks = s_peak.data()
        print("peaks:" + str(peaks))
        offsets = s_offset.data()
        print("offsets:" + str(offsets))
        peak_under_test = s_peak.data()[0]

        # check data
        source_bin = self.bytes2bins(source_data)
        sink_bin = self.bytes2bins(sink_data)
        peak, offset = self.auto_correlation(source_bin, sink_bin)
        #offset = (len(source_bin))-offset
        print("expected: peak = " + str(peak) + ", offset=" + str(offset))
        self.assertAlmostEqual(peak_under_test, peak)
        self.assertAlmostEqual(distances[0], 0.0)
        self.assertAlmostEqual(offsets[0], offset)

if __name__ == '__main__':
    gr_unittest.run(qa_corr_dist_estimator_bfi)
