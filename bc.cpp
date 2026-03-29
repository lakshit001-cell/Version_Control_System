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
#pragma once
#include <vector>
using namespace std;


template <typename T>
class MaxHeap{
    private:
        vector<T> arr;

        int parent(int i){
            return ((i-1)/2);
        }
        int leftchild(int i){
            return(2*i+1);
        }
        int rightchild(int i){
            return (2*i+2);
        }

        void heapifyUp(int i)
        {
            while(i>0 and arr[parent(i)] < arr[i])
            {
                swap(arr[i],arr[parent(i)]);
                i=parent(i);
            }
        }

        void heapifyDown(int i){
            int root=i;
            int left= leftchild(i);
            int right=rightchild(i);
            if(left<arr.size() and arr[left]>arr[root])
                root=left;
            if(right<arr.size() and arr[right]>arr[root])
                root=right;
            if(root!=i)
            {
                swap(arr[i],arr[root]);
                heapifyDown(root);
            }



        }


    public:
            void push(T v){
                arr.push_back(v);
                heapifyUp(arr.size()-1);
            }

            void pop(){
                if(arr.empty())
                    return;

                arr[0]=arr.back();
                arr.pop_back();
                if(!arr.empty())
                    heapifyDown(0);

            }
            T top(){
                if(arr.empty())
                    throw runtime_error("Heap is empty");
                return arr[0];
            }
            bool empty(){
                return(arr.empty());
            }
            int size(){
                return arr.size();
            }

};

#include <iostream>
#include <string>
#include "HashMap.hpp"
#include "Tree.hpp"
#include "Heap.hpp"
#include <sstream>
using namespace std;


struct Filetime{
    string name;
    File* file;
    long long key;

    Filetime(){
        file=NULL;
        key=0;
    }

    Filetime(string filename, File* f, long long k)
    {
        name=filename;
        file=f;
        key=k;
    }
    bool operator<(const Filetime& other) const
    {
        return key< other.key;
    }
    bool operator>(const Filetime& other) const
    {
        return key>other.key;
    }


};


struct FileSize {
    string name;
    File* file;
    long long key; 

    FileSize() {
        file = nullptr;
        key = 0;
    }

    FileSize(string filename, File* f, long long k) 
    {
        name=filename;
        file = f;
        key = k;
    }

    bool operator<(const FileSize& other) const 
    {
        return key < other.key;
    }
    bool operator>(const FileSize& other) const 
    {
        return key > other.key;
    }


};


int main(){
    cout<<"WELCOME, MAKE SURE TO READ README, TYPE COMMANDS ONLY IN UPPERCASE LETTERS WITH ARGUMENTS, START BY CREATING A FILE"<<endl;

    HashMap<string,File*> files;
    string c;
    while (true) {
    string line;
    if (!getline(cin, line)) break;
    if (line.empty()) continue;

    stringstream ss(line);
    string c;
    ss >> c;

    if (c == "CREATE") {
        string filename;
        ss >> filename;

        if (files.contains(filename)) {
            cout << "ERROR, FILE NAME NOT AVAILABLE" << endl;
            continue;
        }

        File* f = new File();
        f->create();
        files.insert(filename, f);
        cout << "FILE " << filename << " created" << endl;

    }

    else if (c == "READ") 
    {
        string filename;
        ss >> filename;

        if (!files.contains(filename)) {
            cout << "NO FILE "<<filename <<" EXISTS" <<endl;
            continue;
        }
        cout << files.get(filename)->Read() << endl;

    }

    else if (c == "INSERT") {
        string filename, t;
        ss >> filename >> t;


        if (!files.contains(filename))
        {
            cout << "NO SUCH FILE EXISTS" << endl;
            continue;
        }

        files.get(filename)->insert(t);
        cout << "Inserted" << endl;


    }

    else if (c == "UPDATE") {
        string filename, t;
        ss >> filename >> t;

        if (!files.contains(filename))
        {
            cout << "NO SUCH FILE EXISTS" << endl;
            continue;

        }
        files.get(filename)->update(t);

        cout << "UPDATED" << endl;
    }

    else if (c == "SNAPSHOT") {
        string filename;

        ss >> filename;
        string message;
        getline(ss, message); 

        if (!files.contains(filename)) {
            cout << "NO SUCH FILE EXISTS" << endl;
            continue;

        }
        files.get(filename)->snapshot(message);
        
    }

    else if (c == "ROLLBACK") {
        string filename;
        ss >> filename;

        if (!files.contains(filename)) {
            cout << "NO SUCH FILE EXISTS"<< endl;
            continue;
        }

        int versionid;
        if (ss >> versionid)
            files.get(filename)->rollback(versionid);
        else

            files.get(filename)->rollback();

        
    }

    else if (c == "HISTORY") {
        string filename;
        ss >> filename;

        if (!files.contains(filename)) {
            cout << "NO SUCH FILE EXISTS" << endl;
            continue;

        }

        files.get(filename)->history();
    }

    else if (c == "RECENT") {
        string d;
        int num;
        ss >> d >> num;

        MaxHeap<Filetime> heap;

        vector<string> keys = files.keys();

        for (string fname : keys) {
            File* f = files.get(fname);
            heap.push(Filetime(fname, f, f->last_modified));
        
        }

        int total=keys.size();

        if(num<0)
        {
            cout<<"PLEASE ENTER A POSITIVE NO"<<endl;
            continue;
        }

        if(num>total)
        {

            cout<<"ONLY "<<total<<" FILES ARE AVAILABE: "<<endl;
            num=total;
        }
        else
            cout << "Most recent " << num << " files:" << endl;
        for (int i = 0; i < num && !heap.empty(); i++) 
        {

            Filetime top = heap.top();
            string timestr=ctime(&top.file->last_modified);
            
            cout << "FILE: " << top.name << " versions=" << top.file->total_versions << ", last_modified=" << timestr << endl;
            heap.pop();

        }
    }

    else if (c == "BIGGEST") {
        string d;
        int num;
        ss >> d >> num;

        MaxHeap<FileSize> heap;

        vector<string> keys = files.keys();
        for (string fname : keys) {
            File* f = files.get(fname);
            heap.push(FileSize(fname, f, f->total_versions));
        }

        int total=keys.size();
        if(num<0)
        {
            cout<<"PLEASE ENTER A POSITIVE NO"<<endl;
            continue;
        }

        if(num>total){
            cout<<"ONLY "<<total<<" FILES ARE AVAILABLE"<<endl;
            num=total;
        }
        else    
            cout << "Top " << num << " biggest trees:" << endl;
        for (int i = 0; i < num && !heap.empty(); i++) {
            FileSize top = heap.top();
            string timesstr=ctime(&top.file->last_modified);

            cout << "File " << top.name<< " versions=" << top.file->total_versions<< ", last_modified=" << timesstr<< endl;
            heap.pop();

        }
    }

    else {
        cout << "COMMAND DO NOT EXIST" << endl;
    }
    
    }
}

#pragma once
#include<string>
#include <vector>
#include <ctime>
#include"HashMap.hpp"
using namespace std;


class Treenode{

    public:
        int version_id;

        string content;
        string message;
        time_t created_timestamp;
        time_t snapshot_timestamp;
        Treenode* parent;
        vector<Treenode*> children;

        Treenode(int id,string c="",string m=""){
            version_id=id;
            content=c;
            message=m;
            created_timestamp=time(NULL);
            snapshot_timestamp=0;
            parent=NULL;
        }

        bool isSnapshot(){
            return (snapshot_timestamp!=0);

        }

};


class File{

    public:

        Treenode* root;
        Treenode* active_version;
        HashMap<int,Treenode*> version_map;
        int total_versions;
        time_t last_modified;

        File(): root(NULL), active_version(NULL),total_versions(0){}

        void create(){

            root= new Treenode(0,"","INITIAL SNAPSHOT");
            root->snapshot_timestamp=time(NULL);
            active_version=root;

            version_map.insert(0,root);
            total_versions=1;
            last_modified=time(NULL);
        }


        string Read(){
            if(active_version)
                return active_version->content;
            else
                return "";
        }




        void insert(string t){
            if(!active_version)
                return;
            
            if(!active_version->isSnapshot())
                active_version->content+=t;

            else{

                int id= total_versions;
                Treenode* temp=new Treenode(id,active_version->content+t);
                temp->parent=active_version;
                active_version->children.push_back(temp);

                active_version=temp;
                version_map.insert(id,temp);
                total_versions++;

            } 

            last_modified=time(NULL);
        }


        void update(string t)
        {
            if(!active_version)
                return;
            if(!active_version->isSnapshot())
                active_version->content=t;

            else{
                int id= total_versions;
                Treenode* temp=new Treenode(id,t);
                temp->parent=active_version;
                active_version->children.push_back(temp);
                active_version=temp;
                version_map.insert(id,temp);
                total_versions++;

            }

            last_modified=time(NULL);
        }

        void snapshot(string m)
        {

            if(!active_version)
                return;
            if(m.empty())
                m="NO MESSAGE PROVIDED";
            if(active_version->isSnapshot()){
                cout<<"snapshot already taken";
                return;
                
            }
            active_version->message=m;
            active_version->snapshot_timestamp=time(NULL);
            last_modified=time(NULL);
            cout<<"snapshot taken (Message: "<<m<<")"<<endl;


        }

        void rollback(int vid=-1){

           if(!active_version)
                return;
            if(vid==-1)
                {
                    if(active_version->parent){
                        active_version=active_version->parent;
                        last_modified=time(NULL);
                        cout<<"ROLLED BACK"<<endl;
                    }
                    else    
                        cout<<"NO PREVIOUS VERSION";

                }

            
            else{

                Treenode* t=version_map.get(vid);
                if(t)
                {
                    active_version=t;
                    last_modified=time(NULL);
                    cout<<"ROLLED BACK"<<endl;
                }

                else{
                    cout<<"WRONG VERSION"<<endl;
                }

            }


          
        }


        void history(){

            if(!active_version)
                return;
            vector<Treenode*> path;
            Treenode* curr=active_version;
            while(curr)
            {
                if(curr->isSnapshot())
                {
                    path.push_back(curr);
                    
                }

                curr=curr->parent;

            }


            for(int i=path.size()-1;i>=0;i--)
            {
                cout<<"version "<<path[i]->version_id<<" Time "<<ctime(&path[i]->snapshot_timestamp)<<" Message "<<path[i]->message<<endl;
            }
            

            
        }




};