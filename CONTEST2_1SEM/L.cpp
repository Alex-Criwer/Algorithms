#include <iostream>

using namespace std;
enum Brackets {
    LEFT_CIRCLE, RIGHT_CIRCLE, LEFT_SQUARE, RIGHT_SQUARE, LEFT_FIGURE, RIGHT_FIGURE
};

struct Node {
    int value;
    Node *prev = NULL;
};

struct Stack {
    int size;
    Node *top;
};

void push(Stack *stack, int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->prev = stack->top;
    stack->top = newNode;
    ++stack->size;
}

void pop(Stack *stack) {
    Node *oldNode = stack->top;
    stack->top = stack->top->prev;
    delete oldNode;
    --stack->size;
}

void clear(Stack *stack) {
    while (stack->size != 0) {
        pop(stack);
    }
}

int main() {
    Stack *stack = new Stack;
    char bracket;
    bool flag = false;
    do {
        cin.get(bracket);
        if (bracket == '(') {
            push(stack, Brackets::LEFT_CIRCLE);
        }
        if (bracket == '[') {
            push(stack, Brackets::LEFT_SQUARE);
        }
        if (bracket == '{') {
            push(stack, Brackets::LEFT_FIGURE);
        }
        if (bracket == ')') {
            if (stack->size == 0) {
                flag = true;
                break;
            } else {
                int temp = stack->top->value;
                pop(stack);
                if (temp != Brackets::RIGHT_CIRCLE - 1) {
                    flag = true;
                }
            }
        }
        if (bracket == ']') {
            if (stack->size == 0) {
                flag = true;
                break;
            } else {
                int temp = stack->top->value;
                pop(stack);
                if (temp != Brackets::RIGHT_SQUARE - 1) {
                    flag = true;
                }
            }
        }
        if (bracket == '}') {
            if (stack->size == 0) {
                flag = true;
                break;
            } else {
                int temp = stack->top->value;
                pop(stack);
                if (temp != Brackets::RIGHT_FIGURE - 1) {
                    flag = true;
                }
            }
        }

    } while (bracket != '\n');
    if (stack->size != 0 || flag) {
        cout << "no" << endl;
    } else {
        cout << "yes" << endl;
    }

    clear(stack);
    delete stack;
    return 0;
}
