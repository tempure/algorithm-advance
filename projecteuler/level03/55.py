# https://pe.metaquant.org/pe055.html
# ans = 249
# 暴力

def is_lychrel(x):
    is_palindrome = lambda x : str(x) == str(x)[::-1]
    for _ in range(50):
        x += int(str(x)[::-1])
        if is_palindrome(x):
            return False
    return True

def main():
    ans = len([x for x in range(1,10000) if is_lychrel(x)])
    return ans

if __name__ == '__main__':
    print(main())