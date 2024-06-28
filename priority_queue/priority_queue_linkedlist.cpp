#include <iostream>
#include <stdlib.h>

using namespace std;

struct node{
    int data;
    int priority;
    struct node* next;
};

typedef struct node Node;

Node* newNode(int d, int p)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = d;
    newNode->priority = p;
    newNode->next = nullptr;

    return newNode;
}

int peek(Node** head) // interesting pointer O(1)
{
    return (*head)->data;
}

void pop(Node** head) // O(1)
{
    Node* to_delete = *head;
    *head = (*head)->next;
    free(to_delete);
}

void push(Node** head, int d, int p) // O(n)
{
    Node* n = newNode(d, p);

    if ((*head)->priority < p) {
        n->next = *head;
        *head = n;
    }
    else {
        Node* iter = *head;
        while (iter->next != nullptr &&
                iter->next->priority > p) {
            iter = iter->next;
        }
        n->next = iter->next;
        iter->next = n;
    }
}

int isEmpty(Node** head)
{
    return *head == nullptr;
}

int main() {
    Node* pq = newNode(4, 1);
    push(&pq, 5, 2);
    push(&pq, 6, 3);
    push(&pq, 7, 0);

    while (!isEmpty(&pq)) {
        cout << " " << peek(&pq);
        pop(&pq);
    }

    cout << endl;

    return 0;
}
