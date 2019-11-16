#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e6;
const int HOME = 2;

int n,m;
int a[NMAX + 5];
int b[NMAX + 5];
int p[NMAX + 5];
int q[NMAX + 5];
long long s[NMAX + 5];
long long t[NMAX + 5];

int pref_lin[NMAX + 5];
int pref_col[NMAX + 5];

long long dp[100][100];

vector<int> event[NMAX + 5];

struct node_t {
    long long base_offset;
    long long sum;
    long long val;
    int lazy;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.base_offset = 0;
        ans.sum = (this->sum) + other.sum;
        ans.val = 0;
        ans.lazy = 0;
        return ans;
    }
} aint[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == 0) {
        return ;
    }

    aint[2 * nod].lazy |= aint[nod].lazy;
    aint[2 * nod + 1].lazy |= aint[nod].lazy;

    aint[2 * nod].val = aint[2 * nod].sum = 0;
    aint[2 * nod + 1].val = aint[2 * nod + 1].sum = 0;

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr) {
    aint[nod].base_offset = 0;
    aint[nod].sum = 0;
    aint[nod].val = 0;
    aint[nod].lazy = 0;

    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
}

void update_val(int nod,int st,int dr,int pos,int delta) { ///+= delta
    propag(nod,st,dr);

    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].val += delta;
        if(st != 0)aint[nod].val = max(0LL,aint[nod].val);
        aint[nod].sum = aint[nod].val;
        return ;
    }

    int mid = (st + dr) / 2;

    update_val(nod * 2,st,mid,pos,delta);
    update_val(nod * 2 + 1,mid + 1,dr,pos,delta);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_offset(int nod,int st,int dr,int pos,int delta,bool initial = false) { /// += delta_offset
    propag(nod,st,dr);
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].base_offset += delta;
        if(initial == false) {
            aint[nod].val -= delta;
            aint[nod].val = max(aint[nod].val,0LL);
        }
        aint[nod].sum = aint[nod].val;
        return ;
    }

    int mid = (st + dr) / 2;

    update_offset(nod * 2,st,mid,pos,delta,initial);
    update_offset(nod * 2 + 1,mid + 1,dr,pos,delta,initial);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_0(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return ;
    }
    if(l <= st && dr <= r) {
        aint[nod].lazy = 1;
        aint[nod].sum = 0;
        aint[nod].val = 0;
        return ;
    }

    int mid = (st + dr) / 2;

    update_0(nod * 2,st,mid,l,r);
    update_0(nod * 2 + 1,mid + 1,dr,l,r);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}
long long query_sum(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return 0;
    }

    if(l <= st && dr <= r) {
        return aint[nod].sum;
    }

    int mid = (st + dr) / 2;

    return query_sum(nod * 2,st,mid,l,r) + query_sum(nod * 2 + 1,mid + 1,dr,l,r);
}

long long get_val(int nod,int st,int dr,int pos) {
    propag(nod,st,dr);
    if(dr < pos || st > pos) {
        return -1;
    }

    if(st == dr) {
        return aint[nod].val;
    }

    int mid = (st + dr) / 2;

    return max(get_val(nod * 2,st,mid,pos),get_val(nod * 2 + 1,mid + 1,dr,pos));
}

int get_pos_sum(int pos,int elem) { ///TODO can be improved
    int l = pos - 1,r = n + 1;
    while(r - l > 1) {
        int mid = (l + r) / 2;
        if(query_sum(1,0,n,pos,mid) + elem >= 0) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    return r;
}

long long get_time(int i,int j) {
    static int last_lin = 0;
    static int last_col = 0;
    static long long last_sum = 0;

    while(last_lin > i) {
        last_sum -= a[last_lin];
        last_lin--;
    }

    while(last_lin < i) {
        last_lin++;
        last_sum += a[last_lin];
    }

    while(last_col > j) {
        last_sum -= b[last_col];
        last_col--;
    }

    while(last_col < j) {
        last_col++;
        last_sum += b[last_col];
    }

    return last_sum;
}

void afis(int nod,int st,int dr,long long &sum) {
    propag(nod,st,dr);
    if(st == dr) {
        //    sum += aint[nod].val + aint[nod].base_offset;
//        printf("%lld ",sum);
        printf("(%lld,%lld) ",aint[nod].val,aint[nod].base_offset);
        return ;
    }

    int mid = (st + dr) / 2;
    afis(nod * 2,st,mid,sum);
    afis(nod * 2 + 1,mid + 1,dr,sum);
}

long long get_ans(int nod,int st,int dr) {
    propag(nod,st,dr);
    if(st == dr) {
        return (aint[nod].val + aint[nod].base_offset);
    }

    int mid = (st + dr) / 2;

    return get_ans(nod * 2,st,mid) + get_ans(nod * 2 + 1,mid + 1,dr);
}

int main() {

    scanf("%d %d",&m,&n);

    for(int i = 1; i <= m; i++) {
        scanf("%d %lld %d",&b[i],&t[i],&q[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d %lld %d",&a[i],&s[i],&p[i]);
    }

    for(int j = 0; j <= m; j++) {
        int l = -1,r = n + 1;
        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(get_time(mid,j) <= t[j]) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        pref_col[j] =  l;
    }


    for(int i = 0; i <= n; i++) {
        int l = -1,r = m + 1;

        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(get_time(i,mid) <= s[i]) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        pref_lin[i] = l;
    }

    if(HOME) {
        printf("STARTDP\n");
        for(int j = 0; j <= m; j++) {
            for(int i = 0; i <= n; i++) {
                if(i == 0 && j == 0) {
                    dp[i][j] = 0;
                }
                else {
                    if(i != 0) {
                        //dp[i][j] = dp[i - 1][j] + p[i] * (pref_lin[i] >= j);
                        dp[i][j] = dp[i - 1][j] + p[i] * (get_time(i,j) <= s[i]);
                        if(j > 0) {
                            //dp[i][j] = max(dp[i][j],dp[i][j - 1] + q[j] * (pref_col[j] >= i));
                            dp[i][j] = max(dp[i][j],dp[i][j - 1] + q[j] * (get_time(i,j) <= t[j]));
                        }
                    }
                    else {
//                    dp[i][j] = dp[i][j - 1] + q[j] * (pref_col[j] >= i);
                        dp[i][j] = dp[i][j - 1] + q[j] * (get_time(i,j) <= t[j]);
                    }
                }
                printf("%lld ",dp[i][j]);
            }
            printf("\n");
        }
        printf("ENDDP\n");
    }

    if(HOME == 2)return 0;

    build(1,0,n);

    for(int i = 1; i <= n; i++) {
        if(pref_lin[i] > -1) {
            update_offset(1,0,n,i,p[i],true);
            event[pref_lin[i] + 1].push_back(i);
            if(HOME)printf("add offset %d %d\n",i,p[i]);
        }
    }
    if(HOME) {
        long long tmp = 0;
        afis(1,0,n,tmp);
        printf("\n");
    }
    for(int j = 1; j <= m; j++) {
        for(auto it:event[j]) {
            update_offset(1,0,n,it,-p[it]);
            if(-p[it] > 0) {
                int k = get_pos_sum(it + 1,p[it]);
                if(k <= n) {
                    update_val(1,0,n,k,(query_sum(1,0,n,it + 1,k) + p[it]) - get_val(1,0,n,k));
                }
                if(it + 1 <= k - 1) {
                    update_0(1,0,n,it + 1,k - 1);
                }
            }
            if(HOME) printf("rem offset %d %d\n",it,-p[it]);
        }
        if(pref_col[j] > -1) {
            update_val(1,0,n,0,q[j]);
            if(HOME)printf("col trans %d %d\n",pref_col[j] + 1,-q[j]);
            int k = get_pos_sum(pref_col[j] + 1,-q[j]);
            if(HOME)printf("pos found %d\n",k);
            if(k <= n) {
                update_val(1,0,n,k,(query_sum(1,0,n,pref_col[j] + 1,k) - q[j]) - get_val(1,0,n,k));
            }
            if(pref_col[j] + 1 <= k - 1) {
                update_0(1,0,n,pref_col[j] + 1,k - 1);
            }
        }
        if(HOME) {
            long long tmp = 0;
            afis(1,0,n,tmp);
            printf("\n");
        }
    }

    printf("%lld\n",get_ans(1,0,n));

    return 0;
}
