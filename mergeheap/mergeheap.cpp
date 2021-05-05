#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("mergeheap.in","r");
FILE *g = fopen("mergeheap.out","w");

template<class T>
class DoubleLinkedList{
    struct node_t{
        node_t* nxt;
        node_t* ant;
        T stuff;

        node_t(T x){
            nxt = this;
            ant = this;
            stuff = x;
        }
    };

    node_t* root;

public:

    DoubleLinkedList(){
        root = NULL;
    }

    DoubleLinkedList(T x){
        root = new node_t(x);
    }

    bool empty(){
        return root == NULL;
    }

    void merge(DoubleLinkedList &other){
        if(this->empty()){
            this->root = other.root;
        }else if(other.empty()){
            this->root = this->root;
        }else{
            node_t* fst = root;
            node_t* lst = root->ant;
            node_t* fst2 = other.root;
            node_t* lst2 = other.root->ant;
            lst->nxt = fst2;
            fst2->ant = lst;
            lst2->nxt = fst;
            fst->ant = lst2;
        }
    }

    T front(){
        if(root == NULL){
            return NULL;
        }
        return root->stuff;
    }

    void pop_front(){
        if(root->nxt == root){
            root = NULL;
        }else{
            node_t* ant = root->ant;
            node_t* nxt = root->nxt;
            nxt->ant = ant;
            ant->nxt = nxt;
            root = nxt;
        }
    }
};

class PairingHeap{
    struct node_t{
        int key;
        DoubleLinkedList<node_t*> subheaps;

        node_t(int x){
            key = x;
            subheaps = DoubleLinkedList<node_t*>();
        }
    };

    node_t *root;

public:

    PairingHeap(){
        root = NULL;
    }
   
    node_t* meld(node_t* x,node_t* y){
        if(x == NULL){
            return y;
        }else if(y == NULL){
            return x;
        }else if(x->key > y->key){
            DoubleLinkedList<node_t*> tmp(y);
            x->subheaps.merge(tmp);
            return x;
        }else{
            DoubleLinkedList<node_t*> tmp(x);
            y->subheaps.merge(tmp);
            return y;
        }
    }

    void insert(int x){
        node_t* tmp = new node_t(x);
        root = meld(root,tmp);
    }

    int get_max(){
        return root->key;
    }

    node_t* merge_root_sons(){
        if(root->subheaps.empty()){
            return NULL;  
        }else{
            node_t* a;
            node_t* b;
            a = root->subheaps.front();
            root->subheaps.pop_front();
            if(root->subheaps.empty()){
                b = NULL;
            }else{
                b = root->subheaps.front();
                root->subheaps.pop_front();
            }
            return meld(meld(a,b),merge_root_sons());
        }
    }

    void delete_max(){
        root = merge_root_sons();         
    }

    void merge(PairingHeap &other){
        this->root = meld(this->root,other.root);
    }
};

const int LEN = (1 << 12);
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int n,q;
PairingHeap v[105];

int main(){

    n = i32();
    q = i32();

    for(int i = 1;i <= q;i++){
        int t;
        t = i32();

        if(t == 1){
            int m,x;
            m = i32();
            x = i32();
            v[m].insert(x);
        }else if(t == 2){
            int m;
            m = i32();
            fprintf(g,"%d\n",v[m].get_max());
            v[m].delete_max();
        }else{
            int a,b;
            a = i32();
            b = i32();
            v[a].merge(v[b]);
            v[b] = PairingHeap();
        }
    }
    
    
    fclose(f);
    fclose(g);


    return 0;
}
