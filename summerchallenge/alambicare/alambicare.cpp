#include <cstdio>

using namespace std;

FILE *f = fopen("alambicare.in","r");
FILE *g = fopen("alambicare.out","w");

const int NMAX = 2e5;
const int QMAX = 2e5;

class AINT {
public:
    int pref_sum[4 * NMAX + 5];
    int pos_neg[4 * NMAX + 5];

    void update(int nod,int st,int dr,int pos,int val) {
        if(dr < pos || st > pos) {
            return;
        }
        if(st == dr) {
            pref_sum[nod] += val;
            pos_neg[nod] = (pref_sum[nod] < 0 ? st:-1);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        pref_sum[nod] = pref_sum[nod * 2] + pref_sum[nod * 2 + 1];
        pos_neg[nod] = (pos_neg[nod * 2] != -1 ? pos_neg[nod * 2]:pos_neg[nod * 2 + 1]);
    }

    int get_sum(int nod,int st,int dr,int l,int r) {
        if(r < st || l > dr) {
            return 0;
        }

        if(l <= st && dr <= r) {
            return pref_sum[nod];
        }

        int mid = (st + dr) / 2;

        return get_sum(nod * 2,st,mid,l,r) + get_sum(nod * 2 + 1,mid + 1,dr,l,r);
    }

    int get_fst(int nod,int st,int dr,int l,int r) {
        if(r < st || l > dr) {
            return -1;
        }

        if(l <= st && dr <= r) {
            return pos_neg[nod];
        }

        int mid = (st + dr) / 2;

        int a = get_fst(nod * 2,st,mid,l,r);
        int b = get_fst(nod * 2 + 1,mid + 1,dr,l,r);

        return (a != -1 ? a:b);
    }

    void afis(int nod,int st,int dr) {
        if(st == dr) {
            printf("%d ",pref_sum[nod]);
            return ;
        }

        int mid = (st + dr) / 2;

        afis(nod * 2,st,mid);
        afis(nod * 2 + 1,mid + 1,dr);
    }
};

int n,q;
AINT norm_aint;
AINT rev_aint;

int solve(int l,int r) {
    int norm_fst = -1,norm_snd = -1;
    int rev_fst = -1,rev_snd = -1;

    norm_fst = norm_aint.get_fst(1,1,n,l + 1,r);
    if(norm_fst != -1) {
        norm_snd = norm_aint.get_fst(1,1,n,norm_fst + 1,r);
    }

    rev_fst = rev_aint.get_fst(1,1,n,n - r + 2,n - l + 1);

    if(rev_fst != -1) {
        rev_snd = rev_aint.get_fst(1,1,n,rev_fst + 1,n - l + 1);
    }

    if(norm_fst == -1) {
        return 0;
    }
    else if(rev_fst == -1 || (rev_snd == -1 && rev_aint.get_sum(1,1,n,1,n - l + 1) <= rev_aint.get_sum(1,1,n,1,n - r + 1))) {
        return 1;
    }
    else if(norm_snd == -1 && norm_aint.get_sum(1,1,n,1,r) <= norm_aint.get_sum(1,1,n,1,l)) {
        return 2;
    }
    else {
        return -1;
    }
}

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        int x;
        fscanf(f,"%d",&x);
        norm_aint.update(1,1,n,i,x);
        norm_aint.update(1,1,n,i + 1,-x);
        rev_aint.update(1,1,n,n - i + 1,x);
        rev_aint.update(1,1,n,n - i + 2,-x);
    }

    while(q--) {
        int t,l,r,val;
        fscanf(f,"%d %d %d",&t,&l,&r);
        if(t == 1) {
            fscanf(f,"%d",&val);
            norm_aint.update(1,1,n,l,val);
            norm_aint.update(1,1,n,r + 1,-val);
            rev_aint.update(1,1,n,n - r + 1,val);
            rev_aint.update(1,1,n,n - l + 2,-val);
        }
        else {
            fprintf(g,"%d\n",solve(l,r));
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
