#include<fstream>
#include<vector>
#include<algorithm>
#define DIM 200005
#define mod 1000000007
using namespace std;
int n, i, nod, vecin, sol, sum, ii, num, r1, r2, j, x, y;
int d[DIM][2], nr[DIM], r[DIM], viz[DIM], aux[2], s[2];
vector<int> v[DIM];
pair<int, int> w[DIM];
ifstream fin("countfefete.in");
ofstream fout("countfefete.out");
int modul(int x){
    if(x >= mod){
        return x - mod;
    }
    if(x < 0){
        return x + mod;
    }
    return x;
}
int rad(int x){
    int y = x, aux;
    while(r[x] > 0){
        x = r[x];
    }
    while(r[y] > 0){
        aux = r[y];
        r[y] = x;
        y = aux;
    }
    return x;
}
int main(){
    fin>> n;
    for(i = 1; i <= n; i++){
        fin>> w[i].first;
        w[i].second = i;
    }
    for(i = 1; i < n; i++){
        fin>> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    sort(w + 1, w + n + 1);
    for(ii = 0; ii < 30; ii++){
        for(i = 1; i <= n; i++){
            r[i] = -1;
            viz[i] = 0;
            d[i][0] = d[i][1] = 0;
        }
        num = sum = 0;
        for(i = n; i >= 1; i--){
            nod = w[i].second;
            viz[nod] = 1;
            num++;
            nr[nod] = num;
            d[num][0] = 1;
            d[num][ ( (w[i].first >> ii) & 1) ]++;
            r2 = nod;
            s[0] = 1;
            s[1] = 0;
            for(j = 0; j < v[nod].size(); j++){
                vecin = v[nod][j];
                if(viz[vecin] == 0){
                    continue;
                }
                r1 = rad(vecin);
                aux[0] = (d[num][0] * 1LL * d[ nr[r1] ][0] + d[num][1] * 1LL * d[ nr[r1] ][1]) % mod;
                aux[1] = (d[num][0] * 1LL * d[ nr[r1] ][1] + d[num][1] * 1LL * d[ nr[r1] ][0]) % mod;
                d[num][0] = aux[0];
                d[num][1] = aux[1];
                s[0] = modul(s[0] + d[ nr[r1] ][0] - 1);
                s[1] = modul(s[1] + d[ nr[r1] ][1]);
                if(r[r1] < r[r2]){
                    r[r1] += r[r2];
                    r[r2] = r1;
                    nr[r1] = num;
                    r2 = r1;
                }
                else{
                    r[r2] += r[r1];
                    r[r1] = r2;
                }
            }
            if( ( (w[i].first >> ii) & 1) == 0){
                sum = modul(sum + d[num][1]);
                sum = modul(sum - s[1]);
            }
            else{
                sum = modul(sum + d[num][0]);
                sum = modul(sum - s[0]);
            }
        }
        sol = (sol + (1 << ii) * 1LL * sum) % mod;
    }
    fout<< sol;
    return 0;
}
