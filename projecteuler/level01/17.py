#怎么又是模拟题。。。
#https://blog.csdn.net/charlie_pyc/article/details/23852419
a=[0 for i in range(1000+10)]
a[1]=3
a[2]=3
a[3]=5
a[4]=4
a[5]=4
a[6]=3
a[7]=5
a[8]=5
a[9]=4
a[10]=3
a[11]=6
a[12]=6
a[13]=8
a[14]=8
a[15]=7
a[16]=7
a[17]=9
a[18]=8
a[19]=8
a[20]=6
a[30]=6
a[40]=5
a[50]=5
a[60]=5
a[70]=7
a[80]=6
a[90]=6
a[100]=7
a[1000]=8
ans=0
for i in range(1,20+1):
    ans+=a[i]
for i in range(21,100):
    a[i]=a[i//10*10]+a[i%10]
    ans+=a[i]
for i in range(100,1000):
    if i%100==0:
        ans+=a[i//100]+a[100]
    else:
        ans+=a[i//100]+a[100]+3+a[i%100]
ans+=a[1]+a[1000]
print(ans)