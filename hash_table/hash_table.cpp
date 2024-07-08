#include <bits/stdc++.h>

using namespace std;

struct Node {
    char* key;
    char* value;
    struct Node* next;
};

// string view

struct HashTable {
    struct Node** buckets;
    int size;
    int capacity;
};

typedef struct Node Node;
typedef struct HashTable HashTable;

void setNode(struct Node* node, char* key, char* value)
{
    node->key = key;
    node->value = value;
    node->next = NULL;
}

void initializeHashTable(struct HashTable* hashtable)
{
    hashtable->capacity = 2;
    hashtable->size = 0;
    hashtable->buckets = (struct Node**)malloc(sizeof(struct Node*) * hashtable->capacity);
    memset(hashtable->buckets, 0, sizeof(struct Node*) * hashtable->capacity);
}

int hashing(HashTable* hashtable, char* key)
{
    int bucketIndex;
    int sum = 0;
    int factor = 31;
    for (int i = 0; i < strlen(key); i++) {
        sum = ((sum % hashtable->capacity) + ((int)key[i] * factor) % hashtable->capacity) % hashtable->capacity;
        factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
    }
    bucketIndex = sum;
    return bucketIndex;
}

bool should_rehashing(HashTable* hashtable)
{
    double load_factor = (double)hashtable->size / hashtable->capacity;
    return load_factor > 0.5;
}

void rehashing(HashTable* hashtable)
{
    printf("Rehashed\n");
    int oldCapacity = hashtable->capacity;
    hashtable->capacity *= 2;
    struct Node** tmp = (struct Node**)calloc(sizeof(struct Node*), hashtable->capacity);
    int bucketIndex = 0;
    int moved_size = 0;
    while (bucketIndex < oldCapacity && moved_size < hashtable->size) {
        struct Node** curr = &hashtable->buckets[bucketIndex++];
        while (*curr) {
            struct Node* taken = *curr;
            *curr = (*curr)->next;
            int tmpIndex = hashing(hashtable, taken->key);
            if (!tmp[tmpIndex]) {
                tmp[tmpIndex] = taken;
                taken->next = NULL;
            } else {
                taken->next = tmp[tmpIndex];
                tmp[tmpIndex] = taken;
            }
            moved_size++;
        }
    }
    free(hashtable->buckets);
    hashtable->buckets = tmp;
}

void insert(HashTable* hashtable, char* key, char* value)
{
    if (should_rehashing(hashtable)) {
        rehashing(hashtable);
    }
    hashtable->size++;
    int bucketIndex = hashing(hashtable, key);
    Node* n = (Node*)malloc(sizeof(Node));
    setNode(n, key, value);
    Node** bucketList = &hashtable->buckets[bucketIndex];
    if (!*bucketList) { // is the initial value is NULL?
        *bucketList = n;
    } else {
        n->next = *bucketList; // insert before head
        *bucketList = n;
    }
}

void deleteKey(HashTable* hashtable, char* key)
{
    int bucketIndex = hashing(hashtable, key);
    if (!hashtable->buckets[bucketIndex]) {
        return;
    }
    Node* curr = hashtable->buckets[bucketIndex];
    Node* prev = NULL;
    while (curr != NULL && 0 != strncmp(curr->key, key, strlen(key))) {
        prev = curr;
        curr = curr->next;
    }
    if (curr) {
        if (!prev) {
            hashtable->buckets[bucketIndex] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
        hashtable->size--;
    } else {
        return;
    }
}

char* search(HashTable* hashtable, char* key)
{
    int bucketIndex = hashing(hashtable, key);
    Node* bucketHead = hashtable->buckets[bucketIndex];
    while (bucketHead != NULL) {
        if (strcmp(key, bucketHead->key) == 0) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }
    char* errorMsg = (char*)malloc(sizeof(char) * 25); // we should free
    strcpy(errorMsg, "Oops! No data found.\n");
    return errorMsg;
}

int main()
{
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    initializeHashTable(hashtable);
    insert(hashtable, "Yogaholic", "Anjali");
    insert(hashtable, "pluto14", "Vartika");
    insert(hashtable, "elite_Programmer", "Manish");
    insert(hashtable, "GFG", "GeeksforGeeks");
    insert(hashtable, "decentBoy", "Mayank");

    printf("Current hash table size: %d\n", hashtable->size);

    printf("%s\n", search(hashtable, "elite_Programmer"));
    printf("%s\n", search(hashtable, "Yogaholic"));
    printf("%s\n", search(hashtable, "pluto14"));
    printf("%s\n", search(hashtable, "decentBoy"));
    printf("%s\n", search(hashtable, "GFG"));

    printf("%s\n", search(hashtable, "randomKey"));

    printf("\nAfter deletion:\n");
    deleteKey(hashtable, "decentBoy");
    printf("%s\n", search(hashtable, "decentBoy"));
    printf("Current hash table size: %d\n", hashtable->size);

    return 0;
}
