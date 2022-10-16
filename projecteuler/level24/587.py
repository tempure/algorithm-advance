from math import sqrt, asin, pi

# 解析几何题，然后直观求面积就行了
# 技巧就是设斜率和交点横坐标的关系
# ans = 2240

def t(n):
    res = (n ** 2 + n - sqrt(2) * n ** 1.5) / (n**2 + 1)
    return res

def area(t, n):
    res = 1/(2*n) - asin(1-t)/2 + (1-t)*(1-1/n)/2
    return res


def main():
    N = 0.001
    i = 100
    while(True):
        if area(t(i), i) / (1-pi/4) < N:
            return i
        else:
            i = i + 1

print(main())
