def isprime(n):
    if n <= 1:
        return False
    for i in range(2,int(n**0.5+1)):
        if n % i == 0:
            return False
    return True
 
num = 0
longest = 0
l = []
for a in range(-1000,1000):
    for b in range(-1000,1001):
        for n in range(1000): # 100 1000 尝试
            f = n**2 + a*n + b
            if isprime(f):
                num = n
                continue
            else:
                break
        if longest < num:
            longest = num
            l = [a,b]
print(longest)
print(l[1]*l[0])

#https://blog.csdn.net/wxinbeings/article/details/80218667
#https://zhuanlan.zhihu.com/p/62137330