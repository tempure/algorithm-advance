# ans = 142857
# https://pe.metaquant.org/pe052.html

from itertools import count

def main():
    for x in count(10,1):
        if all(set(str(k*x))==set(str(x)) for k in range(6,1,-1)):
            print(x)
            return x

if __name__ == '__main__':
    main()