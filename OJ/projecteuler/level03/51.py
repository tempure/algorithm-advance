# time cost = 355 ms ± 1.51 ms
# ans = 121313
# https://www.cnblogs.com/metaquant/p/11820821.html

from sympy import nextprime,isprime
from collections import Counter

def is_replacable_prime(n):
    s = str(n)
    count = Counter(s)
    num,d = count.most_common(1)[0]
    if d % 3 == 0 and num in set('012'):
        k = 1
        for j in range(int(num)+1,10):
            new = s.replace(num,str(j))
            if isprime(int(new)):
                k += 1
        if k == 8:
            return True
    return False

def main():
    n = 1111
    while True:
        p = nextprime(n)
        if is_replacable_prime(p):
            print(p)
            return
        else:
            n = p

if __name__=="__main__":
    main()