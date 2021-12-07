#! /usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import sys
import os

def MakePlot(x, data, lab, fileTitle, O):
    plt.plot(x, data, label=lab)
    plt.suptitle(f"<{O}>/N vs MC Step")
    plt.title(f"File: {fileTitle}")
    plt.xlabel("MC Step #")
    plt.ylabel(f"<{O}>/N")
    plt.show()

def main():
    selif   = os.listdir()
    files   = sorted(selif)
    nF      = len(selif)
    nSamps  = 0

    fig = plt.figure()

    with open(files[0], "r") as f:
        lines = (line for line in f if not line.startswith('#'))
        nSamps = len(np.loadtxt(lines))
    f.close()

    data = np.zeros((nSamps,4))
    for i in range(nF):
        with open(files[i], "r") as f:
            lines = (line for line in f if not line.startswith('#'))
            read = np.loadtxt(lines)
        f.close()
        
        for j in range(nSamps):
            data[j,0 + nF*i] = read[j,0]
            data[j,1 + nF*i] = read[j,1]

    x = np.linspace(0,nSamps-1, nSamps)

    '''
    plt.plot(x, data[:,0], label="<E>/N")
    plt.plot(x, data[:,1], 'k.', label="<M>/N")
    plt.suptitle("<E>/N, <M>/N vs. MC Step")
    plt.title(f"File: {files[i]}")
    plt.xlabel("MC Step #")
    plt.ylabel("<E>/N, <M>/N")
    plt.show()
    '''
    lab = ["<E>/N", "<M>/N","<E>/N", "<M>/N"]
    fileTitle = [files[0], files[0], files[1], files[1]]
    O = ["E", "M", "E", "M"]
    for i in range(4):
        MakePlot(x, data[:,i], lab[i], fileTitle[i], O[i])

if __name__ == "__main__":
    main()
