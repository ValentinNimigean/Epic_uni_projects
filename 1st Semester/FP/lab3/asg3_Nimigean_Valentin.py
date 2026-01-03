import random
import timeit
def generate3(k):
    l=[]
    for i in range(0,k):
        a=random.randint(1,100)
        l.append(a)
    return l
def generate1(k):
    l=[]
    for i in range(0,k):
        a=i
        l.append(a)
    return l
def generate2(k):
    l=[]
    for i in range(0,k):
        a=k-i
        l.append(a)
    return l
def stooge(list,i,j):
    if list[i]>list[j]:
        x=list[i]
        list[i]=list[j]
        list[j]=x
    if (j-i+1)>2:
        aux=(int)((j-i+1)/3)
        stooge(list,i,(j-aux))
        stooge(list,(i+aux),j)
        stooge(list,i,(j-aux))

def insertion(list):
    n = len(list)
    for i in range(1,n):
        a=list[i]
        j=i-1
        while j>=0 and a<list[j]:
            list[j+1]=list[j]
            j=j-1
        list[j+1]=a



def intest(p,k):
    for q in range (0,5):
        if q!=0:
            k=k*2
        if p==1:
            list=generate1(k)
        if p == 2:
            list = generate2(k)
        if p == 3:
            list = generate3(k)

        t = timeit.timeit(lambda: insertion(list),
                          number=10)
        print("list lenght ",k," execution time: ",t,"seconds")
def stgtest(p,k):
    for q in range (0,5):
        if q!=0:
            k=k*2
        if p==1:
            list=generate3(k)

        #print("list lenght ", k, " execution time: ", timeit.timeit("""def stooge(list,i,j):
           # if i>j:
            #    return
            #if list[i]>list[j]:
             #   x=list[i]
              #  list[i]=list[j]
               # list[j]=x
            #if (j-i+1)>2:
             #   aux=(int)((j-i+1)/3)
              # stooge(list,(i+aux),j) 
               # stooge(list,i,(j-aux)) 
       # """,
#
 #                                                                       globals=globals()))
#
        t = timeit.timeit(lambda: stooge(list,0,k-1),
                       number=1)
        print("list lenght ",k," execution time: ",t,"seconds")




def menu():
    print("choose one of the 3 commands:")
    print(" ")
    print("1-test the time efficiency of the insertion sort algorithm")
    print("2-test the time efficiency of the stooge sort algorithm")
    print("3-exit the program")
    a=int(input())

    if a==1:
        print("type 1 for best case scenario:")
        print("type 2 for worst case scenario:")
        print("type 3 for average scenario:")
        p=int(input())
        print("give a lenght to the initial test list:")
        n=int(input())
        intest(p,n)
        menu()
    if a==2:
        print("type 1 for average scenario (stooge sort doesn't have best/worst case scenario):")
        p=int(input())
        print("give a lenght to the initial test list:")
        n=int(input())
        stgtest(p,n)
        menu()
    if a==3:
        return " "
menu()
#Nimigean_Valentin
