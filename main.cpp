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
