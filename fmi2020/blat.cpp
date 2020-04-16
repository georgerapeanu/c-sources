#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("blat.in","r");
FILE *g = fopen("blat.out","w");

int n,m,k;
int punctaj[105][105];

int main() {

    fscanf(f,"%d %d %d",&m,&n,&k);

    int total_mi = 1e9;
    int total_ma = -1e9;
    int partial_mi = 1e9;
    int partial_ma = -1e9;

    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= m; j++) {
            fscanf(f,"%d",&punctaj[i][j]);
            punctaj[k + 1][j] += punctaj[i][j];
        }
        sort(punctaj[i] + 1,punctaj[i] + 1 + m);
        int sum = 0;
        for(int j = 1; j <= n; j++) {
            sum += punctaj[i][j];
        }
        partial_mi = min(partial_mi,sum);
        sum = 0;
        for(int j = m - n + 1; j <= m; j++) {
            sum += punctaj[i][j];
        }
        partial_ma = max(partial_ma,sum);
    }

    sort(punctaj[k + 1] + 1,punctaj[k + 1] + 1 + m);

    int sum = 0;
    for(int j = 1; j <= n; j++) {
        sum += punctaj[k + 1][j];
    }
    total_mi = min(total_mi,sum);
    sum = 0;
    for(int j = m - n + 1; j <= m; j++) {
        sum += punctaj[k + 1][j];
    }
    total_ma = max(total_ma,sum);

    fprintf(g,"%d\n%d\n%d\n%d\n",total_ma,total_mi,partial_ma,partial_mi);

    fclose(f);
    fclose(g);

    return 0;
}
