# 多项式插值，牛顿插值法实现
# https://pe.metaquant.org/pe101.html
# ans = 37076114526

def main():
    res = 0
    tdp = lambda x: (x**11+1)//(x+1)
    arr = [tdp(x) for x in range(1,11)]
    # 这里的 diff 函数求差分数组技巧注意
    diff = lambda arr:[x-y for x,y in zip(arr[1:],arr[:-1])]
    for _ in range(10):
        res += sum(arr)
        arr = diff(arr)
    return res


if __name__ == '__main__':
    print(main())