#! /usr/bin/env python3
# This isn't going on anything that doesn't use python3, and if it is, they 
# know what they're doing already.
# Computes the Specific Heat, #1), part c. 

import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# So, I could write some method of sifting out the temperature from the file 
# names, OR, I can just input the range and step size manually. They all have 
# the same range of temperatures, after all.

def main():
    selif = os.listdir()
    files = sorted(selif)
    
    Trange = np.linspace(0.5, 3.45, len(selif))
    print(f"Number of files in directory: {len(selif)}")

if __name__ == "__main__":
    main()
