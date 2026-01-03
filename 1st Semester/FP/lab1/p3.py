# Solve the problem from the third set here
# problem 14
def prime(x): #algorithm used to determine wether a number is prime or composed (also used in p1)(1 is an exception)
    if x==1:
        return 1
    if x==2:
        return 1
    if x%2==0:
        return 0
    for i in range (3,x//2,2):
        if x%i==0:
            return 0
    return 1

def factors(b): #algorithm used to dinamically generate the sequence
    if b<=0:
        return 1
    k=0
    while b>0:
        k=k+1
        p=k

        if prime(p)==1:
            b=b-1
            #print(p)
            if b<=0:
                return p
        else:
            for i in range (2,p):
                if p%i==0:
                    b=b-i
                    #for l in range (1,i+1):
                       #print(i)
                    for j in range (1,i+1):

                        if b<=0:
                            return i
                        while p%i==0:
                            p=p//i

print("the n-th element of the sequence is:",factors(int(input("write a natural number n:"))))
#Nimigean_Valentin
