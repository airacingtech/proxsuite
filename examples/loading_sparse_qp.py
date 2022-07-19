import proxsuite_pywrap as proxsuite

# load a Qp object using Qp problem dimensions
n = 10
n_eq = 2
n_in = 2
Qp = proxsuite.qp.sparse.QP(n,n_eq,n_in)

import numpy as np
import scipy.sparse as spa

def generate_mixed_qp(n,seed=1):
    #A function for generating random convex Qps
    
    np.random.seed(seed)
    n_eq = int(n/4)
    n_in = int(n/4)
    m =  n_eq + n_in

    P = spa.random(n, n, density=0.075,
                data_rvs=np.random.randn,
                format='csc').toarray()
    P = (P+P.T)/2.  

    s = max(np.absolute(np.linalg.eigvals(P)))
    P += (abs(s)+1e-02) * spa.eye(n) 
    P = spa.coo_matrix(P)
    q = np.random.randn(n)
    A = spa.random(m, n, density=0.15,data_rvs=np.random.randn,format='csc')
    v = np.random.randn(n)   # Fictitious solution
    delta = np.random.rand(m)  # To get inequality
    u = A@v 
    l = (- 1.e20 * np.ones(m)) 

    return P,q,A[:n_eq,:],u[:n_eq],A[n_in:,:],u[n_in:],l[n_in:]

# load a Qp2 object using matrix masks
H,g,A,b,C,u,l = generate_mixed_qp(n)

H_ = H!=0.
A_ = A!=0.
C_ = C!=0.
Qp2 = proxsuite.qp.sparse.QP(H_,A_,C_)