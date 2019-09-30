#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int SIGMA = 4;

const int BASE = 5;
const int MOD1 = 1e9 + 7;
const int MOD2 = 666013;

map<char,int> to_norm;

struct hsh_t {
    int h1;
    int h2;
    int len;

    hsh_t() {
        h1 = h2 = len = 0;
    }

    void add_back(int x) {
        x++;
        this->len++;
        this->h1 = (1LL * this->h1 * BASE + x) % MOD1;
        this->h2 = (1LL * this->h2 * BASE + x) % MOD2;
    }

    bool operator < (const hsh_t &other)const {
        if(this->h1 != other.h1) {
            return this->h1 < other.h1;
        }
        if(this->h2 != other.h2) {
            return this->h2 < other.h2;
        }
        return this->len < other.len;
    }
};

struct trie {
    int st,dr;
    int cnt;
    trie *sons[SIGMA];

    trie() {
        st = dr = 0;
        cnt = 0;
        memset(sons,0,sizeof(sons));
    }
} *root;

void ins(trie *root,char *a) {
    if(*a == '\0' || *a == '\n') {
        root->cnt++;
        return ;
    }

    if(root->sons[to_norm[(*a)]] == NULL) {
        root->sons[to_norm[(*a)]] = new trie();
    }

    ins(root->sons[to_norm[(*a)]],a + 1);
}

vector<pair<hsh_t,int> > pos;

int last = 0;
vector<int> stuff;
void dfs(trie *root) {
    root->st = ++last;
    if(root->cnt > 0) {
        hsh_t tmp;
        for(int i = (int)stuff.size() - 1; i >= 0; i--) {
            tmp.add_back(stuff[i]);
            for(int x = 0; x < root->cnt; x++) {
                pos.push_back({tmp,root->st});
            }
        }
    }
    for(int i = 0; i < SIGMA; i++) {
        if(root->sons[i] != NULL) {
            stuff.push_back(i);
            dfs(root->sons[i]);
            stuff.pop_back();
        }
    }
    root->dr = last;
}

int n,m;
char a[int(1e5) + 5];
char b[int(1e5) + 5];

int get_ans(trie *root,char *a,char *b) {
    if(*a != '\n' && *a != '\0') {
        if(root->sons[to_norm[*a]] == NULL) {
            return 0;
        }
        return get_ans(root->sons[to_norm[*a]],a + 1,b);
    }

    int len = 0;

    while(b[len] != '\n' && b[len] != '\0') {
        len++;
    }

    len--;

    hsh_t tmp;

    while(len >= 0) {
        tmp.add_back(to_norm[b[len]]);
        len--;
    }


    return lower_bound(pos.begin(),pos.end(),make_pair(tmp,root->dr + 1)) - lower_bound(pos.begin(),pos.end(),make_pair(tmp,root->st));
}

int main() {

    to_norm['A'] = 0;
    to_norm['C'] = 1;
    to_norm['G'] = 2;
    to_norm['U'] = 3;

    root = new trie();

    scanf("%d %d\n",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%s\n",a);
        ins(root,a);
    }

    dfs(root);

    sort(pos.begin(),pos.end());

    for(int i = 1; i <= m; i++) {
        scanf("%s %s\n",a,b);
        printf("%d\n",get_ans(root,a,b));
    }

    return 0;
}
