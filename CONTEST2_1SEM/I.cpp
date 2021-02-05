#include<iostream>
#include<cstring>

using namespace std;

struct Node {
    Node *prev;
    int value;
    int min;
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
    ++stack->size;
    if (stack->size == 1 || stack->top->value < stack->top->prev->min) {
        stack->top->min = stack->top->value;
    } else {
        stack->top->min = stack->top->prev->min;
    }
}

int pop(Stack *stack) {
    Node *oldNode = stack->top;
    int value = stack->top->value;
    stack->top = stack->top->prev;
    delete oldNode;
    --stack->size;
    return value;
}

int size(Stack *stack1, Stack *stack2) {
    return stack1->size + stack2->size;
}

void clear(Stack *stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}

int minForOneStack(Stack *stack) {
    return stack->top->min;
}

void transport(Stack *stackPush, Stack *stackPop) {
    int value;
    while (stackPush->size != 0) {
        value = pop(stackPush);
        push(stackPop, value);
    }
}

int min(Stack *stack1, Stack *stack2) {
    int min1, min2;

    if (stack1->size != 0 && stack2->size != 0) {
        min1 = minForOneStack(stack1);
        min2 = minForOneStack(stack2);
        if (min1 < min2) {
            return min1;
        } else {
            return min2;
        }
    } else if (stack1->size != 0 && stack2->size == 0) {
        return stack1->top->min;
    } else if (stack2->size != 0 && stack1->size == 0) {
        return stack2->top->min;
    }
}

int main() {
    int numberOfCommands;
    cin >> numberOfCommands;
    Stack *stackPush = new Stack{NULL, 0};
    Stack *stackPop = new Stack{NULL, 0};
    char *command = new char[50];
    for (int i = 0; i < numberOfCommands; ++i) {
        cin >> command;
        if (strcmp(command, "enqueue") == 0) {
            int number;
            cin >> number;
            push(stackPush, number);
            cout << "ok" << endl;
        }

        if (strcmp(command, "dequeue") == 0) {
            if (stackPop->size == 0 && stackPush->size == 0) {
                cout << "error" << endl;
            } else if (stackPop->size == 0) {
                transport(stackPush, stackPop);
                cout << pop(stackPop) << endl;
            } else {
                cout << pop(stackPop) << endl;
            }
        }

        if (strcmp(command, "front") == 0) {
            if (stackPop->size == 0 && stackPush->size == 0) {
                cout << "error" << endl;
            } else if (stackPop->size == 0) {
                transport(stackPush, stackPop);
                cout << stackPop->top->value << endl;
            } else {
                cout << stackPop->top->value << endl;
            }
        }

        if (strcmp(command, "size") == 0) {
            cout << size(stackPop, stackPush) << endl;
        }
        if (strcmp(command, "clear") == 0) {
            clear(stackPop);
            clear(stackPush);
            cout << "ok" << endl;
        }
        if (strcmp(command, "min") == 0) {
            if (stackPop->size == 0 && stackPush->size == 0) {
                cout << "error" << endl;
            } else {
                cout << min(stackPop, stackPush) << endl;
            }

        }
    }
    clear(stackPop);
    clear(stackPush);
    delete[] command;
    delete[] stackPop;
    delete[] stackPush;
    return 0;
}