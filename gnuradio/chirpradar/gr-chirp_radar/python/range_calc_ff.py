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


import numpy
from gnuradio import gr

class range_calc_ff(gr.sync_block):
    """
    docstring for block range_calc_ff
    """
    def __init__(self, bandwidth, chirp_period):
        gr.sync_block.__init__(self,
            name="range_calc_ff",
            in_sig=[numpy.float32],
            out_sig=[numpy.float32])
        self.bandwidth = bandwidth
        self.chirp_period = chirp_period
        self.speed_of_light = 300000000


    def work(self, input_items, output_items):
        in0 = input_items[0]

        output_items[0][:] = ( in0[:]*self.speed_of_light*self.chirp_period ) / (2*self.bandwidth) 

        return len(output_items[0])

