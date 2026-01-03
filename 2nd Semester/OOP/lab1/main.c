#include <stdio.h>

#include <stdlib.h>

/*
 * Function: generate_pascal_triangle
 * ----------------------------
 * generates the number at the given position in the pascal triangle
 *
 * n: The row of the pascal triangle.
 * k: The position in the row.
 *
 * returns: The number at the given position in the pascal triangle.
 */

int generate_pascal_triangle(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    return generate_pascal_triangle(n - 1, k - 1) + generate_pascal_triangle(n - 1, k);
}
/*
 * Function: prime
 * ----------------------------
 * checks if a number is prime
 *
 * n: The number to be checked.
 *
 * returns: 1 if the number is prime, 0 otherwise.
 */

int prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/*
 * Function: print_pascal_triangle
 * ----------------------------
 * prints the pascal triangle
 *
 * n: The number of rows of the pascal triangle.
 *
 * returns: void
 */


void print_pascal_triangle(int n) {
    for (int i = 0; i < n; i++) {
        printf("%*s",(n - i), ""   );
        for (int j = 0; j <= i; j++) {
            printf("%d ", generate_pascal_triangle(i, j));
        }
        printf("\n");
    }
}

/*
 * Function: sequence
 * ----------------------------
 * prints the longest contiguous sequence of prime numbers
 *
 * a: The vector of numbers.
 * n: The number of elements in the vector.
 *
 * returns: void
 */

void sequence(int a[], int n, int **vector_final,int *lenght_final) {
    int start = 0, end=0, length= 0, start_dinamic = 0,maximum_length=0;
    for (int i = 0; i < n; i++) {
        if (prime(a[i])) {
            if (length == 0) {
                start_dinamic= i;
            }
            length++;

            if (length > maximum_length) {
                maximum_length = length;
                start = start_dinamic;
                end = i;
            }
        } else {
            length = 0;
        }
    }
    *vector_final=  malloc(maximum_length * sizeof(int));
    *lenght_final=maximum_length;

    for (int i = start; i <= end; i++) {
        (*vector_final)[i-start] = a[i];

    }



}
/*
 * Function: main
 * ----------------------------
 * The main function of the program
 *
 * returns: 0
 */
int main() {
    int n, a[1001],ok=0,k;
    int lenght;
    int* final_vector;
    printf("Welcome to my epic c program >:3 \n");
    printf("1. Input a vector of n numbers\n");
    printf("2. Pascal Triangle \n");
    printf("3. Contiguous sequence of prime numbers \n");
    printf("4. Exit \n");
    while (1) {
        printf("Enter an option:");
        int option=0;
        scanf("%d", &option);

        if (option == 1) {
            printf("Enter the number of elements: ");
            scanf("%d", &n);
            printf("Enter the elements: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &a[i]);
            }
            ok=1;
        }
        else if (option == 2) {
            printf("Enter the number of rows: ");
            scanf("%d", &k);
            printf("Pascal Triangle: \n");
            print_pascal_triangle(k);
        } else if (option == 3) {
            if (ok == 0)
                printf("You need to input a vector first! \n");
            else {
                printf("The longest contiguous sequence of prime numbers is: ");
                sequence(a, n, &final_vector, &lenght);
                for (int i = 0; i < lenght; i++)
                    printf("%d ", final_vector[i]);


            }
            printf("\n");

        }

        else if (option == 4) {
            printf("Goodbye! \n");
            return 0;
        }
        else if (option < 1 || option > 4){
            printf("Invalid option! \n");


        }
    }
}



