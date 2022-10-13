"""
这个题不需要写代码, 需要算二维积分
https://pe.metaquant.org/pe449.html
ans = 103.37870096
"""

# python 写的代码解出来的精度居然这么高。。。
# 代码跑出来的结果就是103.37870096022905

from cmath import tanh
import math

from numpy import arctan, arctan2, arctanh


def main():
    a = 3
    b = 1
    k = 1
    v = (
        math.pi
        * 1
        / 12
        * (
            27 * math.sqrt(2) * math.pi
            + 256
            - 27 * math.sqrt(2) * arctan(4 * math.sqrt(2) / 7)
            + 18 * math.sqrt(2) * arctanh(2 * math.sqrt(2) / 3)
        )
    )
    print(v)


if __name__ == "__main__":
    main()
