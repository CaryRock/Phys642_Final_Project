#! /usr/bin/env python3
# This isn't going on anything that doesn't use python3, and if it is, they 
# know what they're doing already.
# Computes the Specific Heat, #1), part c. 

import numpy as np
import matplotlib.pyplot as plt
from scipy.special import ellipk
from scipy.special import ellipe
import mpmath as mpm
import os
import sys

# So, I could write some method of sifting out the temperature from the file 
# names, OR, I can just input the range and step size manually. They all have 
# the same range of temperatures, after all.

# Basically directly copied from the provided 2d_Ising_model_Monte_Carlo.ipynb file
# Asks for a single vector, returns that vector averaged and the according error bars
def get_binned_error(data):
    N = data.size
    delta = np.std(data)/np.sqrt(N)

    start = N % 2
    binned_data = 0.5*(data[start::2] + data[start+1::2])

    return delta, binned_data

def ComputeExactCv(x_a, x_b, num):
    t       = np.linspace(x_a, x_b, num)
    q       = np.copy(t)
    exactCv = np.copy(q)

    Tc = 2/np.log(1+np.sqrt(2))

    for i in range(len(t)):
        K = 1/t[i]
        q[i] = 2*mpm.sinh(2*K)*mpm.sech(2*K)*mpm.sech(2*K)
    
    # I know there's vectorize, but I can figure that out later
    for i in range(len(t)):
        K           = 1/t[i]
        coth2K2     = ( K * mpm.coth(2*K) )
        coth2K2     *= coth2K2
        _1mTanh2K   = mpm.tanh(2*K)
        _1mTanh2K   *= _1mTanh2K
        _2Tanh2Km1  = _1mTanh2K
        _2Tanh2Km1  = _2Tanh2Km1 - 1.0
        _1mTanh2K   = 1 - _1mTanh2K
        ellk        = ellipk(q[i])
        exactCv[i]  = 4/np.pi*coth2K2* ( ellk - ellipe(q[i])  - _1mTanh2K*( np.pi/2 + _2Tanh2Km1*ellk ) )

    return t, exactCv

def main():
### Basic variable initialization, etc. #######################################
    L       = int(sys.argv[1]) # It's very basic, but quite sufficient
    selif = os.listdir()
    files = sorted(selif)
        
    nF      = len(selif)

    x_a = 0.5
    x_b = 3.45
    Trange = np.linspace(x_a, x_b, nF)

    EperN   = np.zeros(nF)
    E2perN  = np.copy(EperN)

### Compute Elliptic Integral, K_1(q) #########################################
    t, exactCv = ComputeExactCv(x_a, x_b, 2*nF + 1)

### Read the data from the files and do the things ############################
    for i in range(nF):
        with open(files[i],"r") as f:
            lines = (line for line in f if not line.startswith('#'))
            data = np.loadtxt(lines, skiprows=2)
        f.close()
        
        EperN[i]    = np.average(data[:,0])
        data2       = np.zeros(len(data))
        for j in range(len(data)):
            data2[j] = data[j][0] * data[j][0] * L * L
        E2perN[i]   = np.average(data2[:])
    
    specHeat = np.zeros_like(EperN)
    for i in range(len(EperN)):
        specHeat[i] = ( E2perN[i] - (EperN[i]*EperN[i] * L * L) )/ (Trange[i]*Trange[i])

    print(f"Estimated value of simulation critical temperature: {Trange[np.argmax(specHeat)]}")
    #skip = 0    # Data was already equilibriated
    #Eave = np.average(EperN[skip:],axis=0)

    #num_levels = int(np.log2(M[skip:,0].size/4))+1
    #errorE = np.zeros([len(Trange), num_levels])
    
    #for iT,cT in enumerate(Trange):
    #    binned_mc_data = EperN[;,iT]    # His raw data is in multiple columns; mine is not

### Make the plots ############################################################
    fig = plt.figure()
    plt.axvline(t[np.argmax(exactCv)], linestyle='dotted')
    plt.plot(Trange, specHeat, 'b.', label=r"MC $C_v$")
    plt.plot(t, exactCv, 'r--', label=r"Onsager $C_v$")
    plt.show()

if __name__ == "__main__":
    main()
