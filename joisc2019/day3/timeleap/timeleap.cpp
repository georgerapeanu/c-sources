#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

const int NMAX = 3e5;

struct node_t {
    int breaking_point;
    int l,r;
    int real_l,real_r;
    long long cst;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.cst = this->cst + other.cst;
        ans.real_l = max(this->real_l,other.real_l);
        ans.real_r = min(this->real_r,other.real_r);
        if(ans.real_l <= ans.real_r) {
            ans.breaking_point = ans.real_r;
            ans.cst = 0;
            ans.l = ans.real_l;
            ans.r = ans.real_r;
        }
        else {
            if(this->real_l <= this->real_r) {
                if(other.real_l <= other.real_r) {
                    if(this->r < other.l) {
                        ans.cst += 0;
                        ans.l = ans.r = other.l;
                        ans.breaking_point = this->r;
                    }
                    else {
                        ans.cst += this->l - other.r;
                        ans.l = ans.r = other.r;
                        ans.breaking_point = this->l;
                    }
                }
                else {
                    ans.l = other.l;
                    ans.r = other.r;
                    if(other.breaking_point > this-> r) {
                        ans.breaking_point = this->breaking_point;
                        ans.cst += 0;
                    }
                    else if(other.breaking_point >= this->l) {
                        ans.breaking_point = other.breaking_point;
                        ans.cst += 0;
                    }
                    else {
                        ans.breaking_point = this->l;
                        ans.cst += this->l - other.breaking_point;
                    }
                }
            }
            else {
                if(this->l >= other.breaking_point) {
                    ans.cst += this->l - other.breaking_point;
                }
                ans.breaking_point = this->breaking_point;
                if(other.r < this->l) {
                    ans.l = ans.r = other.r;
                }
                else if(other.l <= this->l) {
                    ans.l = ans.r = this->l;
                }
                else {
                    ans.l = ans.r = other.l;
                }
            }
        }
        return ans;
    }
};

class SegTree {
public:

    int n;
    node_t aint[NMAX * 4 + 5];

    void build(int nod,int st,int dr,pair<int,int> v[]) {
        if(st == dr) {
            aint[nod].l = aint[nod].real_l = v[st].first;
            aint[nod].r = aint[nod].real_r = v[st].second;
            aint[nod].breaking_point = aint[nod].real_r;
            aint[nod].cst = 0;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,v);
        build(nod * 2 + 1,mid + 1,dr,v);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int pos,pair<int,int> val) {
        if(pos < st || pos > dr) {
            return ;
        }
        if(st == dr) {
            aint[nod].l = aint[nod].real_l = val.first;
            aint[nod].r = aint[nod].real_r = val.second;
            aint[nod].breaking_point = aint[nod].real_r;
            aint[nod].cst = 0;
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    SegTree(int n,pair<int,int> v[]) {
        this->n = n;
        build(1,1,n,v);
    }

    SegTree() {
        this->n = 0;
        memset(this->aint,0,sizeof(this->aint));
    }

    node_t query(int nod,int st,int dr,int l,int r) {
        if(l <= st && dr <= r) {
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        if(l > mid) {
            return query(nod * 2 + 1,mid + 1,dr,l,r);
        }
        else if(r <= mid) {
            return query(nod * 2,st,mid,l,r);
        }
        else {
            return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
        }
    }
};

int n,q;
pair<int,int> fst[NMAX + 5];
pair<int,int> snd[NMAX + 5];

SegTree norm;
SegTree rev;

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i < n; i++) {
        scanf("%d %d",&fst[i].first,&fst[i].second);
        fst[i].second--;
        snd[n - i] = fst[i];
    }

    for(int i = 1; i < n; i++) {
        fst[i].first -= i;
        fst[i].second -= i;
        snd[i].first -= i;
        snd[i].second -= i;
    }

    if(n == 1) {
        while(q--) {
            int t;
            scanf("%d",&t);
            if(t == 1) {
                int p,l,r;
                scanf("%d %d %d",&p,&l,&r);
            }
            else {
                int a,b,c,d;
                scanf("%d %d %d %d",&a,&b,&c,&d);
                printf("%d\n",max(0,b - d));
            }
        }
        return 0;
    }

    norm.n = n - 1;
    norm.build(1,1,n - 1,fst);
    rev.n = n - 1;
    rev.build(1,1,n - 1,snd);

    while(q--) {
        int t;
        scanf("%d",&t);

        if(t == 1) {
            int p,l,r;
            scanf("%d %d %d",&p,&l,&r);
            r--;
            norm.update(1,1,n - 1,p, {l - p,r - p});
            rev.update(1,1,n - 1,n - p, {l - (n - p),r - (n - p)});
        }
        else {
            int a,b,c,d;
            scanf("%d %d %d %d",&a,&b,&c,&d);
            if(a == c) {
                printf("%lld\n",max(0LL,(long long)b - d));
            }
            else if(a < c) {
                b -= a;
                d -= c;
                node_t tmp = norm.query(1,1,n - 1,a,c - 1);
                int ext_wh = -1;

                if(b > tmp.r) {
                    ext_wh = tmp.r;
                }
                else if(b >= tmp.l) {
                    ext_wh = b;
                }
                else {
                    ext_wh = tmp.l;
                }

                long long ans = tmp.cst + max(0,b - tmp.breaking_point) + max(0,ext_wh - d);

                printf("%lld\n",ans);
            }
            else {
                a = n + 1 - a;
                c = n + 1 - c;
                b -= a;
                d -= c;
                node_t tmp = rev.query(1,1,n - 1,a,c - 1);
                int ext_wh = -1;

                if(b > tmp.r) {
                    ext_wh = tmp.r;
                }
                else if(b >= tmp.l) {
                    ext_wh = b;
                }
                else {
                    ext_wh = tmp.l;
                }
                long long ans = tmp.cst + max(0,b - tmp.breaking_point) + max(0,ext_wh - d);

                printf("%lld\n",ans);
            }
        }
    }

    return 0;
}
