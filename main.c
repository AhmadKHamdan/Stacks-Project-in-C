/* NAME: AHMAD HAMDAN
ID: 1210241
SECTION: 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void readFromFile();
void printToFile();
struct node *createStack();
void pop(struct node *S);
int top(struct node *Stack);
void push(int X, struct node *Stack);
bool isEmpty(struct node *Stack);
void makeEmpty(struct node *Stack);
void disposeStack(struct node *Stack);
void printStack(int index, int mode);
void reverseStack(int index);
void printPrefixStack(int index, int mode);
void reversePrefixStack(int index); 
void printEquations();
void checkEquations();
void printInvalid();
void printPrefixEquations();
void infixToPrefix(int index);
void printResults();
void evaluatePrefix(int index, int mode);
bool checkValidity(int index, int mode);
bool checkPara(int index, int mode);

struct node
{
    int value;
    struct node *next;
};

int size = 0,
    flagOpPrint = 0;                // Creating global variables which were needed
FILE *fptr, *outFile;               // Creating a global variable to the file
struct node **Array, **prefixArray; // Creating a dynamic sized array

int main()
{
    // Creating the main menu of the program
    int input = 0;
    while (input != 8)
    {
        printf("\n1- Read from the file input\n");
        printf("2- Print all equations\n");
        printf("3- Check the validity of the equations\n");
        printf("4- Convert from infix to prefix\n");
        printf("5- Evaluate the prefix expressions\n");
        printf("6- Print all invalid equations\n");
        printf("7- Print all information to a file\n");
        printf("8- Exit\n");
        printf(".......................\n");
        printf("Please choose an operation: ");
        scanf("%d", &input);
        if (input == 1)
            readFromFile();
        if (input == 8)
        {
            printf("\n\tGood Bye <3\n\n");
            break;
        }
        // Checking if the user read from the file
        if (size)
        {
            if (input == 2)
                printEquations();
            if (input == 3)
                checkEquations();
            if (input == 4)
                printPrefixEquations();
            if (input == 5)
                printResults();
            if (input == 6)
                printInvalid();
            if (input == 7)
                printToFile();
        }
        else
            printf("\nUnavailable! Zero numbers read from the files.\n");
    }
    return 0;
}

// Function to read from the file
void readFromFile()
{
    // Code to get the name of the input file
    int temp, i = 0;
    char fname[15], chr; // Creating an array of chars (String) for the name of the file
    printf("Enter the name of the input file: ");
    scanf("%d", NULL);
    gets(fname); // Get the name of the file
    fptr = fopen(fname, "r");

    // Checks if the file was found properly
    while (fptr == NULL)
    {
        printf("\nError. Unable to open the file for reading\n");
        printf("Enter the name of the input file: ");
        scanf("%d", NULL);
        gets(fname); // Get the name of the file

        // Opens the input file to read
        fptr = fopen(fname, "r");
    }

    // Calculating how many numbers is in the file
    chr = getc(fptr);
    while (chr != EOF)
    {
        // Count whenever new line is encountered
        if (chr == '\n')
        {
            size++;
        }
        // take next character from file.
        chr = getc(fptr);
    }
    size++;

    // Allocating the memory required for the "size" numbered pointers
    Array = (struct node **)malloc(size * sizeof(struct node *));
    prefixArray = (struct node **)malloc(size * sizeof(struct node *));

    // Clearing the linked list and allocating the memory required
    struct node *mainStack = createStack(mainStack);

    // Rereading the file
    rewind(fptr);

    // Reading the entire file
    while (temp != EOF)
    {
        // Creating the head node and initializing it
        temp = fgetc(fptr);

        if (temp != 45 && temp != 10 && temp != EOF)
        {
            // Turning characters to integers
            push(temp, mainStack);
        }

        // 10 = \n to check if we reached a new line
        else if (temp == 10)
        {
            Array[i] = mainStack;
            i++;
            mainStack = createStack(mainStack);
        }

        // checks for negative signsF
        else if (temp == 45)
        {
            push(temp, mainStack);
        }
    }

    // Once it reaches the end of the file
    if (temp == EOF)
    {
        Array[i] = mainStack;
        i++;
    }

    // Make sure the numbers have been read correctly
    if (i > 0)
    {
        printf("\nThe numbers have been read.\n");
    }
    else
    {
        printf("The operation was not successful.\n");
    }

    // Closing the file at the end
    fclose(fptr);
}

// Function to print the results to a file
void printToFile()
{
    outFile = fopen("output.txt", "w");

    fprintf(outFile, "All results:\n");
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        fprintf(outFile, "\n%c. Equation No.%d -> ", ('a' + j++), (j + 1));
        printStack(i, 1);
        infixToPrefix(i);
        reverseStack(i);
        if (checkValidity(i, 0))
        {
            fprintf(outFile, "\n\nThe equation is valid.\n");
            fprintf(outFile, "\nThe equation in prefix form -> ");
            printPrefixStack(i, 1);
            fprintf(outFile, "\n\nThe result = ");
            evaluatePrefix(i, 1);
            fprintf(outFile, "\n.............\n");
        }
        else
        {
            fprintf(outFile, "\n\nThe equation is not valid.");
            fprintf(outFile, "\n.............\n");
        }
    }
    fprintf(outFile, "\n");
    printf("Results have been printed.\n");
    fclose(outFile);
}

// Function to initialize the stack
struct node *createStack()
{
    struct node *Stack;
    Stack = (struct node *)malloc(sizeof(struct node));
    if (Stack == NULL)
    {
        printf("Out of space !");
    }
    Stack->next = NULL;
    makeEmpty(Stack);
    return Stack;
}

// Function to pop the last in node
void pop(struct node *Stack)
{
    struct node *firstCell;
    if (isEmpty(Stack))
    {
        printf("Empty stack");
    }
    else
    {
        firstCell = Stack->next;
        Stack->next = Stack->next->next;
        free(firstCell);
    }
}

// Function to return the value of the top node
int top(struct node *Stack)
{
    if (!isEmpty(Stack))
    {
        return Stack->next->value;
    }
    return 0;
}

// Function to insert a node
void push(int X, struct node *Stack)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        printf("Out of space !");
    }
    else
    {
        temp->value = X;
        temp->next = Stack->next;
        Stack->next = temp;
    }
}

// Function to check if the stack is empty
bool isEmpty(struct node *Stack)
{
    return Stack->next == NULL;
}

// Function to print the stack
void printStack(int index, int mode)
{
    if (!isEmpty(Array[index]))
    {
        int temp = top(Array[index]);
        pop(Array[index]);
        printStack(index, mode);

        if (!(temp >= 42 && temp <= 47) && temp != 94)
        {
            if (mode)
                fprintf(outFile, "%c", temp);
            else
                printf("%c", temp);
            flagOpPrint = 0;
        }
        else
        {
            if (flagOpPrint)
            {
                if (mode)
                    fprintf(outFile, "%c", temp);
                else
                    printf("%c", temp);
                flagOpPrint = 0;
            }
            else
            {
                if (mode)
                    fprintf(outFile, " %c ", temp);
                else
                    printf(" %c ", temp);
                flagOpPrint = 1;
            }
        }

        push(temp, Array[index]);
    }
}

// Function to reverse a stack
void reverseStack(int index)
{
    struct node *temp = createStack(temp);
    while (!isEmpty(Array[index]))
    {
        push(top(Array[index]), temp);
        pop(Array[index]);
    }
    Array[index] = temp;
}

// Function to print the stack
void printPrefixStack(int index, int mode)
{
    if (!isEmpty(prefixArray[index]))
    {
        int temp = top(prefixArray[index]);
        pop(prefixArray[index]);
        printPrefixStack(index, mode);
        if (mode)
            fprintf(outFile, "%c", temp);
        else
            printf("%c", temp);
        push(temp, prefixArray[index]);
    }
}

// Function to reverse a stack
void reversePrefixStack(int index)
{
    struct node *temp = createStack(temp);
    while (!isEmpty(prefixArray[index]))
    {
        push(top(prefixArray[index]), temp);
        pop(prefixArray[index]);
    }
    prefixArray[index] = temp;
}

// Function to empty out the stack
void makeEmpty(struct node *Stack)
{
    if (Stack == NULL)
    {
        printf("Out of space !");
    }
    else
    {
        while (!isEmpty(Stack))
        {
            pop(Stack);
        }
    }
}

// Function to get rid of the stack
void disposeStack(struct node *Stack)
{
    // Emptying the stack
    makeEmpty(Stack);

    // Freeing the top of the stack
    free(Stack);
}

// Function to print all equations
void printEquations()
{
    printf("\nAll equations:\n");
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        printf("\n%c. Equation No.%d -> ", ('a' + j++), (j + 1));
        printStack(i, 0);
    }
    printf("\n");
}

// Function to print which equations are valid and which are not
void checkEquations()
{
    for (int i = 0; i < size; i++)
    {
        reverseStack(i);
        printf("\n%c. Equation No.%d -> ", ('a' + i), (i + 1));
        checkValidity(i, 1);
    }
    printf("\n");
}

// Function to print every invalid equation
void printInvalid()
{
    printf("\nAll invalid equations:\n");
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        reverseStack(i);
        if (!checkValidity(i, 0))
        {
            printf("\n%c. Equation No.%d -> ", ('a' + j++), (j + 1));
            printStack(i, 0);
        }
    }
    printf("\n");
}

// Function to print the prefix expression for the valid equations
void printPrefixEquations()
{
    printf("\nPrefix for all valid equations:\n");
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        infixToPrefix(i);
        reverseStack(i);
        if (checkValidity(i, 0))
        {
            printf("\n%c. Equation No.%d -> ", ('a' + j++), (j + 1));
            printPrefixStack(i, 0);
        }
    }
    printf("\n");
}

// Function to convert an equation from infix to prefix
void infixToPrefix(int index)
{
    // We need a stack to save the operators
    struct node *assistance = createStack(assistance);

    // We need a stack to save the equation in prefix form
    struct node *result = createStack(result);

    // We need a stack to return the original equation
    struct node *original = createStack(original);

    // Setting a flag for the negative sign
    int negativeSign = 0;

    while (!isEmpty(Array[index]))
    {

        // for numbers
        if (top(Array[index]) >= 48 && top(Array[index]) <= 57)
        {
            push(top(Array[index]), result);
            negativeSign = 0;
        }
        else
        {
            push(32, result);
            // ] and ) case (always goes in)
            if (top(Array[index]) == 41 || top(Array[index]) == 93)
                push(top(Array[index]), assistance);

            // ( case (print everything till the closing bracket)
            else if (top(Array[index]) == 40)
            {
                while (!isEmpty(assistance))
                {
                    if (top(assistance) == 41)
                    {
                        pop(assistance);
                        break;
                    }
                    push(top(assistance), result);
                    pop(assistance);
                }
            }

            // [ case (print everything till the closing bracket)
            else if (top(Array[index]) == 91)
            {

                while (!isEmpty(assistance))
                {
                    if (top(assistance) == 93)
                    {
                        pop(assistance);
                        break;
                    }
                    push(top(assistance), result);
                    pop(assistance);
                }
            }

            // + case
            if (top(Array[index]) == 43 || top(Array[index]) == 45)
            {
                while (!isEmpty(assistance) && ((top(assistance) == 47) || (top(assistance) == 42) || top(assistance) == 94))
                {
                    push(top(assistance), result);
                    push(32, result);
                    pop(assistance);
                }
                if (top(Array[index]) == 45)
                {
                    negativeSign = 1;
                }
                push(top(Array[index]), assistance);
            }

            // * and / cases
            if (top(Array[index]) == 47 || top(Array[index]) == 42)
            {
                while (!isEmpty(assistance) && top(assistance) == 94)
                {
                    push(32, result);
                    push(top(assistance), result);
                    pop(assistance);
                }
                push(top(Array[index]), assistance);
            }

            // ^ case
            if (top(Array[index]) == 94)
            {
                push(top(Array[index]), assistance);
            }
        }

        push(top(Array[index]), original);
        pop(Array[index]);

        // - case acts different
        if (negativeSign && (top(Array[index]) < 48 || top(Array[index]) > 57) && !(top(Array[index]) == 41 || top(Array[index]) == 93))
        {
            pop(assistance);
            if (top(result) == 94 || top(result) == 42 || top(result) == 47 || top(result) == 43)
            {
                int y = top(result);
                pop(result);
                pop(result);
                pop(result);
                push(45, result);
                push(32, result);
                push(y, result);
            }
            else
            {
                if (top(Array[index]) == 41 || top(Array[index]) == 93)
                {
                    push(32, result);
                }
                pop(result);
                push(45, result);
            }
            negativeSign = 0;
        }
    }
    while (!isEmpty(assistance))
    {
        push(32, result);
        push(top(assistance), result);
        pop(assistance);
    }

    // Setting the prefixArray[index] to the final result prefix form equation
    prefixArray[index] = result;

    // Reversing it to get the prefix form and not the postfix form
    reversePrefixStack(index);

    // Setting Array[index] to the original equation once again
    Array[index] = original;
    reverseStack(index);

    // Freeing the unwanted stacks
    disposeStack(result);
    disposeStack(assistance);
    disposeStack(original);
}

// Function to print the result of the prefix equations
void printResults()
{
    printf("\nPrefix for all valid equations and their results:\n");
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        infixToPrefix(i);
        reverseStack(i);
        if (checkValidity(i, 0))
        {
            printf("\n%c. Equation No.%d -> ", ('a' + j++), (j + 1));
            printPrefixStack(i, 0);
            printf(" = ");
            evaluatePrefix(i, 0);
        }
    }
    printf("\n");
}

// Function to evaluate the prefix of a stack
void evaluatePrefix(int index, int mode)
{
    // We need to find the prefix of the equation
    infixToPrefix(index);

    // Creating a temporay stack for the evaluation process
    struct node *assistance;
    assistance = createStack(assistance);

    int digits = 0, power = 1, negativePower = 0;

    while (!isEmpty(prefixArray[index]))
    {
        // If it is a number
        if (top(prefixArray[index]) >= 48 && top(prefixArray[index]) <= 57)
        {
            digits = digits + ((top(prefixArray[index]) - '0') * power);
            power = power * 10;
            negativePower = 1;
        }
        else if (negativePower && top(prefixArray[index]) == 45)
        {
            digits = digits * -1;
        }
        else if (top(prefixArray[index]) == 32) // Space
        {
            if (digits != 0)
            {
                push(digits, assistance);
            }
            power = 1;
            digits = 0;
            negativePower = 0;
        }
        else // Operations
        {
            negativePower = 0;
            int n1 = top(assistance);
            pop(assistance);
            int n2 = top(assistance);
            pop(assistance);
            if (top(prefixArray[index]) == 42)
                push(n1 * n2, assistance);
            if (top(prefixArray[index]) == 43)
                push(n1 + n2, assistance);
            if (top(prefixArray[index]) == 45)
                push(n1 - n2, assistance);
            if (top(prefixArray[index]) == 47)
                push(n1 / n2, assistance);
            if (top(prefixArray[index]) == 94)
                push(pow(n1, n2), assistance);
        }
        pop(prefixArray[index]);
    }
    if (mode)
        fprintf(outFile, "%d", top(assistance));
    else
        printf("%d", top(assistance));
}

// Checking if an equations is valid or invalid
bool checkValidity(int index, int mode)
{
    // The mode sent to this function decides whether the function should print the validity or not
    int flagNum = 0, flagOp = 0, flagPara = 0;
    struct node *temporary = createStack(temporary);

    // Checking if the parentheses are correct
    if (!checkPara(index, mode))
    {
        reverseStack(index);
        return false;
    }

    // Checking if the first character is an operator
    if (top(Array[index]) >= 42 && top(Array[index]) <= 47 && top(Array[index]) != 45)
    {
        if (mode)
        {
            printf("Invalid: An operator %c at the start", top(Array[index]));
        }
        while (!isEmpty(temporary))
        {
            push(top(temporary), Array[index]);
            pop(temporary);
        }

        reverseStack(index);
        return false;
    }

    while (!isEmpty(Array[index]))
    {
        if (top(Array[index]) >= 48 && top(Array[index]) <= 57) // NUMBERS
        {
            // Checking if there is a number right after a parenthesis
            if (flagPara && (top(temporary) == 41 || top(temporary) == 93))
            {
                if (mode)
                {
                    printf("Invalid: No operator between parenthesis %c and %c", top(temporary), top(Array[index]));
                }
                while (!isEmpty(temporary))
                {
                    push(top(temporary), Array[index]);
                    pop(temporary);
                }

                reverseStack(index);
                return false;
            }
            flagNum = 1;
            flagOp = 0;
            flagPara = 0;
        }

        if ((top(Array[index]) >= 42 && top(Array[index]) <= 47) || top(Array[index]) == 94) // OPERATIONS
        {
            // Checking if there are two operators right after each other
            if (flagOp && top(Array[index]) != 45)
            {
                if (mode)
                {
                    printf("Invalid: Two adjacent operators %c and %c", top(temporary), top(Array[index]));
                }
                while (!isEmpty(temporary))
                {
                    push(top(temporary), Array[index]);
                    pop(temporary);
                }

                reverseStack(index);
                return false;
            }
            flagNum = 0;
            flagOp = 1;
            flagPara = 0;
        }
        if (top(Array[index]) == 40 || top(Array[index]) == 41 || top(Array[index]) == 91 || top(Array[index]) == 93) // PARENTHESIS
        {
            if (flagPara)
            {
                if (((top(Array[index]) == 40 && top(temporary) == 41)) || ((top(Array[index]) == 91 && top(temporary) == 93)))
                {
                    if (mode)
                    {
                        printf("Invalid: No operator between parenthesis %c and parenthesis %c", top(temporary), top(Array[index]));
                    }
                    while (!isEmpty(temporary))
                    {
                        push(top(temporary), Array[index]);
                        pop(temporary);
                    }
                    reverseStack(index);
                    return false;
                }
            }
            if (flagNum && (top(Array[index]) == 40 || top(Array[index]) == 91))
            {
                if (mode)
                {
                    printf("Invalid: No operator between number %c and parenthesis %c", top(temporary), top(Array[index]));
                }
                while (!isEmpty(temporary))
                {
                    push(top(temporary), Array[index]);
                    pop(temporary);
                }
                reverseStack(index);

                return false;
            }
            if (flagOp && (top(Array[index]) == 41 || top(Array[index]) == 93))
            {
                if (mode)
                {
                    printf("Invalid: Operator %c and parenthesis %c are adjacent", top(temporary), top(Array[index]));
                }
                while (!isEmpty(temporary))
                {
                    push(top(temporary), Array[index]);
                    pop(temporary);
                }
                reverseStack(index);

                return false;
            }
            flagNum = 0;
            flagOp = 0;
            flagPara = 1;
        }
        push(top(Array[index]), temporary);
        pop(Array[index]);
    }

    // Checking if the equation ends with an operator
    if (flagOp)
    {
        if (mode)
        {
            printf("Invalid: An operator %c at the end", top(temporary));
        }
        push(top(Array[index]), temporary);
        pop(Array[index]);

        while (!isEmpty(temporary))
        {
            push(top(temporary), Array[index]);
            pop(temporary);
        }
        reverseStack(index);

        return false;
    }

    // Printing if valid
    if (mode)
    {
        printf("Valid");
    }

    // Getting back Array[index] back to its original state
    while (!isEmpty(temporary))
    {
        push(top(temporary), Array[index]);
        pop(temporary);
    }
    reverseStack(index);

    // Getting rid of the unwanted stacks
    disposeStack(temporary);

    return true;
}

// Function to check the validity of the parenthesis
bool checkPara(int index, int mode)
{
    struct node *par = createStack(par);
    struct node *temporary = createStack(temporary);
    int lol = 0;

    while (!isEmpty(Array[index]))
    {
        if (top(Array[index]) == '(' || top(Array[index]) == '[')
        {
            push(top(Array[index]), par);
        }
        else if (top(Array[index]) == ')' || top(Array[index]) == ']')
        {

            if (top(Array[index]) == ')' && top(par) == '(')
            {
                pop(par);
            }
            else if (top(Array[index]) == ']' && top(par) == '[')
            {
                pop(par);
            }
            else
            {
                if (mode)
                {
                    printf("Invalid: Missing a closing bracket for %c", top(par));
                }

                // Getting back Array[index] back to its original state
                Array[index] = temporary;
                reverseStack(index);

                // Getting rid of the unwanted stacks
                disposeStack(temporary);
                disposeStack(par);

                return false;
            }
        }
        push(top(Array[index]), temporary);
        pop(Array[index]);
    }

    // Getting back Array[index] back to its original state
    Array[index] = temporary;
    reverseStack(index);

    // Getting rid of the unwanted stacks
    disposeStack(temporary);

    if (isEmpty(par))
    {
        disposeStack(par);
        return true;
    }
    else
    {
        if (mode)
        {
            printf("Invalid: Missing an opening bracket for %c", top(par));
        }
        disposeStack(par);
        return false;
    }
}