#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int a[NMAX + 5];
int b[NMAX + 5];
int c[NMAX + 5];

map<pair<int,int>,vector<int> > nodes;
bool viz[NMAX + 5];

int nxt[NMAX + 5];

pair<int,int> get_pair(int a,int b) {
    if(a > b) {
        swap(a,b);
    }
    return {a,b};
}

pair<pair<int,int>,int> get_tuple(int a,int b,int c) {
    vector<int> v = {a,b,c};
    sort(v.begin(),v.end());
    return {{v[0],v[1]},v[2]};
}

map<pair<pair<int,int>,int>,int> chestie;

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);

        nodes.clear();
        chestie.clear();

        for(int i = 1; i <= n; i++) {
            viz[i] = nxt[i] = 0;
        }

        for(int i = 1; i <= n - 2; i++) {
            scanf("%d %d %d",&a[i],&b[i],&c[i]);
            nodes[get_pair(a[i],b[i])].push_back(c[i]);
            nodes[get_pair(b[i],c[i])].push_back(a[i]);
            nodes[get_pair(c[i],a[i])].push_back(b[i]);
            chestie[get_tuple(a[i],b[i],c[i])] = i;
        }

        nxt[a[1]] = b[1];
        nxt[b[1]] = c[1];
        nxt[c[1]] = a[1];
        viz[a[1]] = 1;
        viz[b[1]] = 1;
        viz[c[1]] = 1;

        vector<pair<int,int> > q = {get_pair(a[1],b[1]),get_pair(b[1],c[1]),get_pair(c[1],a[1])};

        vector<int> order = {chestie[get_tuple(a[1],b[1],c[1])]};

        for(int i = 0; i < (int)q.size(); i++) {
            for(auto it:nodes[q[i]]) {
                if(viz[it] == false) {
                    if(nxt[q[i].first] == q[i].second) {
                        nxt[q[i].first] = it;
                        nxt[it] = q[i].second;
                    }
                    else {
                        nxt[q[i].second] = it;
                        nxt[it] = q[i].first;
                    }
                    viz[it] = true;
                    q.push_back(get_pair(q[i].first,it));
                    q.push_back(get_pair(q[i].second,it));
                    order.push_back(chestie[get_tuple(q[i].first,q[i].second,it)]);
                }
            }

        }

        for(int nod = 1,i = 1; i <= n; nod = nxt[nod],i++) {
            printf("%d ",nod);
        }
        printf("\n");
        reverse(order.begin(),order.end());
        for(auto it:order) {
            printf("%d ",it);
        }
        printf("\n");
    }

    return 0;
}
