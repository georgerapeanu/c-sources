#include <bits/stdc++.h>
#include "weirdtree.h"
#define DIMN 300010
using namespace std;

struct segm_tree{
    long long sum;
    int maxi1, cntmaxi1, maxi2, lazy;
    /// lazy este cea mai mare valoare care poate sa apara ever in subarb
} aint[4*DIMN];

int v[DIMN], n;

segm_tree combine (segm_tree a , segm_tree b){
    segm_tree c;

    c.sum = a.sum + b.sum;

    if (a.maxi1 > b.maxi1){
        c.maxi1 = a.maxi1;
        c.cntmaxi1 = a.cntmaxi1;

        c.maxi2 = max(a.maxi2 , b.maxi1);
    }
    else if (a.maxi1 < b.maxi1){
        c.maxi1 = b.maxi1;
        c.cntmaxi1 = b.cntmaxi1;

        c.maxi2 = max(b.maxi2 , a.maxi1);
    }
    else { /// egale
        c.maxi1 = a.maxi1;
        c.cntmaxi1 = a.cntmaxi1 + b.cntmaxi1;

        c.maxi2 = max(b.maxi2 , a.maxi2);
    }

    c.lazy = max(a.lazy, b.lazy);

    return c;
}

void lazy_update (int nod , int st , int dr){
    /// the maximum value in the interval st , dr must be aint[nod].lazy
    if (st == dr)
        return;

    if (aint[nod].lazy < aint[2 * nod].maxi1){
        aint[2 * nod].sum = aint[2 * nod].sum - 1LL * aint[2 * nod].maxi1 * aint[2 * nod].cntmaxi1 +
                                                 1LL * aint[nod].lazy * aint[2 * nod].cntmaxi1;
        aint[2 * nod].maxi1 = aint[nod].lazy;
        aint[2 * nod].lazy = min(aint[2 * nod].lazy , aint[nod].lazy);
    }

    if (aint[nod].lazy < aint[2 * nod + 1].maxi1){
        aint[2 * nod + 1].sum = aint[2 * nod + 1].sum - 1LL * aint[2 * nod + 1].maxi1 * aint[2 * nod + 1].cntmaxi1 +
                                                 1LL * aint[nod].lazy * aint[2 * nod + 1].cntmaxi1;
        aint[2 * nod + 1].maxi1 = aint[nod].lazy;
        aint[2 * nod + 1].lazy = min(aint[2 * nod + 1].lazy , aint[nod].lazy);
    }

}

void build (int nod, int st , int dr){
    int mid = (st + dr)/2;

    if (st == dr){
        aint[nod].sum = v[st];
        aint[nod].maxi1 = v[st];
        aint[nod].cntmaxi1 = 1;
        aint[nod].maxi2 = 0;
        aint[nod].lazy = v[st];
        return;
    }

    build (2 * nod , st , mid);
    build (2 * nod + 1 , mid + 1 , dr);

    aint[nod] = combine(aint[2 * nod] , aint[2 * nod + 1]);

}

segm_tree query (int nod , int st , int dr, int l , int r){
    segm_tree sol = {0, 0 , 0 , 0, 0};
    int mid = (st + dr)/2;
    lazy_update (nod , st , dr);
    if (l <= st && dr <= r){
        sol = aint[nod];
        return sol;
    }

    if (l <= mid){
        sol = combine(sol , query(2 * nod , st , mid , l , r));
    }
    if (mid + 1 <= r){
        sol = combine(sol , query(2 * nod + 1 , mid + 1 , dr , l , r));
    }

    lazy_update (2 * nod , st , mid);
    lazy_update (2 * nod + 1 , mid + 1 , dr);
    aint[nod] = combine(aint[2 * nod] , aint[2 * nod + 1]);

    return sol;

}

void update (int nod , int st , int dr , int l , int r , int &capacity, int maxi){
    int mid = (st + dr)/2;

    lazy_update (nod , st , dr);

    if (st > r || dr < l || aint[nod].maxi1 <= maxi - (capacity > 0)){
        return; /// nothing to change here
    }

    if (l <= st && dr <= r && aint[nod].maxi1 > maxi - (capacity > 0) &&
         (aint[nod].maxi2 < maxi - (capacity > 0) || (aint[nod].cntmaxi1 == dr - st + 1)) &&
        (!capacity || capacity >= aint[nod].cntmaxi1)){
        if (!capacity){
            aint[nod].sum = aint[nod].sum - 1LL * aint[nod].maxi1 * aint[nod].cntmaxi1
                                          + 1LL * maxi * aint[nod].cntmaxi1;
            aint[nod].lazy = maxi;
            aint[nod].maxi1 = maxi;
        } else { /// the whole interval is 1 less
            aint[nod].sum = aint[nod].sum - 1LL * aint[nod].maxi1 * aint[nod].cntmaxi1
                                          + 1LL * (maxi - 1) * aint[nod].cntmaxi1;
            aint[nod].lazy = maxi - 1;
            aint[nod].maxi1 = maxi - 1;
            capacity -= aint[nod].cntmaxi1;
        }

        lazy_update (nod,st,dr);
        return;
    }

    if (l <= mid)
        update (2 * nod , st , mid , l , r , capacity , maxi);

    if (mid + 1 <= r)
        update (2 * nod + 1 , mid + 1 , dr , l , r , capacity , maxi);

    lazy_update (2 * nod , st , mid);
    lazy_update (2 * nod + 1 , mid + 1 , dr);

    aint[nod] = combine(aint[2 * nod] , aint[2 * nod + 1]);

}

void update_value (int nod , int st , int dr , int pos , int val){
    int mid = (st + dr)/2;

    lazy_update (nod , st , dr);

    if (st == dr){
        aint[nod].sum = val;
        aint[nod].maxi1 = val;
        aint[nod].cntmaxi1 = 1;
        aint[nod].maxi2 = 0;
        aint[nod].lazy = val;
        return;
    }

    if (pos <= mid)
        update_value (2 * nod , st , mid , pos , val);
    else
        update_value (2 * nod + 1 , mid + 1 , dr , pos , val);

    lazy_update (2 * nod , st , mid);
    lazy_update (2 * nod + 1 , mid + 1 , dr);

    aint[nod] = combine(aint[2 * nod] , aint[2 * nod + 1]);

}

void initialise (int N , int q , int h[]){
    int i;
    n = N;
    for (i = 1 ; i <= n ; i++){
        v[i] = h[i];
    }
    build (1 , 1 , n);
}

void cut (int l, int r, int k){
    segm_tree ans;
    long long cuts;
    int capacity;
    while (k){
        ans = query (1 , 1 , n , l , r);

        if (ans.maxi1 == 0){
            /// not much you can do
            return;
        }

        cuts = 1LL * (ans.maxi1 - ans.maxi2) * ans.cntmaxi1;

        if (cuts <= k){
            /// all values equal to maxi1 become equal to maxi2 in [l , r]
            k -= cuts;
            capacity = 0;
            update (1 , 1 , n , l , r , capacity, ans.maxi2);
        }
        else {
            /// too many values bigger than maxi2, do stuff
            int valueToReach = ans.maxi1 - k / ans.cntmaxi1;
            capacity = k % ans.cntmaxi1;
            update (1 , 1 , n , l , r , capacity , valueToReach);
            k = 0;
        }

    }
}

void magic (int i, int k){
    update_value (1 , 1 , n , i , k);
}

void fetchDebugData(int &count,int &max_count){
  count = max_count = -1;
}
long long inspect (int l, int r){
    return query(1 , 1 , n , l , r).sum;
}

/*int main()
{
    FILE *fin = fopen ("a.in", "r");
    FILE *fout = fopen ("a.out", "w");
    int n , q , i , tip , l , r , k;
    int h[DIMN];
    fscanf (fin,"%d%d",&n,&q);
    for (i = 1 ; i <= n ; i++){
       fscanf (fin,"%d",&h[i]);
    }

    initialise(n , q , h);

    for (;q;q--){
        fscanf (fin,"%d",&tip);
        if (tip == 1){
            /// chestia cu scadere
            fscanf (fin,"%d%d%d",&l,&r,&k);
            cut (l , r , k);
        } else if (tip == 2){
            /// chestia cu update un element
            fscanf (fin,"%d%d",&i,&k);
            magic(i , k);
        } else {
            /// query suma pe interval l r
            fscanf (fin,"%d%d",&l,&r);
            fprintf (fout,"%lld\n",inspect(l , r));
        }
    }
    return 0;
}*/
