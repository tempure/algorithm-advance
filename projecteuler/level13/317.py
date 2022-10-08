"""
Envelope: https://en.wikipedia.org/wiki/Envelope_(mathematics)
求抛物线方程，然后求包络线方程
每一个角度对应一个抛物线轨迹，而这些抛物线轨迹的包络线可以将这些抛射轨迹都包含其中
就是一堆抛物线他们互相交叉，但是包络线是和这些所有抛物线都至少有一个点相切的最外面的那条
ans = 1856532.8455
"""

import math

def main():
    v = 20
    h = 100
    g = 9.81;
    res = math.pi * (v**2) / g * (h + v**2/(2*g))**2
    print(res)

if __name__ == '__main__':
    main() 