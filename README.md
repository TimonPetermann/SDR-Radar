# SDR-Positioning-System
SDR-Positioning-System is misleading - the origianl Idea was implementing a positioning system based on SDR radar. However, this turned to be to complex. Instead two different continuous wave radar system were implemented using GNU radio and two Pluto SDRs.

# FMCW


# Digital Code Modulated Continous Wave Radar (DCMCW)
## First approach
Our first approach based on transmitting a digital code/spreading sequence and recovering the digital signal in order to correlate the digital codes currently being sent and currently being received. This turned out to be too complex and also more effort than necessary.

The module which was written for the digital correlation can be found in **gnuradio/CodeRadar/gr-lab_radar/lib**. It is named **corr_dist_estimator_bfi**. However, it has not been matured, since the first approach was discarded in an unfinished state.

Grc and other files related to the first approach can be directly found in the folder **gnuradio/CodeRadar**

## Second approach
The second approach directly correlates the source signal with the received signal. Therefore, recovering the transmitted digital code is not necessary. This makes the system a lot less complex. The code related to this approach is fully functional.

The modules which were written for the second approach of DCMCW radar can be found in **gnuradio/CodeRadar/gr-lab_radar/lib**, too. The module **simple_decimator_cc** is used for decimating a signal by simply interleaving a configurable amount of samples. The **signal_corr_estimator_cf** module does the main DCMCW signal processing.

The Grc files used for the second approach can be found in **gnuradio/CodeRadar/Second_Approach**. **test1.grc** can be used to simulate the system, **test_pluto.grc** can be used for HIL or full system testing.

# Loop Back
The python script used to set a PlutoSDR into loop back mode can be found in **python/loopback**.