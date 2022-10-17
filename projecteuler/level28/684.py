# 推公式求和
# 求s(n)思路就是贪心，第一位尽可能小，后面全部取9，这样可以保证位数最少
# 求和就基本等比数列求和
# https://pe.metaquant.org/pe684.html 
# ans = 922058210

def s(k,r,m=10**9+7):
    res = (((r+1)*(r+2)//2+5)*pow(10,k,m)-(9*k+6+r)%m + m)%m
    return res

def main(n=90):
    fib = [0,1]
    for _ in range(n-1):
        fib.append(sum(fib[-2:]))
    res = [s(*divmod(fib[i],9)) for i in range(2,n+1)]
    return sum(res)%(10**9+7)

print(main())
