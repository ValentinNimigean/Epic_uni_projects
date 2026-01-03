# Solve the problem from the first set here
# problem 2
def isprime(a): #algorithm used to determine wether a number is prime or not
    if a==1:
        return 0
    if a==2:
        return 1
    if a%2==0:
        return 0
    for i in range (3,a,2):
        if a%i==0:
            return 0
    return 1

def numbers(b): #algorithm used to decompose a number n into two prime numbers (if possible) 
    ok=0
    for j in range (2,b):
        if isprime(j)==1:
            if isprime(b-j)==1:
                if ok==0:
                    print("the number can be decomposed into the following prime numbers:")
                    print(j)
                    print(b-j)
                    ok=1
    if ok==0:
        print("the number cannot be decomposed in prime numbers.")
    return " "
print (numbers(int(input("write a natural number:"))))
#Nimigean_Valentin
