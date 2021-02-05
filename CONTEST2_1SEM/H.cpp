#include <iostream>
#include<cstring>

using namespace std;

struct Node {
    int value;
    Node *prev;
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
    ++(stack->size);

    if ((stack->size) == 1) {
        stack->top->min = value;
    } else {
        if (value < (stack->top->prev->min)) {
            stack->top->min = value;
        } else {
            stack->top->min = stack->top->prev->min;
        }
    }
}

void pop(Stack *stack) {
    Node *oldNode = stack->top;
    stack->top = (stack->top)->prev;
    delete oldNode;
    --(stack->size);
}

int back(Stack *stack) {
    return stack->top->value;
}

int size(Stack *stack) {
    return stack->size;
}

void clear(Stack *stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}

int min(Stack *stack) {
    return stack->top->min;
}

int main() {
    Stack *stack = new Stack{NULL, 0};
    int numberOfCommands;
    char *command = new char[50];
    cin >> numberOfCommands;
    for (int i = 0; i < numberOfCommands; ++i) {
        cin >> command;
        if (strcmp(command, "push") == 0) {
            int value;
            cin >> value;
            push(stack, value);
            cout << "ok" << endl;
        }
        if (strcmp(command, "pop") == 0) {
            if (stack->size > 0) {
                cout << back(stack) << endl;
                pop(stack);
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "back") == 0) {
            if (stack->size > 0) {
                cout << back(stack) << endl;
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "min") == 0) {
            if (stack->size > 0) {
                cout << min(stack) << endl;
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "size") == 0) {
            cout << size(stack) << endl;
        }
        if (strcmp(command, "clear") == 0) {
            clear(stack);
            cout << "ok" << endl;
        }

    }
    delete[] command;
    clear(stack);
    delete stack;
    return 0;
}