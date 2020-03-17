#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

FILE *f = fopen("cerc3.in","r");
FILE *g = fopen("cerc3.out","w");

int n;
int ord[2005];
int x[2005];
int y[2005];
int r[2005];
int dx[2005];
int dy[2005];
double stx[2005];
double drx[2005];

int gcd(int a,int b){
    if(b == 0){
        return a;
    }
    return gcd(b,a % b);
}


bool cmp(int a,int b){
    if(dx[a] != dx[b]){
        return dx[a] < dx[b];
    }
    if(dy[a] != dy[b]){
        return dy[a] < dy[b];
    }
    if(drx[a] != drx[b]){
        return drx[a] < drx[b];
    }
    return stx[a] < stx[b];
}

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d %d",&x[i],&y[i],&r[i]);
        int gc = gcd(x[i],y[i]);
        dx[i] = x[i] / gc;
        dy[i] = y[i] / gc;
        stx[i] = x[i] - (dx[i] / ((double)sqrt(dx[i] * dx[i] + dy[i] * dy[i]))) * r[i];
        drx[i] = 2 * x[i] - stx[i];
        ord[i] = i;
    }

    sort(ord + 1,ord + 1 + n,cmp);

    int lst = 1;
    int ans_a = 0;
    int mx = 0;
    int cnt_mx = 0;

    for(int i = 2;i <= n + 1;i++){
        if(dx[ord[i]] != dx[ord[i -  1]] || dy[ord[i]] != dy[ord[i - 1]]){
            int tmp_bst = 1;
            int ult = lst;
            for(int j = lst + 1;j < i;j++){
                if(stx[ord[j]] > drx[ord[ult]]){
                    ult = j;
                    tmp_bst++;
                }
            }
            if(mx < tmp_bst){
                mx = tmp_bst;
                cnt_mx = 0;
            }
            if(mx == tmp_bst){
                cnt_mx++;
            }
            ans_a++;
            lst = i;
        }
    }

    fprintf(g,"%d %d %d\n",ans_a,mx,cnt_mx);

    fclose(f);
    fclose(g);

    return 0;
}
