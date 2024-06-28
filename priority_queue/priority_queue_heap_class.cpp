#include <iostream>
#include <vector>

using namespace std;

// used as typename T
typedef struct {
    int data;
    int priority;
} Data;

template<typename T>
class PriorityQueue {
private:
    vector<T> data;

public:
    PriorityQueue() {}
    void Enqueue(T item);
    T Dequeue();
    T Peek() { return data[0]; };
    int Count() { return data.size(); };
};

int main()
{
    PriorityQueue<int> pq;
    pq.Enqueue(1);
    cout << "Size of pq is : " << pq.Count() <<
        " and peek element is : " << pq.Peek() << endl;
    pq.Enqueue(10);
    pq.Enqueue(-8);
    cout << "Size of pq is : " << pq.Count() <<
        " and peek element is : " << pq.Peek() << endl;
    pq.Dequeue();
    cout << "Size of pq is : " << pq.Count() <<
        " and peek element is : " << pq.Peek() << endl;
    pq.Dequeue();
    cout << "Size of pq is : " << pq.Count() <<
        " and peek element is : " << pq.Peek() << endl;
    pq.Enqueue(25);
    cout << "Size of pq is : " << pq.Count() <<
        " and peek element is : " << pq.Peek() << endl;
    return 0;
}

template<typename T>
void PriorityQueue<T>::Enqueue(T item)
{
    data.push_back(item);
    int index = data.size() - 1;
    while (index > 0) {
        int parent = (index - 1) / 2; // because of the check on index, parent won't be negative
        if (data[parent] > data[index]) break;
        swap(data[parent], data[index]);
        index = parent;
    }
}

template<typename T>
T PriorityQueue<T>::Dequeue()
{
    T result = data[0];
    int li = data.size() - 1;
    data[0] = data[li];
    data.pop_back();

    // re-structure
    size_t cc = 0;
    size_t maxIndex = cc;
    while (cc < data.size()) {
        size_t lc = cc * 2 + 1;
        if (lc < data.size() && data[lc] > data[cc]) {
            maxIndex = lc;
        }
        size_t rc = cc * 2 + 2;
        if (rc < data.size() && data[rc] > data[cc]) {
            maxIndex = rc;
        }
        if (cc != maxIndex) {
            swap(data[maxIndex], data[cc]);
            cc = maxIndex;
        } else {
            break;
        }
    }

    return result;
}
