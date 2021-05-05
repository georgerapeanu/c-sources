#include <cstdio>

using namespace std;

class Heap{
    struct node_t{
        node_t* child;
        node_t* sibling;
        int key;

        node_t(int key){
            child = NULL;
            sibling = NULL;
            this->key = key;
        }
    }*root;

public:

    Heap(){
        root = NULL;
    }

    node_t* meld(node_t* a,node_t* b){
        if(a == NULL){
            return b;
        }
        if(b == NULL){
            return a;
        }
        if(a->key > b->key){
            b->sibling = a->child;
            a->child = b;
            return a;
        }else{
            a->sibling = b->child;
            b->child = a;
            return b;
        }
    }

    void push(int key){
        node_t *tmp = new node_t(key);
        root = meld(root,tmp);
    }

    int top(){
        return root->key;
    }

    node_t* merge_root_sons(){
        if(root->child == NULL){
            return NULL;
        }
        node_t* a = root->child;
        if(a->sibling == NULL){
            return a;
        }
        node_t* b = a->sibling;
        root->child = b->sibling;
        a->sibling = b->sibling = NULL;
        return meld(meld(a,b),merge_root_sons());
    }

    void pop(){
        root = merge_root_sons();
    }

    void merge(Heap &other){
        root = meld(root,other.root);
    }
}heaps[105];

int n,m;
int t;
int x,y;

FILE *f = fopen("mergeheap.in","r");
FILE *g = fopen("mergeheap.out","w");

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

    n = i32();m = i32();

    for(int i = 1;i <= n;i++){
        heaps[i] = Heap();
    }

    for(int i = 1;i <= m;i++){
        t = i32();
        if(t == 1){
            x = i32();
            y = i32();
            heaps[x].push(y);
        }else if(t == 2){
            x = i32();
            fprintf(g,"%d\n",heaps[x].top());
            heaps[x].pop();
        }else{
            x = i32();
            y = i32();
            heaps[x].merge(heaps[y]);
            heaps[y] = Heap();
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
