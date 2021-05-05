#include <bits/stdc++.h>
 
using namespace std;
 
FILE *f = fopen("mergeheap.in","r");
FILE *g = fopen("mergeheap.out","w");
 
const int LGMAX = 19;
 
class FibonacciHeap{
    struct node_t{
        int key;
        node_t* nxt;
        node_t* ant;
        vector<node_t*> sons;
 
        node_t(int x){
            key = x;
            nxt = this;
            ant = this;
            sons = vector<node_t*>();
        }
    };
 
    node_t* nill;
    node_t* max_ptr;
 
public:
 
    FibonacciHeap(){
        nill = new node_t(-(2e9 + 5));
        max_ptr = nill;
    }
   
    void insert(int x){
        node_t* tmp = new node_t(x);
        tmp->nxt = nill->nxt;
        tmp->ant = nill;
        tmp->nxt->ant = tmp;
        tmp->ant->nxt = tmp;
        if(x > max_ptr->key){
            max_ptr = tmp;
        }
    }
 
    void merge(const FibonacciHeap &other){
        node_t* fst = nill;
        node_t* lst = nill->ant;
        node_t* fst2 = other.nill->nxt;
        node_t* lst2 = other.nill->ant;
        if(fst2 == other.nill || lst2 == other.nill){
            return;
        }
        lst->nxt = fst2;fst2->ant = lst;
        lst2->nxt = fst;fst->ant = lst2;
        if(this->max_ptr->key < other.max_ptr->key){
            max_ptr = other.max_ptr;
        }
    }
 
    int get_max(){
        return max_ptr->key;
    }
 
    void delete_max(){
     
        node_t* lst = max_ptr->ant;
 
        for(auto &it:max_ptr->sons){
            lst->nxt = it;
            it->ant = lst;
            lst = it;
        }
        lst->nxt = max_ptr->nxt;
        lst->nxt->ant = lst;
        
        vector<node_t*> available_with_deg(LGMAX,NULL);
 
        for(node_t* it = nill->nxt;it != nill;it = it->nxt){
            node_t* curr = it;
            while(available_with_deg[curr->sons.size()] != NULL){
                node_t* other = available_with_deg[curr->sons.size()];
                if(other->key > curr->key){
                    swap(curr,other);
                }
                available_with_deg[curr->sons.size()] = NULL;
                curr->sons.push_back(other);
            }
            available_with_deg[curr->sons.size()] = curr;
        }
        
        nill->ant = nill;
        nill->nxt = nill;
        max_ptr = lst = nill;
 
        for(auto &it:available_with_deg){
            if(it != NULL){
                lst->nxt = it;
                it->ant = lst;
                lst = it;
                if(max_ptr->key < it->key){
                    max_ptr = it;
                }
            }
        }
 
        lst->nxt = nill;
        nill->ant = lst;
    }
};
 
int n,q;
FibonacciHeap v[105];

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
            v[b] = FibonacciHeap();
        }
    }
    
    
    fclose(f);
    fclose(g);
 
 
    return 0;
}
