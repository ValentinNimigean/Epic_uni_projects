import random
import math
def generate(k): #function to generate a list with random values
    l=[]
    for i in range(0,k):
        a=random.randint(1,100);
        l.append(a)
    return l
def stooge(list,i,j,step,k): #function that sorts a list using the stooge sort algorithm
    if k%step==0:
        print(list)
    if list[i]>list[j]:
        x=list[i]
        list[i]=list[j]
        list[j]=x
    if (j-i+1)>2:
        aux=(int)((j-i+1)/3)
        stooge(list,i,(j-aux),step,k+1) #sorts the first two thirds of the list 
        stooge(list,(i+aux),j,step,k+1) #sorts the last two thirds of the list 
        stooge(list,i,(j-aux),step,k+1) #sorts the first two thirds of the list 

def insertion(list,step): #function that sorts a list using the insert sort algorithm
    n=len(list)
    k=1
    for i in range(1,n):
        a=list[i]
        j=i-1
        while j>=0 and a<list[j]: 
            list[j+1]=list[j]
            j=j-1
        list[j+1]=a
        k=k+1
        if k%step==0:
            print(list)
    print("")
    print(list)
def menu(l):
    print("choose one of the 4 commands:")
    print(" ")
    print("1-generate a list of random numbers")
    print("2-put the list through the input sort algorithm")
    print("3-put the list through the stooge sort algorithm")
    print("4-exit the program")
    a=int(input())
    if l==0:
        if a==2:
            print ("Please generate a list before using a sorting algorithm")
            print ("")
            menu(l)
        if a==3:
            print ("Please generate a list before using a sorting algorithm")
            print("")
            menu(l)  
    n=0
    if a==1:
        n=int(input("please provide the lenght of the list:"))
        l=generate(n)
        print("the generated list is:")
        print(l)
        print(" ")

        menu(l)
    if a==2:
        l1=l[:]
        step1=int(input("please input the value for 'step':"))
        insertion(l1,step1)
        menu(l)
    if a==3:
        l2=l[:]
        step2=int(input("please input the value for 'step':"))
        print (step2)
        k=1
        n=len(l2)
        stooge(l2,0,n-1,step2,k)
        print(" ")
        print(l2)
        menu(l)
    if a==4:
        return " "
menu(0)
#Nimigean_Valentin
