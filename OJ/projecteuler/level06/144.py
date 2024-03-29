# 就纯椭圆的解析几何题
# while死循环每次求一下反射光线和椭圆焦点然后判断位置就行了
# https://pe.metaquant.org/pe144.html
# ans = 354

def next_point(x0,y0,x1,y1):
    i = (y1-y0)/(x1-x0)
    n = y1/(4*x1)
    r = (-i+2*n+i*n**2)/(1+2*i*n-n**2)
    m = y1-r*x1
    x_new = (-2*r*m)/(4+r**2)-x1
    y_new = r * x_new + m
    return x_new,y_new

def main():
    n = 1
    x0,y0,x1,y1 = 0,10.1,1.4,-9.6
    while True:
        x_new,y_new = next_point(x0,y0,x1,y1)
        if abs(x_new)<=0.01 and y_new>0:
            return n
        else:
            x0,y0,x1,y1 = x1,y1,x_new,y_new
            n += 1

if __name__ == '__main__':
    print(main())