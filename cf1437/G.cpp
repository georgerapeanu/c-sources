#include <bits/stdc++.h>

using namespace std;

struct node_t{
    node_t *son['z' - 'a' + 1];
    node_t *fail;
    int max_fail_val;

    node_t(){
        max_fail_val = -1;
        memset(son,0,sizeof(son));
        fail = NULL;
    };

};

void ins(node_t *root,const string &s,int pos,int val){
    if(pos >= (int)s.size()){
        s->max_fail_val = max(s->max_fail_val,val);
        return ;
    }
    if(root->son[s[pos] - 'a'] == NULL){
        root->son[s[pos] - 'a'] = new node_t();
    }
    ins(root->son[s[pos] - 'a'],s,pos + 1,val);
}

void calculate_fails(node_t *root){
    queue<node_t*> q;
    q.push(root);

    while(!q.empty()){
        root = q.front();
        q.pop();
        if(root->fail == NULL){
            root->max_fail_val = max(root->max_fail_val,root->fail->max_fail_val);
        }
        for(int i = 0;i <= 'z' - 'a';i++){
            if(root->son[i] != NULL){
                node_t *tmp = root->fail;
                while(tmp != NULL && tmp->son[i] == NULL){
                    tmp = tmp->fail;
                }
                if(tmp != NULL){
                    tmp = tmp->son[i];
                }
                root->son[i]->fail = tmp;
                q.push(root->son[i]);
            }
        }
    }
}

void query(node_t &real_root,node_t *root,const string &s,int pos,int &ans){
    ans = max(ans,root->max_fail_val);
    if(pos >= (int)s.size()){
        return ; 
    }

    while(root != NULL && root->son[s[pos] - 'a'] == NULL){
        root = root->fail;
    }

    if(root == NULL){
        root = real_root;
        query(real_root,root,s,pos + 1,ans);
    }
    else{
        root = root->son[s[pos] - 'a'];
        query(real_root,root,s,pos + 1,ans);
    }
}

int main(){

    node_t *root = new node_t();

    int n,q;

    cin >> n >> q;

    while(n--){
        string s;
        cin >>s
    }

    return 0;
}
