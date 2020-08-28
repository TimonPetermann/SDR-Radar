/* -*- c++ -*- */

#define LAB_RADAR_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "lab_radar_swig_doc.i"

%{
#include "lab_radar/corr_dist_estimator_bfi.h"
%}

%include "lab_radar/corr_dist_estimator_bfi.h"
GR_SWIG_BLOCK_MAGIC2(lab_radar, corr_dist_estimator_bfi);
