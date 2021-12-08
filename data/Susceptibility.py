#! /usr/bin/env python3
# Computes the susceptibility. #1), part d

import numpy as np
import matplotlib.pyplot as plt
import os
import sys

def main():
    L       = int(sys.argv[1])
    selif   = os.listdir()
    files   = sorted(selif)
    nF      = len(selif)
    x_a     = 0.5
    x_b     = 3.45
    Trange  = np.linspace(x_a, x_b, nF)

    M       = np.zeros(nF)
    M2      = np.zeros(nF)

    for i in range(nF):
        with open(files[i], "r") as f:
            lines = (line for line in f if not line.startswith('#'))
            data = np.loadtxt(lines)
        f.close()
        
        data2 = np.zeros(len(data))
        for j in range(len(data)):
            data2[j] = data[j][1] * data[j][1] * L * L
        M2[i] = np.average(data2[:])
        M[i]  = np.average(data[:,1])

    Xm = np.zeros(nF)
    for i in range(nF):
        Xm[i] = ( M2[i] - (M[i] * M[i] * L * L) ) / Trange[i]
    
    fileName = f"Xm_{L}.dat"
    with open(fileName,"w") as f:
        print("#Xm", file=f)
        for i in range(len(Xm)):
            print(Xm[i], file=f)
    f.close()

    fig = plt.figure()
    plt.plot(Trange, Xm, 'b', linewidth=2, label="Simulation χ")
    plt.title(f"Simulation χ @ L = {L}")
    plt.xlabel("Temperature (K)")
    plt.ylabel(r"$χ_M$")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()
