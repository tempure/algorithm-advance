# 这个题当然暴力是可做的，只不过复杂度很高 1e9 的数据要算很久
# 分类讨论是比较快的，基本上常数复杂度的，但是讨论情况很多
# https://pe.metaquant.org/pe145.html
# ans = 608720

def reversible_numbers(d):
    r = d % 4
    if r == 0 or r == 2:
        return 20*30**(d//2-1)
    elif r == 3:
        return 100*(500)**((d-3)//4)
    else:
        return 0

def main():
    ans = sum([reversible_numbers(x) for x in range(2,10)])
    return ans


if __name__ == '__main__':
    print(main())