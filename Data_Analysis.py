import numpy as np
import matplotlib.pyplot as plt
from scipy.special import ellipk
import mpmath as mpm
import sys

def GetBinnedError(data):
    # Returns the standard error in "data" and resturns neighbor-averaged data
    # Almost directly copied from the 2d_Ising_model_Monte_Carlo.ipynb
    N_bins = data.size
    delta = np.std(data)/np.sqrt(N_bins)

    start_bin = N_bins % 2
    binned_mc_data = 1/2*(data[start_bin::2] + data[start_bin+1::2])

    return delta, binned_mc_data

def OnsagerSolution(numberTemps, initialTemp, finalTemp):
    exact = np.arange(initialTemp, finalTemp, 1/numberTemps)

    
    for i in range(numberTemps):
        q = 2*mpm.sinh(2/exact[i])/(mpm.cosh(2/exact[i])*mpm.cosh(2/exact[i]))
        exact[i] = ellipk(q)

def main():
    with open(sys.argv[1]) as f:
        lines = (line for line in f if not line.startswith('#'))
        data = np.loadtxt(lines, skiprows=1)

    length = len(data)

    energyPerSpin = data[:,3]
    magPerSpin = data[:,2]

if __name__ == "__main__":
    main()
