import numpy as np
import matplotlib.pyplot as plt

def TridiagMatrixAlg(a, b, c, d, N):
    y = np.array([0.] * N)
 
    for i in range(1, N):
        xi = a[i] / b[i-1]
        a[i] = 0
        b[i] -= xi * c[i-1]
        d[i] -= xi * d[i-1]

    y[N-1] = d[N-1]/b[N-1]    
    
    for i in range(N-2, -1, -1):
        y[i] = 1/b[i] * (d[i] - c[i]*y[i+1])    
    return y

def U(x):
    # return x*0.
    return x**2/2

def A(x, N):
    h = x[1] - x[0]
    a = np.array([-1./(2 * h**2)] * N)
    a[0] = 0
    b = 1. / (h**2) + U(x)
    c = np.array([-1./(2 * h**2)] * N)
    c[N-1] = 0
    return a, b, c

def Orthogonalization(psi_next, psi_prevs):
    for psi in psi_prevs: # ортогонализация
        psi_next -= psi * (np.inner(psi_next, psi)) / np.linalg.norm(psi)

def InverseIterations(psi0, x, N, iteration, levels):
    E = []
    psi = []
    a, b, c = A(x, N)
    for m in range(0, levels):
        psi_next = psi0.copy()
        Orthogonalization(psi_next, psi)
        for k in range(0, iteration):
            psi_prev = psi_next
            psi_next = TridiagMatrixAlg(np.copy(a), np.copy(b), np.copy(c), np.copy(psi_next), N)
            Orthogonalization(psi_next, psi)
    
        E0 = np.linalg.norm(psi_prev) / np.linalg.norm(psi_next)
        E.append(E0)
        psi_next /= np.linalg.norm(psi_next)        
        psi.append(psi_next)
    
    return E, psi
    
def main():
    N = 1000 # partion
    iteration = 50 # А**(iteration)
    x1 = -10
    x2 = 10 
    levels = 3
    x = np.linspace(x1, x2, N)
    y0 = np.linspace(1, 2, N) # pseudo solution
    E, psi = InverseIterations(y0, x, N, iteration, levels)

    for i in range(0, levels):
        print(str.format('E{}: {}', i, E[i]))
        plt.plot(x, psi[i], label = 'psi' + str(i))
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()