# 就直接枚举就行了，很简单的题
# https://pe.metaquant.org/pe206.html
# ans = 1389019170

def is_concealed_square(number):
    seq = ['1', '2', '3', '4', '5', '6', '7', '8', '9','0']
    digits = [x for x in str(number)]
    if len(digits) == 19 and digits[0::2] == seq:
        return True
    return False

def main(n=1389026620):
    while True:
        if is_concealed_square(n**2):
            return n
        else:
            n = n - 10


if __name__ == '__main__':
    print(main())