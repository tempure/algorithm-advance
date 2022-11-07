# 大数用c++确实折磨。。。
a,ans=1,0
for i in range(1,100+1):
    a*=i
while a>0:
    ans+=a%10
    a//=10
print(ans)