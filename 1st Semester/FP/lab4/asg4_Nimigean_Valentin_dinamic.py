
def valid(n,mtx,i ,j ,b):
    if i> n - 1 or i < 0 :
        return 0
    if j > n - 1 or j < 0:
        return 0
    if abs(mtx[i][j]-b )!=1 :
        return 0

    return 1


def naive(n,mtx, i, j, b):
    maxim=1
    i1=i
    j1=j+1
    if valid(n,mtx,i1,j1,mtx[i][j]):
        maxim1=1+naive(n,mtx,i1,j1,mtx[i][j])
        maxim=max(maxim1,maxim)
    i2=i+1
    j2=j
    if valid(n,mtx,i2,j2,mtx[i][j]):
        maxim1=1+naive(n,mtx,i2,j2,mtx[i][j])
        maxim= max(maxim1, maxim)
    return maxim




def path ( maxii , maxij , mtx1):
    if maxii<0 or maxij< 0:
        return  " "
    print(maxii," ",maxij)
    if mtx1[maxii][maxij]== mtx1[maxii-1][maxij]+1:
        path (maxii-1,maxij,mtx1)
    elif  mtx1[maxii][maxij]== mtx1[maxii][maxij-1]+1:
        path (maxii,maxij-1,mtx1)
def print1 (maxi,maxii,maxij,mtx1):
    print("the maximum lenght is: ", maxi)
    print("the path is:")
    path (maxii,maxij,mtx1)

def dinamic (n,mtx):
    maxi = 0
    mtx1=[]
    a=[]
    for i in range (0,n):
        a.append(1)
    mtx1.append(a)
    for i in range(1,n):
        a=[]
        for j in range (0,n):
            a.append(0)
        mtx1.append(a)

    for i in range (0,n):
        mtx1[0][i]=1
    for i in range (0,n):
        for j in range (0,n):
            if i == 0 and j==0:
                mtx1[i][j]=1
            else:
                if abs(mtx[i][j] - mtx[i - 1][j]) == 1 and mtx1[i - 1][j] >=mtx1[i][j]and mtx1[i-1][j]!=0:
                    mtx1[i][j] = mtx1[i - 1][j] + 1
                    print (mtx1)
                if abs(mtx[i][j] - mtx[i][j - 1]) == 1 and mtx1[i][j - 1] >=mtx1[i][j]and mtx1[i][j-1]!=0:
                    mtx1[i][j] = mtx1[i][j - 1] + 1
                    print (mtx1)
                if mtx1[i][j] > maxi:
                    maxi = mtx1[i][j]
                    maxii = i
                    maxij = j

    print(mtx1)
    print1(maxi,maxii,maxij,mtx1)

#def generate (n):
    #mtx=[]
    #for i in range(0,n):
        #a=[]
        #for j in range (0,n):
            #a.append(int(input()))
        #mtx.append(a)
    #(dinamic(n,mtx))
    #print(mtx)



def menu():
    p=int(input("choose between a naive algorithm (1) and a dynamic algorithm(2): "))
    # generate(int(input("please input the size of the matrix:")))
    n=5
    #generate(n)
    mtx=[
        [1,1,2,3,4],
        [1,2,1,1,1],
        [3,3,4,7,0],
        [4,4,5,6,7],
        [5,6,7,1,8]
    ]

    if p==2:
        dinamic(n,mtx)
        menu()
    if  p==1:
        m=0
        for k in range(0,n):
            if(naive(n,mtx,0,k,0)>m):
                m= naive(n,mtx,0,k,0)
        print("the maximum lenght is:",m)
        menu()
    if p>2:
        menu()

menu()
