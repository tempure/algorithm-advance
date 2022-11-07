# 和137题是一样的，只不过递推初始项变了而已
# 这就导致一个问题就是，方程的基本解有更多组了，所以用之前137题的对于每组基本解都分类讨论就代码太麻烦了
# 所以可以考虑使用矩阵递推，python 的 sympy 有专门用来求解佩尔方程的库，，，但是我不太会用。。。
# pelleq_solution_generator(d,n) 函数我没理解错的话就是一直返回解？？？似乎看起来是这样的
# https://pe.metaquant.org/pe140.html
# ans = 5673835352990

import numpy as np
from sympy.solvers.diophantine.diophantine import diop_DN

def pelleq_solution_generator(d,n): # 传进去的参数就是佩尔方程里面的 d 和 n
    u,v = diop_DN(d,1)[0]
    uv_zero = np.mat([[u],[v]])
    uv_mat = np.mat([[u,d*v],[v,u]])
    xy_mat = [np.mat([[x,d*y],[y,x]]) for x,y in diop_DN(d,n)]
    new_mat = np.identity(2,dtype=int)
    while True:
        yield [np.abs(x @ new_mat @ uv_zero) for x in xy_mat]
        new_mat = new_mat @ uv_mat

def main(N=30):
    arr = [2]
    for sol in pelleq_solution_generator(5,44):
        for ans in sol:
            if ans[0,0] % 5 == 2:
                arr.append((ans[0,0]-7)//5)
                if len(arr) == N:
                    return sum(arr)


if __name__ == '__main__':
    print(main())