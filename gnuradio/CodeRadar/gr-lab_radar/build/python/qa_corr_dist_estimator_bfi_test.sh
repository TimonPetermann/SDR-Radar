#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir="/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/python"
export GR_CONF_CONTROLPORT_ON=False
export PATH="/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/python":$PATH
export LD_LIBRARY_PATH="":$LD_LIBRARY_PATH
export PYTHONPATH=/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/swig:$PYTHONPATH
/usr/bin/python3 /home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/python/qa_corr_dist_estimator_bfi.py 
