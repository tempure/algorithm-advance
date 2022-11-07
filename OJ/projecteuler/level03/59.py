# 维吉尼亚密码 https://zh.wikipedia.org/wiki/%E7%BB%B4%E5%90%89%E5%B0%BC%E4%BA%9A%E5%AF%86%E7%A0%81
# 频率分析破解
# https://pe.metaquant.org/pe059.html
# ans = 129448

from collections import Counter

def main():
    with open('../data/p059_cipher.txt') as f:
        cipher = list(map(int,f.read().split(',')))
    space_ascii = ord(' ')
    key = [Counter(cipher[i::3]).most_common(1)[0][0] ^ space_ascii for i in range(3)]
    cycles = len(cipher)//3
    res = sum([x^y for x,y in zip(cipher,key*cycles)])
    return res

if __name__ == '__main__':
    print(main())