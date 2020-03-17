#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("ahocorasick.in","r");
FILE *g = fopen("ahocorasick.out","w");

struct trie{
    trie* fail;
    int cnt;
    vector<int> patterns;
    trie* sons['z' - 'a' + 1];

    trie(){
        memset(sons,0,sizeof(sons));
        fail = NULL;
        cnt = 0;
        patterns = vector<int>();
    }
}*root;

void ins(trie *root,char *c,int id){
    if(*c == '\n' || *c == '\0'){
        root->patterns.push_back(id);
        return;
    }
    if(root->sons[*c - 'a'] == NULL){
        root->sons[*c - 'a'] = new trie();
    }

    ins(root->sons[*c - 'a'],c + 1,id);
}

int n;
char c[1000005];
char p[10005];


trie *q[1000005];
int st,dr;
int ans[105];

int main(){

    root = new trie();

    fgets(c + 1,1000005,f);
    fscanf(f,"%d\n",&n);

    for(int i = 1;i <= n;i++){
        fgets(p + 1,10005,f);
        ins(root,p + 1,i);
    }


    root->fail = root;
    q[st = dr = 1] = root;

    while(st <= dr){
        trie* tmp = q[st++];
        for(int i = 0;i <= 'z' - 'a';i++){
            if(tmp->sons[i] != NULL){
                trie* a = tmp->fail;
                while(a != root && a->sons[i] == NULL){
                    a = a->fail;
                }
                if(a->sons[i] != NULL && a != tmp){
                    a = a->sons[i];
                }
                tmp->sons[i]->fail = a;
                q[++dr] = tmp->sons[i];
            }
        }
    }

    trie* tmp = root;

    for(int i = 1;c[i] != '\0' && c[i] != '\n';i++){

        while(tmp != root && tmp->sons[c[i] - 'a'] == NULL){
            tmp = tmp->fail;
        }
        if(tmp->sons[c[i] - 'a'] != NULL){
            tmp = tmp->sons[c[i] - 'a'];
        }
        tmp->cnt++;
    }

    for(int i = dr;i;i--){
        for(auto it:q[i]->patterns){
            ans[it] += q[i]->cnt;
        }
        q[i]->fail->cnt += q[i]->cnt;
    }

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d\n",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
