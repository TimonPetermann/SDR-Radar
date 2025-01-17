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


import numpy
from gnuradio import gr

class max_freq_peak_detector_ff(gr.sync_block):
    """
    docstring for block max_freq_peak_detector_ff
    """
    def __init__(self, sampling_rate, f_max, f_min, fft_size=1024):
        gr.sync_block.__init__(self,
            name="max_freq_peak_detector_ff",
            in_sig=[(numpy.float32, fft_size)],
            out_sig=[numpy.float32])
        self.fft_size = fft_size
        self.sampling_rate = sampling_rate
        self.f_max = f_max
        self.f_min = f_min

        #set up frequency interval once for efficiency
        T_samp = 1/self.sampling_rate
        self.f = numpy.fft.fftfreq(self.fft_size, d=T_samp)
        self.mask = numpy.logical_or(numpy.abs(self.f) > f_max, numpy.abs(self.f) < f_min)


    def work(self, input_items, output_items):
        in0 = input_items[0][0]

        # check input data conditions
        if(len(in0) != self.fft_size):
            raise ValueError('Input vector size does not match fft_size!')

        # apply fourier transform and lowpass filter
        fft_signal = numpy.fft.fft(in0)
        fft_signal[self.mask] = 0

        # retrieve frequency peak and set belonging frequency to output
        idx = numpy.argmax(numpy.abs(fft_signal))
        if(idx >= len(self.f)):
            idx = len(self.f) - 1
        output_items[0][0] = abs(self.f[idx])

        return len(output_items)

