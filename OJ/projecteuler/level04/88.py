# https://pe.metaquant.org/pe088.html
# 本质还是在一定范围内暴力
# ans = 7587457
# how to prove n <= 2k ??

def main():
    def update_min_n_arr(p,s,f,start):
        k = p - s + f
        if k < 12001:
            min_n_arr[k] = min(min_n_arr[k],p)
            for i in range(start,12000//p*2):
                update_min_n_arr(p*i,s+i,f+1,i)

    min_n_arr = [24000]*12001
    update_min_n_arr(1,1,1,2)
    return sum(set(min_n_arr[2:])) # 2 <= k <= 12000

if __name__ == '__main__':
    print(main())