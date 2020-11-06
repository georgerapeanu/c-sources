#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int SIGMA = 'z' - 'a';

struct trie_node_t{
    trie_node_t *son[SIGMA + 1];
    vector<int> sg;
    int cnt;

    trie_node_t(){
        cnt = 0;
        memset(son,0,sizeof(son));
        sg = vector<int>();
    }
} *root;

void ins(trie_node_t *root,const string &word,int pos){
    if(pos >= (int)word.size()){
        root->cnt++;
        return ;
    }
    if(root->son[word[pos] - 'a'] == NULL){
        root->son[word[pos] - 'a'] = new trie_node_t();
    }
    ins(root->son[word[pos] - 'a'],word,pos + 1);
}

int dfs(trie_node_t *root){
//    printf("%d ",root);printf("%d\n",root->cnt);
    vector<int> sg;
    int xo = 0;
    for(int i = 0;i <= SIGMA;i++){
        if(root->son[i] != NULL){
            sg.push_back(dfs(root->son[i]));
            xo ^= sg.back();
        }
        else{
            sg.push_back(0);
        }
    }
    for(int i = 0;i <= SIGMA;i++){
        if(root->son[i] != NULL){
            xo ^= sg[i];
            for(auto it:root->son[i]->sg){
                root->sg.push_back(xo ^ it);
            }
            xo ^= sg[i];
        }
    }

    if(root->cnt){
        root->sg.push_back(xo);
    }

    int mex = 0;

    sort(root->sg.begin(),root->sg.end());

    for(int i = 0;i < (int)root->sg.size();i++){
        if(root->sg[i] == mex){
            mex++;
        }
    }   
    
    return mex;
}

int main(){

    root = new trie_node_t();

    int n;
    string s;

    cin >> n;

    while(n--){
        cin >> s;
        ins(root,s,0);
    }

    int ans = 0;

    dfs(root);

    for(auto it:root->sg){
    //    printf("%d ",it);
        ans += (it == 0);
    }

    printf("%d\n",ans);

    return 0;
}
