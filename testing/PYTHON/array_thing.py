#! /usr/bin/env python3

import numpy as np

def get_binned_error(data):
    N = data.size
    delta = np.std(data)/np.sqrt(N)

    start = len(data) % 2
    binned_data = 1/2*(data[start::2] + data[start+1::2])
    
    return delta, binned_data

def main():
    x = np.linspace(1,10,10)
    print(f"x = {x}")
    
    start = len(x) % 2
    x_even = x[start::2]
    x_odd = x[start+1::2]

    print(f"x_even = {x_even}")
    print(f"x_odd = {x_odd}")

    num_levels = int(np.log2(x.size))   # Don't add that +1 from his code - it's too many steps here
    print(f"# of possible levels = {num_levels}")
    for i in range(num_levels):
        deltaX, x = get_binned_error(x)
        print(f"delta = {deltaX}\nbinned_x = {x}")

if __name__ == "__main__":
    main()
