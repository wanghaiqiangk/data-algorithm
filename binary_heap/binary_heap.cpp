/*
 * 图解数据结构与算法 汪建
*/
#include <math.h>
#include <assert.h>
#include <iostream>

using namespace std;

int binary_heap[10000];
ssize_t size = 0;

int getParentIndex(int index)
{
    return floor((index - 1) / 2.0);
}

int getFirstChildIndex(int index)
{
    return 2 * index + 1;
}

int getSecondChildIndex(int index)
{
    return 2 * index + 2;
}

int getChildInex(int index,  int child)
{
    assert(child > 0 && child < 3);
    return 2 * index + child;
}

void swap(int* a, int* b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void insert(int value)
{
    int index = size++;
    binary_heap[index] = value;
    while (index > 0) {
        int parentIndex = getParentIndex(index);
        if (parentIndex >= 0 && binary_heap[parentIndex] > value) {
            swap(&binary_heap[parentIndex], &binary_heap[index]);
        } else {
            return;
        }
        index = parentIndex;
    }
}

void _delete() // delete has been used as keyword in c++
{
    if (size < 1) return;
    size--;
    swap(binary_heap[0], binary_heap[size]);
    int index = 0;
    while (index < size) {
        int checkIndex = -1;
        int firstChild = getFirstChildIndex(index);
        int secondChild = getSecondChildIndex(index);
        if (firstChild < size && secondChild < size) {
            if (binary_heap[firstChild] < binary_heap[secondChild]) {
                checkIndex = firstChild;
            } else {
                checkIndex = secondChild;
            }
        } else if (firstChild < size) {
            checkIndex = firstChild;
        }
        else if (secondChild < size) {
            checkIndex = secondChild;
        }
        else {
            return;
        }
        if (binary_heap[index] > binary_heap[checkIndex]) {
            swap(&binary_heap[index], &binary_heap[checkIndex]);
            index = checkIndex;
        } else {
            return;
        }
    }
}

void print()
{
    for (int i = 0; i < size; ++i)
    {
        cout << binary_heap[i] << " ";
    }
    cout << endl;
}

int getTreeLevel(int n)
{
    int i = 0;
    while (1) {
        if (pow(2, i+1) - 1 < n) {
            i++;
        }
        else {
            return i;
        }
    }
}

int getFirstIndexOnLevel(int level)
{
    return 2 * level - 1;
}

void adjust_subtree(int parent)
{
    while (parent < size) {
        int checkIndex = -1;
        int firstChild = getFirstChildIndex(parent);
        int secondChild = getSecondChildIndex(parent);
        if (firstChild < size && secondChild < size) {
            if (binary_heap[firstChild] < binary_heap[secondChild]) {
                checkIndex = firstChild;
            } else {
                checkIndex = secondChild;
            }
        } else if (firstChild < size) {
            checkIndex = firstChild;
        }
        else if (secondChild < size) {
            checkIndex = secondChild;
        }
        else {
            return;
        }
        if (binary_heap[parent] > binary_heap[checkIndex]) {
            swap(&binary_heap[parent], &binary_heap[checkIndex]);
            parent = checkIndex;
        } else {
            return;
        }
    }
}

void adjust_level_tree(int start, int count)
{
    int p = start;
    while (p < start + count) {
        adjust_subtree(p++);
    }
}

void adjust_tree(int parent)
{
    int firstChild = getFirstChildIndex(parent);
    int secondChild = getSecondChildIndex(parent);
    if (firstChild < size) {
        adjust_tree(firstChild);
    }
    if (secondChild < size) {
        adjust_tree(secondChild);
    }
    adjust_subtree(parent);
}

void make_heap(int data[], ssize_t count)
{
    size = count;
    for (int i = 0; i < size; ++i) {
        binary_heap[i] = data[i];
    }
#if 0 // iteration
    int Level = getTreeLevel(size);
    while (--Level >= 0) {
        adjust_level_tree(pow(2, Level)-1, pow(2, Level));
    }
#endif

#if 1 // recursion
    adjust_tree(0);
#endif
}

int main() {
    insert(4);
    insert(7);
    insert(2);
    insert(5);
    insert(6);
    insert(1);
    insert(0);
    insert(3);
    insert(8);
    print();

    _delete();
    print();

    int data[] = {4, 7, 2, 5, 6, 1, 0, 3, 8};
    make_heap(data, 9);
    print();

    return 0;
}
