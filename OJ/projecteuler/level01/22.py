import fileinput,string
f=open("p022_names.txt","r")
s=f.readline()
info=s.split(',')
info.sort()
res=0
for i in range(0,len(info)):
    addsum=0
    for j in range(0,len(info[i])):
        if info[i][j]>='A' and info[i][j] <= 'Z':
            addsum+=ord(info[i][j])-ord('A')+1
    addsum*=(i+1)
    res+=addsum
print (res)