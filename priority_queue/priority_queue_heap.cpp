#include <iostream>

using namespace std;

int H[50];
int size = -1;

int parent(int i)
{
    return (i - 1) / 2;
}

int leftChild(int i)
{
    return 2 * i + 1;
}

int rightChild(int i)
{
    return 2 * i + 2;
}

void shiftUp(int i)
{
    while (i > 0 && H[parent(i)] < H[i]) {
        swap(H[parent(i)], H[i]);
        i = parent(i);
    }
}

void shiftDown(int i)
{
    int maxIndex = i;

    int l = leftChild(i);

    if (l <= size && H[l] > H[maxIndex]) {
        maxIndex = l;
    }

    int r = rightChild(i);

    if (r <= size && H[r] > H[maxIndex]) {
        maxIndex = r;
    }

    if (maxIndex != i) {
        swap(H[maxIndex], H[i]);
        shiftDown(maxIndex);
    }
}

void insert(int p)
{
    size++;
    H[size] = p;
    shiftUp(size);
}

int extractMax()
{
    int result = H[0];
    swap(H[0], H[size]);
    size--;
    shiftDown(0);
    return result;
}

void changePriority(int i, int p)
{
    int oldP = H[i];
    H[i] = p;

    if (p > oldP) {
        shiftUp(i);
    } else {
        shiftDown(i);
    }
}

int getMax() { return H[0]; }

void remove(int i)
{
    int maxP = getMax();
    H[i] = maxP + 1;
    shiftUp(i);
    extractMax();
}

void print()
{
    int i = 0;
    while (i <= size) {
        cout << H[i] << " ";
        ++i;
    }
    cout << "\n";
}

int main() {
    insert(45);
    insert(20);
    insert(14);
    insert(12);
    insert(31);
    insert(7);
    insert(11);
    insert(13);
    insert(7);

    cout << "Priority Queue: ";
    print();

    cout << endl;

    cout << "Node with maximum priority:"
        << extractMax() << "\n";

    cout << "Priority Queue after extracting maximum:";
    print();

    changePriority(2, 49);
    cout << "Priority queue after change priority:";
    print();

    remove(3);
    cout << "Priority queue after removing a element:";
    print();

    return 0;
}
