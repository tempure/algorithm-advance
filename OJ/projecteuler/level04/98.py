# 暴力模拟就行了
# 但是这个题解似乎没有考虑超过2个的单词字母相同set之间的两两配对？
# 只考虑了严格数量为2的 pair
# https://pe.metaquant.org/pe098.html
# ans = 18769

def group_by_value(d):
    res = {}
    for k,v in d.items():
        res[v] = [k] if v not in res.keys() else res[v] + [k]
    res = {k:v for k,v in res.items() if len(v)>1}
    return res

def get_word_pairs():
    with open('../data/p098_words.txt') as f:
        words = f.read().replace('"',"").split(',')
    d ={x:tuple(sorted(x)) for x in words}
    pairs = {k:v for k,v in group_by_value(d).items() if len(k)>2 and len(v)==2}
    return pairs

def get_square_numbers():
    is_all_diff = lambda n: len(set(str(n))) == len(str(n))
    squares = [i**2 for i in range(10,31622) if is_all_diff(i**2)]
    sq_dict = {x:len(str(x)) for x in squares}
    return group_by_value(sq_dict)

def main():
    res = []
    squares = get_square_numbers()
    pairs = get_word_pairs()
    for arr in pairs.values():
        dt = len(arr[0])
        for sq in squares[dt]:
            d = {k:v for k,v in zip(arr[0],str(sq))}
            num = int("".join([d[x] for x in arr[1]]))
            if num in squares[dt]:
                res += [sq,num]
    return max(res)

if __name__ == '__main__':
    print(main())