# 枚举底数和次幂，然后判断就行
# https://pe.metaquant.org/pe119.html
# 注意这种枚举得到的结果不是单调递增的，需要最后排序
# 找到30个需要尝试b,p的数据范围
# ans = 248155780267521

def main(k=30):
    arr = []
    for b in range(2,100):
        for p in range(2,10):
            n = b ** p
            if n > 10:
                ds = sum([int(x) for x in str(n)])
                if ds == b:
                    arr.append(n)
    return sorted(arr)[k-1]

if __name__ == '__main__':
    print(main())