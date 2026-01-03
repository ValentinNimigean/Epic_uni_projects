# Solve the problem from the second set here
# problem 10
def palin(a): #simple algorithm that reverses the order of numbers
    s=0
    while a>0:
        s=s*10+a%10
        a=a//10
    return s

print("the palindrome of th number is:",palin(int(input("write a natural number:"))))
#Nimigean_Valentin
