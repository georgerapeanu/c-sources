#include <bits/stdc++.h>

using namespace std;

struct node_t {
    node_t *sons[2];
    int dp;

    node_t() {
        sons[0] = sons[1] = NULL;
        dp = 0;
    }

}*root;

int n;
int val;

void ins(node_t *root,int val,int pos) {
    if(pos < 0) {
        return ;
    }

    int b = (val >> pos) & 1;

    if(root->sons[b] == NULL) {
        root->sons[b] = new node_t();
    }

    ins(root->sons[b],val,pos - 1);
}

void dfs(node_t *root,int lvl) {
    if(root == NULL) {
        return ;
    }

    dfs(root->sons[0],lvl - 1);
    dfs(root->sons[1],lvl - 1);

    if(root->sons[0] == NULL && root->sons[1] == NULL) {
        root->dp = 0;
        return ;
    }

    if(root->sons[0] == NULL) {
        root->dp = root->sons[1]->dp;
        return ;
    }

    if(root->sons[1] == NULL) {
        root->dp = root->sons[0]->dp;
        return ;
    }

    root->dp = (1 << lvl) + min(root->sons[0]->dp,root->sons[1]->dp);
}

int main() {

    root = new node_t();

    scanf("%d",&n);

    while(n--) {
        scanf("%d",&val);
        ins(root,val,29);
    }

    dfs(root,29);

    printf("%d\n",root->dp);

    return 0;
}
