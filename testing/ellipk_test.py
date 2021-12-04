import numpy as np
import matplotlib.pyplot as plt
from scipy.special import ellipk
import mpmath as mpm
import sys

def main():
    numberTemps = 40
    initialTemp = 0.2
    finalTemp = 3.2
    
    x = np.linspace(initialTemp, finalTemp, numberTemps)
    print(f"Temperature array:\n{x}")
    q = np.copy(x)
    exact = np.copy(x)

    
    for i in range(numberTemps):
        K = 1/x[i]
        q[i] = 2*mpm.sinh(2*K)*mpm.sech(2*K)*mpm.sech(2*K)
    
    for i in range(numberTemps):
        K = 1/x[i]
        exact[i] = -mpm.coth(K)*(1 + 2/np.pi * (2*mpm.tanh(2*K)*mpm.tanh(2*K)-1)*ellipk(q[i]) )
    
    print(f"Exact solution values:\n{exact}")
    fig = plt.figure()
    plt.plot(x, exact, 'r--', label="Onsager")
    plt.legend()
    plt.xlabel("T (K)")
    plt.ylabel("E (in units of J)")
    plt.show()

if __name__ == "__main__":
    main()
