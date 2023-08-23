/*
performing addition in custom data type
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check_null(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory not allocated");
        exit(EXIT_FAILURE);
    }
}

typedef struct
{
    int *digits;
    int size;
} bigInt;

// assigning space for array in memory
void bigInt_init(bigInt *n, int size)
{
    size = size + 1;
    n->digits = (int *)malloc(size * sizeof(int));
    n->size = size;
}

void bigInt_free(bigInt *n)
{
    free(n->digits);
    n->digits = NULL;
    n->size = 0;
}

void bigInt_assign_values(bigInt *n, char *input_str)
{
    n->digits[0] = 0;
    for (int i = 0; i < strlen(input_str) - 1; i++)
    {
        n->digits[i+1] = (int)input_str[i] - '0';
    }
}

void bigInt_print(bigInt *n)
{
    int start = 0;
    if(n->digits[0] == 0)
    {
        start = 1;
    }
    for (int i = start; i < n->size; i++)
    {
        printf("%d", n->digits[i]);
    }
}

int bigInt_compare(bigInt *n, bigInt *n2)
{
    /*
        This function if filling the free space of number which is shorter in length than another number
    */
    if (n->size < n2->size)
    {
        int temp_index = n->size;
        n->digits = (int *)realloc(n->digits, n2->size * sizeof(int));
        if (n->digits == NULL)
        {
            printf("Memory can't be allocated");
            exit(EXIT_FAILURE);
        }
        n->size = n2->size;

        for (int i = n->size; i >= 0; i--)
        {
            if (temp_index >= 0)
            {
                n->digits[i] = n->digits[temp_index];
            }
            else
            {
                n->digits[i] = 0;
            }
            temp_index--;
        }

        return -1; // most significant number of 2nd is greater than 1st's
    }
    else if (n->size > n2->size)
    {
        int temp_index = n2->size;
        n2->digits = (int *)realloc(n2->digits, n->size * sizeof(int));
        if (n2->digits == NULL)
        {
            printf("Memory can't be allocated");
            exit(EXIT_FAILURE);
        }
        n2->size = n->size;

        for (int i = n2->size; i >= 0; i--)
        {
            if (temp_index >= 0)
            {
                n2->digits[i] = n2->digits[temp_index];
            }
            else
            {
                n2->digits[i] = 0;
            }
            temp_index--;
        }

        return 1; // most significant number of 1st is greater than 2nd's
    }
}

void bigInt_addition(bigInt *n, bigInt *n2)
{
    bigInt_compare(n, n2);

    int carry = 0;
    int sum;
    int j = n->size - 1;

    for (int i = n2->size - 1; i >= 0; i--)
    {
        sum = n->digits[j] + n2->digits[i] + carry;
        if (sum > 9)
        {
            n->digits[j] = sum - 10;
            carry = sum / 10;
        }
        else
        {
            n->digits[j] = sum;
            carry = 0;
        }
        j--;
    }
}

char *input(char *input_str, int n)
{
    fgets(input_str, n, stdin); // buffer overflow prevention and also getting input

    /*
    checking if lenght of inputted string is equals to the predefine size or not, if yes then checking if 2nd
    last character is new line or not if not then assuming still some characters left to read so assigning memory
    of double sized and getitng rest of the values form input string, keep doing this until 9th index contains \n
    */
    while (strlen(input_str) == n - 1 && input_str[n - 2] != '\n') // checking if input_str is enough or not
    {
        // reallocate memory with twice the size
        n *= 2;
        input_str = (char *)realloc(input_str, n * sizeof(char));
        check_null(input_str);

        // read rest of the input
        fgets(input_str + n / 2 - 1, n / 2 + 1, stdin);
    }

    // freeing the unused memory
    input_str = (char *)realloc(input_str, strlen(input_str) + 1);
    check_null(input_str);

    return input_str;
}

void main()
{
    bigInt num, num2;
    char *input_str;
    int n = 10;

    // initializing 10 bytes of memory for input
    input_str = (char *)malloc(n * sizeof(char));
    check_null(input_str);

    // storing pointer of inputted array in input_str
    printf("Enter your first number: ");
    input_str = input(input_str, n);

    // initializing bigInt with size n and assigning input_str values to it
    n = strlen(input_str) - 1;
    bigInt_init(&num, n);
    bigInt_assign_values(&num, input_str);

    // freeing the previously created input_str for further inputs
    free(input_str);
    n = 10;

    // reassigning memory for input_str
    input_str = (char *)malloc(n * sizeof(char));
    check_null(input_str);

    // getting input for 2nd variable and assigning pointer to input_str
    printf("Enter your second number: ");
    input_str = input(input_str, n);

    // initializing and assigning values to 2nd variable of bigInt
    n = strlen(input_str) - 1;
    bigInt_init(&num2, n);
    bigInt_assign_values(&num2, input_str);

    // freeing the input char type array
    free(input_str);

    // performing rest of the operations
    bigInt_addition(&num, &num2);
    printf("The sum is:- ");
    bigInt_print(&num);
    bigInt_free(&num);
    bigInt_free(&num2);
}
