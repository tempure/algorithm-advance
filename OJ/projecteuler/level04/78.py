# 生成函数求整数拆分方案数，更快的算法
# https://en.wikipedia.org/wiki/Partition_(number_theory)#Partition_function
# https://pe.metaquant.org/pe078.html
# 时间复杂度O(sqrt(N))
# ans = 55374

def partion_function(n):
    pn = [1,1]
    for i in range(2,n+1):
        k,acc = 1,0
        g1 = lambda k : i - k*(3*k-1)//2
        g2 = lambda k : i - k*(3*k+1)//2
        f = lambda x : pn[x] if x >= 0 else 0
        while g1(k) >= 0: # 这里不能是 g2(k) >= 0,不然算不出来结果
        # 因为当 g2(k) < 0 时候，此时 g1(k) 还没减到0
            acc += (-1)**(k+1)*(f(g1(k))+f(g2(k)))
            k += 1
        pn.append(acc)
    return pn

def main(N=10**6):
    pn = partion_function(55400)
    for i in range(len(pn)):
        if pn[i] % N == 0:
            return i

if __name__ == '__main__':
    print(main())