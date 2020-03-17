#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> aint;
string c_s;
vector<int> lft;
vector<int> rgt;
vector<int> prefsum;
vector<int> root;///root[i + n] = the root of aint if the offset is equal to i
vector<vector<int> > events; ///events[i + n] = positions with prefsum[pos] equal to i

int new_node() {
    aint.push_back(0);
    rgt.push_back(0);
    lft.push_back(0);
    return (int)aint.size() - 1;
}

void build(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod] = (c_s[st] == 'B' ? st:-st);
        return ;
    }

    int a = new_node();
    int b = new_node();

    lft[nod] = a;
    rgt[nod] = b;

    int mid = (st + dr) / 2;

    build(lft[nod],st,mid);
    build(rgt[nod],mid + 1,dr);

    aint[nod] = aint[lft[nod]] + aint[rgt[nod]];
}

int update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return nod;
    }
    if(st == dr) {
        int tmp = new_node();
        aint[tmp] = val;
        return tmp;
    }

    int mid = (st + dr) / 2;

    int a = update(lft[nod],st,mid,pos,val);
    int b = update(rgt[nod],mid + 1,dr,pos,val);

    int tmp = new_node();

    lft[tmp] = a;
    rgt[tmp] = b;

    aint[tmp] = aint[lft[tmp]] + aint[rgt[tmp]];

    return tmp;
}

long long query(int nod,int st,int dr,int l,int r) {
    if(r < st || l > dr) {
        return 0;
    }
    if(l <= st && dr <= r) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return query(lft[nod],st,mid,l,r) + query(rgt[nod],mid + 1,dr,l,r);
}

void init(string s) {
    c_s = s;
    int n = s.size();
    prefsum.resize(n);
    events.resize(2 * n + 5);
    root.resize(2 * n + 5);

    for(int i = 0; i < n; i++) {
        prefsum[i] = (s[i] == 'B' ? 1:-1) + (i > 0 ? prefsum[i - 1]:0);
        events[prefsum[i] + n].push_back(i);
    }


    /*    aint.reserve(22 * n);///cu sistem de submit as putea calibra mai bine constante
        lft.reserve(22 * n);
        rgt.reserve(22 * n);
    */
    new_node();
    build(0,0,n - 1);
    root[2 * n + 1] = 0;

    for(int offset = n; offset >= -n; offset--) {
        root[n + offset] = root[n + offset + 1];
        for(auto it:events[offset + n + 1]) {
            if(s[it] == 'B') {
                root[n + offset] = update(root[n + offset],0,n - 1,it,-it);
            }
        }
        for(auto it:events[offset + n]) {
            if(s[it] == 'F') {
                root[n + offset] = update(root[n + offset],0,n - 1,it,it);
            }
        }
    }
}

vector<long long> dance(vector<int> l,vector<int> r) {
    int n = c_s.size();
    vector<long long> ans;

    for(int i = 0; i < (int)l.size(); i++) {
        l[i]--;
        r[i]--;
        if(prefsum[r[i]] - (l[i] > 0 ? prefsum[l[i] - 1]:0) != 0) {
            ans.push_back(0);
            continue;
        }
        ans.push_back(query(root[n + (l[i] > 0 ? prefsum[l[i] - 1]:0)],0,n - 1,l[i],r[i]));
    }

    return ans;
}

string s;
int q;
vector<int> l;
vector<int> r;

int main() {

    cin >> s;

    cin >> q;

    for(int i = 1; i <= q; i++) {
        int x,y;
        cin >> x >> y;
        l.push_back(x);
        r.push_back(y);
    }

    init(s);

    vector<long long> v = dance(l,r);

    for(auto it:v) {
        printf("%lld\n",it);
    }

    return 0;
}
