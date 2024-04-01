#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max_stack 100

typedef struct {
    char data[max_stack];
    int top;
} stack;

void initStack(stack *s) {
    s->top = -1;
}

int isEmpty(stack *s) {
    return s->top == -1;
}

int isFull(stack *s) {
    return s->top == max_stack - 1;
}

void Push(stack *s, char c) {
    if (isFull(s)) {
        printf("Stack Penuh!\n");
        return;
    }
    s->data[++s->top] = c;
}

char Pop(stack *s) {
    if (isEmpty(s)) {
        printf("Stack Kosong\n");
        return '\0';
    }
    return s->data[s->top--];
}

int priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return c;
        case '*':
        case '/':
            return c + 2;
        case '^':
            return c + 4;
        default:
            return 0;
    }
}

void InfixPostfix(char *infix, char *postfix) {
    stack s;
    initStack(&s);
    int i, j = 0;
    for (i = 0; infix[i]; i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            Push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && s.data[s.top] != '(') {
                postfix[j++] = Pop(&s);
            }
            if (!isEmpty(&s) && s.data[s.top] == '(') {
                Pop(&s);
            }
        } else {
            while (!isEmpty(&s) && priority(s.data[s.top]) >= priority(infix[i])) {
                postfix[j++] = Pop(&s);
            }
            Push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = Pop(&s);
    }
    postfix[j] = '\0';
}

double hasil(char *postfix) {
    stack s;
    initStack(&s);
    int i;
    for (i = 0; postfix[i]; i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            Push(&s, postfix[i]);
        } else {
            double b = Pop(&s) - '0';
            double a = Pop(&s) - '0';
            switch (postfix[i]) {
                case '+':
                    Push(&s, a + b + '0');
                    break;
                case '-':
                    Push(&s, a - b + '0');
                    break;
                case '*':
                    Push(&s, a * b + '0');
                    break;
                case '/':
                    Push(&s, a / b + '0');
                    break;
                case '^':
                    Push(&s, pow(a, b) + '0');
                    break;
            }
        }
    }
    return Pop(&s) - '0';
}

int main() {
    char infix[max_stack], postfix[max_stack];
    system("cls");
    printf("+---------------------------------------------------------+\n\n");
    printf("\t\tKALKULATOR INFIX KE POSTFIX \n\n");
    printf("+---------------------------------------------------------+\n\n");
    printf("\tMasukkan Notasi Infix (tanpa spasi) : ");
    scanf("%s", infix);
    InfixPostfix(infix, postfix);
    printf("\tNotasi Postfix : %s\n", postfix);
    printf("\tHasil : %.2f\n\n", hasil(postfix));
    printf("+---------------------------------------------------------+");
    return 0;
}