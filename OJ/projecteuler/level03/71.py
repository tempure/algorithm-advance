# Farey Sequence https://zh.wikipedia.org/wiki/%E6%B3%95%E9%87%8C%E6%95%B8%E5%88%97
# 假设第一个分数为a/b，第三个分数为c/d，则中间第二个分数为(a+c)/(b+d)
# https://pe.metaquant.org/pe071.html
# ans = 428570

def main(D=10**6):
    k = int((D-5)/7)
    return 2+3*k


if __name__ == '__main__':
    print(main())