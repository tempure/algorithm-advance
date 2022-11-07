# 这个题解：https://pe.metaquant.org/pe173.html 的公式和代码里面的怎么不一样
# 代码里面是 side//i - i, 题解里面公式推是 N/4/n + n ....
# ans = 1572729
# 但是代码改为 side//i + i 答案却是错的，离谱
# 这个题解的思路就是按照n分类，对于每个n计算对应有多少个x
# 但是这个公式里面居然计算进去了 x = 1 的情况也算合法。。。我不太懂了。。。。
# 正确的解法看 173.cpp 的解法 

def main(N=10**6):
    side = N//4
    u = int(side**0.5) + 1
    res = sum((side//i-i for i in range(1,u)))
    return res

if __name__ == '__main__':
    print(main())