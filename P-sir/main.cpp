#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f = fopen("psir.in","r");
FILE *g = fopen("psir.out","w");
vector<int> V;
int N;
int P[2005];
unsigned int S[2005][2005],rez;
int main(){
    fscanf(f,"%d",&N);
    V.push_back(0);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&P[i]);
        V.push_back(P[i]);
    }
    sort(V.begin(),V.end());
    V.resize(unique(V.begin(),V.end()) - V.begin());
    for(int i = 1;i <= N;i++){
        P[i] = find(V.begin(),V.end(),P[i]) - V.begin();
    }
    for(int i = N;i;i--){
        for(int j = i + 1;j <= N;j++){
            int st = min(P[i],P[j]);
            int dr = max(P[i],P[j]);
            S[i][P[j]] += 1 + S[j][dr - 1] - S[j][st];
            rez += 1 + S[j][dr - 1] - S[j][st];
        }
        for(int j = 1;j <= N;j++){
            S[i][j] += S[i][j - 1];
        }
    }
    fprintf(g,"%u",rez);
    fclose(f);
    fclose(g);
    return 0;
}
