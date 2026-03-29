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