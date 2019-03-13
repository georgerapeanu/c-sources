#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("tablou.in","r");
FILE *g = fopen("tablou.out","w");

const int NMAX = 3000;
const int MMAX = 3000;
const int KMAX = 1e5;
const int LMAX = 100;

int n,m,k;
char t[NMAX + 5][MMAX + 5];
int sp[NMAX + 5][MMAX + 5];

vector<int> sums;

long long total_sum;

int get_sum(int x,int y,int xx,int yy){
    return sp[xx][yy] - sp[x - 1][yy] - sp[xx][y - 1] + sp[x - 1][y - 1];
}

int A[LMAX + 5],lena;
int B[LMAX + 5],lenb;
int C[LMAX + 5],lenc;

void init(int A[],int &len,long long val){
    len = 0;
    while(val){
        A[++len] = val % 10;
        val /= 10;
    }

    len = max(len,1);
}

void afis(long long a){
    init(A,lena,a);

    int lenc = lena + lenb + 1;

    for(int i = 1;i <= lenc;i++){
        C[i] = 0;
    }

    for(int i = 1;i <= lena;i++){
        for(int j = 1;j <= lenb;j++){
            C[i + j - 1] += A[i] * B[j];
        }
    }

    int t = 0;

    for(int i = 1;i <= lenc || t;i++){
        C[i] += t;
        t = C[i] / 10;
        C[i] %= 10;
        lenc = max(lenc,i);
    }

    while(C[lenc] == 0 && lenc > 1){
        lenc--;
    }

    for(int i = lenc;i;i--){
        fprintf(g,"%d",C[i]);
    }
}

int main(){

    fscanf(f,"%d %d\n",&n,&m);

    int orig_sum = 0;

    for(int i = 1;i <= n;i++){
        fgets(t[i] + 1,MMAX + 5,f);
        for(int j = 1;j <= m;j++){
            sp[i][j] = sp[i - 1][j] + sp[i][j - 1] - sp[i - 1][j - 1] + (t[i][j] - '0');
            orig_sum += (t[i][j] - '0');
        }
    }

    fscanf(f,"%d",&k);

    for(int i = 1;i <= k;i++){
        int x,y,xx,yy,c;
        fscanf(f,"%d %d %d %d %d\n",&x,&y,&xx,&yy,&c);
        int sum = orig_sum - get_sum(x,y,xx,yy) + c * (xx - x + 1) * (yy - y + 1);
        sums.push_back(sum);
        total_sum += sum;
    }

    init(B,lenb,1LL * n * m);

    for(int i = 0;i < (int)sums.size();i++){
        long long a = (1LL * k * sums[i] - total_sum);
        if(a < 0){
            a = -a;
            fprintf(g,"-");
        }
        afis(a);
        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
