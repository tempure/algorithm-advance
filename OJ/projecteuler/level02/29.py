import math
List = []
for a in range (2,101):
    for b in range (2,101):
        x = math.pow(a,b)
        List.append(x)
List = list(set(List))
print(len(List))

#https://zhuanlan.zhihu.com/p/62291839