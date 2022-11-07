# no online judge support sympy ??

# from sympy import isprime

# 这题不知道哥猜应该是做不出来的 - -||
# https://www.acwing.com/solution/content/140215/

import math

def isprime(n):
    for i in range(2, int(math.sqrt(n)+1)):
        if n % i == 0:
            return False
    return True

def main():
    res = 0
    n = int(input())
    if(isprime(n)):
        res = 1
    elif isprime(n-2) or n%2==0:
        res = 2
    else:
        res = 3;
    print(res)

if __name__ == '__main__':
    main()