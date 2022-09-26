# 就本质还是暴力，枚举所有连续平方数的和然后判断是否回文
# 枚举的时候注意用set，因为不同的连续平方数的和有可能相同
# 题解里面的 sqrt(2N-1) + 1/2 ≈ sqrt(N/2)... ? 没懂
# 给出的 n 上界 7071 是没问题的, sqrt(N/2) 也差不多是 7071
# ans = 2906969179

def is_palindromic(n):
    n = str(n)
    return n == n[::-1]

def main(N=10**8):
    psos = set()
    u = int((N/2)**0.5)
    for i in range(1,u):
        sos = i*i
        while sos < N:
            i += 1
            sos += i*i
            if is_palindromic(sos): 
                psos.add(sos)
    return sum(psos)

if __name__ == '__main__':
    print(main())
