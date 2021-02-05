#include<iostream>

using namespace std;

struct Node {
    int value;
    Node *prev;
};

struct Stack {
    Node *top;
    int size;
};

void push(Stack *stack, int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->prev = stack->top;
    stack->top = newNode;
    ++(stack->size);
}

int pop(Stack *stack) {
    int currValue = stack->top->value;
    Node *oldNode = stack->top;
    stack->top = stack->top->prev;
    delete oldNode;
    --(stack->size);
    return currValue;
}

bool isDigit(char element) {
    return ((element - '0') >= 0 && (element - '0')<= 9);
}

void clear(Stack *stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}

int main() {
    Stack *stack = new Stack{NULL, 0};
    char element;
    do {
        cin.get(element);
        if (isDigit(element)) {
            push(stack, element - '0');
        } else if (element == '+') {
            int temp1 = pop(stack);
            int temp2 = pop(stack);
            push(stack, temp1 + temp2);
        } else if (element == '-') {
            int temp1 = pop(stack);
            int temp2 = pop(stack);
            push(stack, temp2 - temp1);
        } else if (element == '*') {
            int temp1 = pop(stack);
            int temp2 = pop(stack);
            push(stack, temp1 * temp2);
        }
    } while (element != '\n');
    cout << pop(stack);
    clear(stack);
    delete stack;
    return 0;
}