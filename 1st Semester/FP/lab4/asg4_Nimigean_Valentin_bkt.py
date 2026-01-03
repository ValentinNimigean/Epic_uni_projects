def valid (v,x):
    for i in range (0,len(v)-1):
        if v[i]==x:
            return 0
    return 1
def valid1 (v,k,m):
    if k==0:
        return 1
    elif abs(v[k]-v[k-1])>=m:
        return  1
    return 0




def bkp1 (v,n,m) :

    if len(v)==n:
        print(v)

    else:
        v.append(0)
        for i in range (0,n):
            v[-1]=i

            if valid(v,i):

                if len(v)==1:
                    bkp1(v[:], n, m)
                elif abs(v[len(v)-1]-v[len(v)-2])>=m:
                    bkp1(v[:],n,m)

def bkp2(n,m):
    k=0
    ok=0
    v=[]
    v.append(-1)
    while k>=0:
        if v[k]==n-1:
            del(v[k])
            k=k-1
        else:
            v[k]=v[k]+1
            if k<n-1 and valid(v,v[k]) and valid1 (v,k,m):
                k=k+1
                v.append(-1)
            elif k==n-1  and valid(v,v[k]) and valid1(v,k,m) :
                print(v)
                ok=ok+1
    if ok==0:
        print("there are no solutions")

    menu()



def menu():
    n=int(input("please input the value of n:"))
    m=int(input("please input the value of m:"))
    x=int(input("Choose between the recursive sorting algorithm (type 1) and the iterrative algorithm (type 2):"))
    if x==1:
        ok=0
        bkp1([],n,m,)

        menu()
    else:
        bkp2(n,m)
        menu()


menu()
