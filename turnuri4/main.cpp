#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

FILE *f = fopen("turnuri4.in","r");
FILE *g = fopen("turnuri4.out","w");

const int NMAX = 1e5;
const int VMAX = 1e9;

int n;
pair<int,int> v[NMAX + 5];

set<int> s;

pair<int,int> st[NMAX + 5];
pair<int,int> dr[NMAX + 5];

long long delta[NMAX + 5];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i].first);
        v[i].second = i;
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    s.insert(0);
    s.insert(n + 1);

    for(int i = 1;i <= n;i++){
        set<int> :: iterator it = s.lower_bound(v[i].second);

        dr[v[i].second].first = *it;

        it++;

        if(it != s.end()){
            dr[v[i].second].second = *it;
        }
        else{
            dr[v[i].second].second = -1;
        }

        it--;
        it--;

        st[v[i].second].first = *it;

        if(it != s.begin()){
            it--;
            st[v[i].second].second = *it;
        }
        else{
            st[v[i].second].second = -1;
        }

        s.insert(v[i].second);
    }

    long long overall = 0;

    for(int i = 1;i <= n;i++){
        overall += dr[i].first - st[i].first - 1;
        if(st[i].first > 0){
            delta[st[i].first] += st[i].first - st[i].second;
        }
        if(dr[i].first <= n){
            delta[dr[i].first] += dr[i].second - dr[i].first;
        }

        delta[i] += st[i].first - dr[i].first + 2;
    }

    for(int i = 1;i <= n;i++){
        fprintf(g,"%lld\n",overall + delta[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
