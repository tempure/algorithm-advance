# 用埃氏筛的思路降低复杂度求质因数乘积的结果
# 然后就是双关键字排序就行了
# https://pe.metaquant.org/pe124.html
# ans = 21417

def main(n=10**5,k=10**4):
    arr = [[1,i] for i in range(n+1)]
    for i in range(2,n+1):
        if arr[i][0] == 1: # arr[i][0]==1 此时说明 i 未被前面的数筛掉，是个素数
            for j in range(i,n+1,i):
                arr[j][0] *= i
    return sorted(arr)[k][1]

if __name__ == '__main__':
    print(main())