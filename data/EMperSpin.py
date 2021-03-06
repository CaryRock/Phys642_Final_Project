#! /usr/bin/env python3
# Produces a plot of <E>/N and <M>/N vs. T

import numpy as np
import matplotlib.pyplot as plt
from scipy.special import ellipk
import mpmath as mpm
import os
import sys

def main():
### Basic variable initialization, etc. #######################################
    L       = int(sys.argv[1]) # It's very basic, but quite sufficient
    selif   = os.listdir()
    files   = sorted(selif)
    nF      = len(selif)
    Trange = np.linspace(0.5, 3.45, len(selif))
#    for i in range(len(selif)):
#        Trange[i] = 1/Trange[i]

    MperN = np.zeros(len(selif))
    EperN = np.copy(MperN)

### Compute Elliptic Integral, K_1(q) #########################################
    q       = np.linspace(0.5, 3.45, 2*len(selif)+1)
    t       = np.copy(q)
    exact   = np.copy(q)
    exactM  = np.copy(q)

    Tc = 2/np.log(1+np.sqrt(2))

    for i in range(len(t)):
        K           = 1/t[i]
        q[i]        = 2 * mpm.sinh(2*K) / ( mpm.cosh(2*K) * mpm.cosh(2*K) )
        A           = 2 * mpm.tanh(2*K) * mpm.tanh(2*K) - 1
        exact[i]    = -mpm.coth(2*K) * (1 + 2/np.pi * A * ellipk(q[i]*q[i]) )
        tanh2K      = mpm.tanh(K)
        tanh2K      *= tanh2K

        if(t[i] < Tc):
            numer       = np.power(1-tanh2K, 4)
            denom       = 16 * tanh2K * tanh2K
            exactM[i] = np.power(1-numer/denom, 1/8)
        else:
            exactM[i] = 0

### Read the data from the files and do the things ############################
    for i in range(nF):
        with open(files[i],"r") as f:
            lines = (line for line in f if not line.startswith('#'))
            data = np.loadtxt(lines, skiprows=2)
        f.close()
        
        for j in range(len(data)):
            EperN[i] += data[j][0]
            MperN[i] += data[j][1]
    
    EperN /= len(data)
    MperN /= len(data)

### Make the plots ############################################################
    fig = plt.figure()
    plt.plot(Trange, EperN, 'b.', label="<E>/N")
    plt.plot(t, exact, 'k--', label="Onsager Exact <E>/N")
    plt.legend()
    plt.xlabel("T (K)")
    plt.ylabel("<E>/N (units of J)")
    plt.suptitle("<E>/N vs T")
    plt.title(f"L = {L}")

    plt.show()

    plt.plot(Trange, abs(MperN), 'r.', label="<M>/N")
    plt.plot(t, exactM, 'k--', label="Onsager Exact <M>/N")
    plt.legend()
    plt.xlabel("T (K)")
    plt.ylabel("<M>/N (unitless)")
    plt.suptitle("<M>/N vs T")
    plt.title(f"L = {L}")
    plt.show()

if __name__ == "__main__":
    main()
