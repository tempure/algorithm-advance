year,month,day,week,ans,f=1901,1,1,1,0,0
d=[0,31,28,31,30,31,30,31,31,30,31,30,31]

# https://blog.csdn.net/charlie_pyc/article/details/23852419

def days(x,y): #第y年的x月有多少天
    if x==2:
        if y%400==0 or y%4==0 and y%100!=0:
            return 29
        else:
            return 28
    else:
        return d[x]
while 1:
    if year==2000 and month==12 and day==31:
        break
    day+=1
    week+=1
    if week==8:
        week=1
    if day>days(month,year):
        day=1
        month+=1
        if month>12:
            month=1
            year+=1
    # if year==1901 and month==1 and day==1:
        # f=1
    if day==1 and week==7:
        ans+=1
print(ans-1)