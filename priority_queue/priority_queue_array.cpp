#include <limits.h>
#include <iostream>
#include <cassert>

using namespace std;

struct item {
    int value;
    int priority;
};

item pr[100000];

int size = 0;

void enqueue(int value, int priority) // O(1)
{
    pr[size].value = value;
    pr[size].priority = priority;

    size++;
}

int peek() // O(n)
{
    int highestPriority = INT_MIN;
    int ind = -1;

    for (int i = 0; i < size; i++)
    {
        if (highestPriority == pr[i].priority && ind > -1
                && pr[ind].value < pr[i].value)
        {
            ind = i;
        }
        else if (highestPriority < pr[i].priority)
        {
            highestPriority = pr[i].priority;
            ind = i;
        }
    }

    return ind;
}

void dequeue() // O(n)
{
    int ind = peek();  // re-use

    for (int i = ind; i+1 < size; ++i)
    {
        pr[i] = pr[i+1];
    }

    size--;
}

int main()
{
    enqueue(10, 2);
    enqueue(14, 4);
    enqueue(16, 4);
    enqueue(12, 3);

    int ind = peek();
    cout << ind << endl;
    assert(ind == 2);
    cout << pr[ind].value << endl; // 16

    dequeue();

    ind = peek();
    cout << pr[ind].value << endl; // 14

    dequeue();

    ind = peek();
    cout << pr[ind].value << endl; // 12

    return 0;
}
