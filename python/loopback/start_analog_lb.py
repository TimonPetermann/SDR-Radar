import adi
import argparse


# cmd argument stuff
parser = argparse.ArgumentParser()
parser.add_argument("rx_frequency", help="Frequency of Rx in MHz")
parser.add_argument("tx_frequency", help="Frequency of Tx in MHz")

args = parser.parse_args()



# read cmd line args and transform to Hz
rx_freq = int(args.rx_frequency * 1e6)
tx_freq = int(args.tx_frequency * 1e6)

# create pluto object
sdr = adi.Pluto('ip:192.168.2.1')

sdr.rx_lo = rx_freq
sdr.tx_lo = tx_freq

# analog loopback mode
sdr.loopback = 2


input("Press Enter to finish loopback mode...")

# set to default mode and free object
sdr.loopback = 0
del(sdr)