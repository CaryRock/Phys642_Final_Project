#! /usr/bin/env python3
# Computes the susceptibility. #1), part d

import numpy as np
import matplotlib.pyplot as plt
import os
import sys

def MakePlot(x, y, desc):
    plt.plot(x, y, '.', label=desc)

def main():
    L       = np.zeros(4)
    for i in range(4):
        L[i] = 12 + 4*i

    files   = sorted(os.listdir())
    nF      = len(files)
    x_a     = 0.5
    x_b     = 3.45
    Trange  = np.linspace(x_a, x_b, 60)
    t       = np.zeros_like(Trange)
    Tc      = 2/np.log(1+np.sqrt(2))
    for i in range(len(Trange)):
        t[i] = Trange[i]/Tc - 1

    data = np.zeros((nF, len(Trange)))

    for i in range(nF):
        with open(files[i], "r") as f:
            lines = (line for line in f if not line.startswith('#'))
            data[i,:] = np.loadtxt(lines)
        f.close()
    
    desc = ["L = 12","L = 16","L = 20","L = 24"]
    
    nu = 1.0
    gam = 1.75

    fig = plt.figure()
    for i in range(nF):
        MakePlot(t*pow(L[i], 1/nu), data[i,:]*pow(L[i],-gam/nu), desc[i])
    plt.title(f"Collapse of Simulation χ @ L = {L}; γ = {gam}, ν = {1.0}")
    plt.xlabel(r"Reduced temperature, $t$")
    plt.ylabel(r"$χ_M$")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()
