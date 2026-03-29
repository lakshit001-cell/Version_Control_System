#pragma once
#include <vector>
#include <string>
using namespace std;


template <typename K, typename V>
class HashMap {
private:

    class Node {
    public:
        K key;
        V value;
        Node* next;

        Node(K k, V v) {
            key = k;
            value = v;
            next = NULL;
        }
    };

    
    int maxsize;       
    int count;        
    double loadFactor; 
    vector<Node*> table;

    int hashFunction(const int& key) {
        return key % maxsize;
    }

    
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % maxsize;
        }
        return hash;
    }

    
    void rehash() {
        int curr = maxsize;
        vector<Node*> oldTable = table;
        maxsize *= 2;
        table.clear();
        table.resize(maxsize, NULL);
        count = 0;

        for (int i = 0; i < curr; i++) {
            Node* node = oldTable[i];
            while (node) {
                insert(node->key, node->value);
                Node* temp = node;
                node = node->next;
                delete temp; 
            }
        }



    }
public:


    HashMap(int size = 1000) {
        maxsize = size;
        count = 0;
        loadFactor = 0.7;
        table.resize(maxsize, NULL);
    }


    void insert(K key, V value) {
        int id = hashFunction(key);
        Node* node = table[id];
        while (node != NULL) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = table[id];
        table[id] = newNode;
        count++;

        if ((double)count / maxsize > loadFactor) {
            rehash();
        }
    }


    V get(K key) {
        int id = hashFunction(key);
        Node* node = table[id];
        while (node != NULL) {
            if (node->key == key)
                return node->value;
            node = node->next;
        }

        return V();
    }

    bool contains(K key) {
        int id = hashFunction(key);
        Node* node = table[id];
        while (node) {
            if (node->key == key) return true;
            node = node->next;
        }
        return false;
    }
    

    vector<K> keys() {
        vector<K> r;
        for (int i = 0; i < maxsize; i++) {
            Node* node = table[i];
            while (node) {
                r.push_back(node->key);
                node = node->next;
            }
        }
        return r;
    }


};
