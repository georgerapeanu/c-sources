#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

inline long long det(pair<long long,long long> a,pair<long long,long long> b,pair<long long,long long> c) {
    return a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second);
}

inline bool cmp(pair<long long,long long> a,pair<long long,long long> b) {
    return det(make_pair(0,0),a,b) > 0;
}

struct node_t {

    int lst_ind;
    vector<pair<long long,long long> > points;

    node_t operator + (const node_t &other)const {
        node_t ans;
       
        if(this->points.size() == 0){
            ans = *this;
            ans.lst_ind = this->points.size() - 1;
            return ans;
        }
        if(other.points.size() == 0){
            ans = other;
            ans.lst_ind = other.points.size() - 1;
            return ans;
        }

        int i = 0;
        int j = 0;

        while(i < (int)points.size() && j < (int)other.points.size()){
            pair<long long,long long> p;
            if(cmp(points[i],other.points[j]) == true){
                p = points[i++];
            }
            else{
                p = other.points[j++];
            }
            while((int)ans.points.size() > 2 && det(ans.points[(int)ans.points.size() - 2],ans.points[(int)ans.points.size() - 1],p) < 0){
                ans.points.pop_back();
            }
            ans.points.push_back(p);
        }
        while(i < (int)points.size()){
            pair<long long,long long> p;
            p = points[i++];
            while((int)ans.points.size() > 2 && det(ans.points[(int)ans.points.size() - 2],ans.points[(int)ans.points.size() - 1],p) < 0){
                ans.points.pop_back();
            }
            ans.points.push_back(p);
        }
        while(j < (int)other.points.size()){
            pair<long long,long long> p;
            p = other.points[j++];
            while((int)ans.points.size() > 2 && det(ans.points[(int)ans.points.size() - 2],ans.points[(int)ans.points.size() - 1],p) < 0){
                ans.points.pop_back();
            }
            ans.points.push_back(p);
        }

        ans.lst_ind = (int)ans.points.size() - 1;

        return ans;
    }

    long long query(pair<long long,long long> v) {
        while(lst_ind - 1 >= 0 && points[lst_ind].first * v.first + points[lst_ind].second * v.second <= points[lst_ind - 1].first * v.first + points[lst_ind - 1].second * v.second) {
            lst_ind--;
        }
        return points[lst_ind].first * v.first + points[lst_ind].second * v.second;
    }

    node_t() {
        lst_ind = 0;
        points = vector<pair<long long,long long> >();
    }

};

class SegmentTree {
    int n;
    vector<node_t> aint;

public:

    SegmentTree(int n,vector<pair<long long,long long> > v) {
        this->n = n;
        this->aint = vector<node_t>(2 * n + 5,node_t());
        for(int i = 1;i <= n;i++){
            aint[n + i].points = {v[i]};
        }
        for(int i = n;i;i--){
            aint[i] = aint[(i << 1)] + aint[(i << 1) | 1];
        }
    }

    long long query(int l,int r,pair<long long,long long> v) {
        long long ans = 0;
        l += n;
        r += n + 1;

        for(;l < r;l >>= 1,r >>= 1){
            if(l & 1){
                ans = max(ans,aint[l++].query(v));
            }
            if(r & 1){
                ans = max(ans,aint[--r].query(v));
            }
        }

        return ans;
    }

};

int n;
int a[NMAX + 5];
int b[NMAX + 5];

long long solve(int st,int dr) {
    if(st == dr) {
        return 1LL * a[st] * b[st];
    }

    int mid = (st + dr) / 2;

    long long ans = max(solve(st,mid),solve(mid + 1,dr));

    int mi_a = 1e9;
    int mi_b = 1e9;

    int i_a = mid;
    int i_b = mid;
    int i2_b = mid;

    vector<pair<long long,long long> > points = {};

    int mip_b = 1e9;

    for(int i = mid; i >= st; i--) {
        mip_b = min(mip_b,b[i]);
        points.push_back({1LL * mip_b,1LL * mip_b * (1 - i)});
    }
    points.push_back({0LL,0LL});
    reverse(points.begin(),points.end());

    SegmentTree aint(mid - st + 1,points);

    for(int i = mid + 1; i <= dr; i++) {
        mi_a = min(mi_a,a[i]);
        mi_b = min(mi_b,b[i]);
        while(i_a >= st && a[i_a] >= mi_a) {
            i_a--;
        }
        while(i_b >= st && b[i_b] > mi_b) {
            i_b--;
        }
        while(i2_b >= st && b[i2_b] >= mi_b) {
            i2_b--;
        }
        ans = max(ans,1LL * mi_a * mi_b * (i - max(i_a,i2_b)));
        if(i_a + 1 <= i_b) {
            ans = max(ans,aint.query(i_a + 1 - (st - 1),i_b - (st - 1),make_pair(1LL * mi_a * i,1LL * mi_a)));
        }
        ///[i_a + 1,i_b]
    }
    return ans;
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans;
}

int main() {

    n = i32();

    for(int i = 1; i <= n; i++) {
        a[i] = i32();
        b[i] = i32();
    }

    long long ans = 0;

    ans = max(ans,solve(1,n));
    ans = max(ans,solve(1,n));
    swap(a,b);
    ans = max(ans,solve(1,n));
    reverse(a + 1,a + 1 + n);
    reverse(b + 1,b + 1 + n);
    ans = max(ans,solve(1,n));
    swap(a,b);

    printf("%lld\n",ans);

    return 0;
}
