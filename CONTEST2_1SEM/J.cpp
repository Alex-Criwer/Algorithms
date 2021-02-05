#include<iostream>
#include<cstring>

using namespace std;

struct Node {
    int value;
    Node *prev = NULL;
    Node *next = NULL;
};
struct Dequeue {
    Node *top;
    Node *end;
    int size;
};

void push_front(Dequeue *dequeue, int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->prev = dequeue->top;
    if (dequeue->size == 0) {
        dequeue->end = newNode;
    } else {
        dequeue->top->next = newNode;
    }
    dequeue->top = newNode;
    ++dequeue->size;
}

void push_back(Dequeue *dequeue, int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = dequeue->end;
    if (dequeue->size == 0) {
        dequeue->top = newNode;
    } else {
        dequeue->end->prev = newNode;
    }
    dequeue->end = newNode;
    ++dequeue->size;
}

void pop_front(Dequeue *dequeue) {
    if (dequeue->size > 1) {
        Node *oldNode = dequeue->top;
        dequeue->top = dequeue->top->prev;
        dequeue->top->next = NULL;
        delete oldNode;
        --dequeue->size;
    } else {
        delete dequeue->top;
        dequeue->top = NULL;
        dequeue->end = NULL;
        dequeue->size = 0;
    }
}

void pop_back(Dequeue *dequeue) {
    if (dequeue->size > 1) {
        Node *oldNode = dequeue->end;
        dequeue->end = dequeue->end->next;
        dequeue->end->prev = NULL;
        delete oldNode;
        --dequeue->size;
    } else {
        delete dequeue->end;
        dequeue->top = NULL;
        dequeue->end = NULL;
        dequeue->size = 0;
    }
}

void clear(Dequeue *dequeue) {
    while (dequeue->size != 0) {
        pop_front(dequeue);
    }
}

int main() {
    Dequeue *dequeue = new Dequeue{NULL, NULL, 0};
    int numberOfCommands;
    cin >> numberOfCommands;
    char *command = new char[30];

    for (int i = 0; i < numberOfCommands; ++i) {
        cin >> command;
        if (strcmp(command, "push_front") == 0) {
            int number;
            cin >> number;
            push_front(dequeue, number);
            cout << "ok" << endl;
        }
        if (strcmp(command, "push_back") == 0) {
            int number;
            cin >> number;
            push_back(dequeue, number);
            cout << "ok" << endl;
        }
        if (strcmp(command, "pop_front") == 0) {
            if (dequeue->size == 0) {
                cout << "error" << endl;
            } else {
                cout << dequeue->top->value << endl;
                pop_front(dequeue);
            }

        }
        if (strcmp(command, "pop_back") == 0) {
            if (dequeue->size == 0) {
                cout << "error" << endl;
            } else {
                cout << dequeue->end->value << endl;
                pop_back(dequeue);
            }
        }
        if (strcmp(command, "front") == 0) {
            if (dequeue->size == 0) {
                cout << "error" << endl;
            } else {
                cout << dequeue->top->value << endl;
            }
        }
        if (strcmp(command, "back") == 0) {
            if (dequeue->size == 0) {
                cout << "error" << endl;
            } else {
                cout << dequeue->end->value << endl;
            }
        }
        if (strcmp(command, "size") == 0) {
            cout << dequeue->size << endl;
        }
        if (strcmp(command, "clear") == 0) {
            clear(dequeue);
            cout << "ok" << endl;
        }

    }
    delete[] command;
    clear(dequeue);
    delete dequeue;
    return 0;
}

