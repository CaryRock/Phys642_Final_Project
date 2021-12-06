#! /usr/bin/env python3
# This isn't going on anything that doesn't use python3, and if it is, they 
# know what they're doing already.
# Computes the Specific Heat, #1), part c. 

import numpy as np
import matplotlib.pyplot as plt
from scipy.special import ellipk
import mpmath as mpm
import os
import sys

# So, I could write some method of sifting out the temperature from the file 
# names, OR, I can just input the range and step size manually. They all have 
# the same range of temperatures, after all.

def main():
### Basic variable initialization, etc. #######################################
    L       = int(sys.argv[1]) # It's very basic, but quite sufficient
    selif = os.listdir()
    files = sorted(selif)
    
    nF      = len(selif)
    Trange = np.linspace(0.5, 3.45, len(selif))

    MperN = np.zeros(len(selif))
    EperN = np.copy(MperN)

### Compute Elliptic Integral, K_1(q) #########################################
    q       = np.copy(Trange)
    exactCv   = np.copy(Trange)

    Tc = 2/np.log(1+np.sqrt(2))

    for i in range(len(Trange)):
        K = 1/Trange[i]
        q[i] = 2*mpm.sinh(2*K)*mpm.sech(2*K)*mpm.sech(2*K)
    
    # I know there's vectorize, but I can figure that out later
    for i in range(len(Trange)):
        K           = 1/Trange[i]
        coth2K2     = ( K * mpm.coth(2*K) )
        coth2K2     *= coth2K2
        1mTanh2K    = mpm.tanh(2*K)
        1mTanh2K    *= 1mTanh2K
        2Tanh2Km1   = 1mTanh2K
        2Tanh2Km1   = 2Tanh2Km1 - 1.0
        1mTanh2K    = 1 - 1mTanh2K


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
    plt.plot(Trange, exact, 'k--', label="Onsager Exact <E>/N")
    plt.legend()
    plt.xlabel("T (K)")
    plt.ylabel("<E>/N (units of J)")
    plt.title("<E>/N vs T")

    plt.show()

    plt.plot(Trange, MperN, 'r.', label="<M>/N")
    plt.plot(Trange, exactM, 'k--', label="Onsager Exact <M>/N")
    plt.legend()
    plt.xlabel("T (K)")
    plt.ylabel("<M>/N (unitless)")
    plt.title("<M>/N vs T")
    plt.show()

if __name__ == "__main__":
    main()
