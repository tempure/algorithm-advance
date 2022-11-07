#有不用python暴力的方法吗？
#似乎是预处理不是暴力：https://blog.csdn.net/m0_60950850/article/details/122826341
a,ans=pow(2,1000),0
while a>0:
    ans+=a%10
    a//=10
print(ans)