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

