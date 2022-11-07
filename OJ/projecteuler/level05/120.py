# 纯纯的推公式就行了，这题可以手算
# https://pe.metaquant.org/pe120.html
# 注意转换为线性丢番图方程这一步还是需要思考一下的
# ans = 333082500

def main():
    even = [a**2-2*a for a in range(3,1001) if a%2==0]
    odd = [a**2-a for a in range(3,1001) if a%2==1]
    ans = sum(even) + sum(odd)
    return ans


if __name__ == '__main__':
    print(main())