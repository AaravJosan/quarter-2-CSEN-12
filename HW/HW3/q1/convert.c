#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Stack{
    int top;
    unsigned capacity;
    char** array;
};

struct Stack* createStack(unsigned capacity){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char**)malloc(capacity * sizeof(char*));
    return stack;
}

bool isOperator(char x){
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^');
}

int isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, char* item){
    stack->array[++stack->top] = item;
}

char* peek(struct Stack* stack){
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return NULL;
}

int getPriority(char c){
    switch(c){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

char* pop(struct Stack* stack){
    return stack->array[stack->top--];
}

char* preToInfix(char* pre_exp){
    int length = strlen(pre_exp);
    struct Stack* stack = createStack(length);

    for(int i = length - 1; i >= 0; i--){
        if(isOperator(pre_exp[i])) {
            char* op1 = pop(stack);
            char* op2 = pop(stack);
            char* temp = (char*)malloc((strlen(op1) + strlen(op2) + 4) * sizeof(char));
            sprintf(temp, "(%s%c%s)", op1, pre_exp[i], op2);
            push(stack, temp);
        } 
        else{
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = pre_exp[i];
            operand[1] = '\0';
            push(stack, operand);
        }
    }

    return pop(stack);
}

void infixToPrefix(char* infix){
    char expression[100];
    int count = 0;
    int len = strlen(infix);
    struct Stack* stack = createStack(len);
    char* prefix = (char*)malloc(len * sizeof(char));
    int j = 0;

    for(int i = len - 1; i >= 0; i--){
        if(infix[i] == '(')
            infix[i] = ')';
        else if(infix[i] == ')')
            infix[i] = '(';
        prefix[j++] = infix[i];
    }
    prefix[j] = '\0';

    for(int i = 0; i < len; i++){
        if(isalpha(prefix[i]) || isdigit(prefix[i])){
            expression[count] = prefix[i];
            count++;
        }
        else if(prefix[i] == '(')
            push(stack, "(");
        else if(prefix[i] == ')') {
            while(!isEmpty(stack) && strcmp(peek(stack), "(") != 0){
                expression[count] = *pop(stack);
                count++;
            }
            pop(stack);
        } 
        else if(isOperator(prefix[i])) {
            while(!isEmpty(stack) && getPriority(prefix[i]) <= getPriority(*peek(stack))){
                expression[count] = *pop(stack);
                count++;
            }
            push(stack, (char[]){prefix[i], '\0'});
        }
    }

    while(!isEmpty(stack)){
        expression[count] = *pop(stack);
        count++;
    }
    int slen = strlen(expression);
    for (int i = 0, j = slen - 1; i <= j; i++, j--) { 
        char c = expression[i]; 
        expression[i] = expression[j]; 
        expression[j] = c; 
    } 
    printf("%s", expression);

    free(prefix);
    free(stack->array);
    free(stack);
}


int main() {
    char pre[] = "*-A/BC-/AKL";
    char* infix = preToInfix(pre);
    printf("Infix expression: %s\n", infix);

    char inf[] = "((A-B)*(C/D))";
    infixToPrefix(inf);

    free(infix);
}
