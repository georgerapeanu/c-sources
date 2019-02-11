#include<fstream>
#include<algorithm>
#define DIM 100005
using namespace std;
int n, niv, i, ii, jj, x, y, sum, u, m, num, a;
int v[32][DIM], nr[32], d[32][DIM], ff[DIM];
long long sol;
pair<int, int> w[DIM], aux[DIM];
ifstream fin("fft2d.in");
ofstream fout("fft2d.out");
int main(){
    fin>> niv >> n;
    for(i = 1; i <= n; i++){
        fin>> x >> y;
        v[x][++nr[x]] = y;
    }
    for(i = 1; i <= nr[niv - 1]; i++){
        d[niv - 1][i] = 1;
    }
    for(ii = niv - 2; ii >= 0; ii--){
        for(i = 1; i <= nr[ii]; i++){
            d[ii][i] = (1 << (niv - ii - 1) );
        }
        for(jj = ii + 1; jj < niv; jj++){
            m = 0;
            //x = (1 << (niv - ii - 2) ) - (1 << (niv - jj - 1) );
            for(i = 1; i <= nr[ii]; i++){
                w[++m].second = i;
                w[m].first = v[ii][i];
                for(a = niv - ii - 3; a > niv - jj - 3; a--){
                    if( ( (v[ii][i] >> a) & 1) == 1){
                        w[m].first -= (1 << a);
                    }
                }
                //w[m].first = ( (v[ii][i] >> (niv - ii - 1)) << (niv - jj - 1) ) + (v[ii][i] & ( (1 << (niv - jj - 1) ) - 1) );
            }
            for(i = 1; i <= nr[jj]; i++){
                w[++m].second = i + nr[ii];
                w[m].first = v[jj][i];
                for(a = niv - ii - 3; a > niv - jj - 3; a--){
                    if( ( (v[jj][i] >> a) & 1) == 1){
                        w[m].first -= (1 << a);
                    }
                }
                //w[m].first = ( (v[jj][i] >> (niv - ii - 1)) << (niv - jj - 1) ) + (v[jj][i] & ( (1 << (niv - jj - 1) ) - 1) );
            }
            for(i = 0; i < (1 << 15); i++){
                ff[i] = 0;
            }
            for(i = 1; i <= m; i++){
                ff[ (w[i].first & ( (1 << 15) - 1) ) ]++;
            }
            for(i = 1; i < (1 << 15); i++){
                ff[i] += ff[i - 1];
            }
            for(i = m; i >= 1; i--){
                aux[ ff[ (w[i].first & ( (1 << 15) - 1) ) ] ] = w[i];
                ff[ (w[i].first & ( (1 << 15) - 1) ) ]--;
            }
            for(i = 1; i <= m; i++){
                w[i] = aux[i];
            }

            for(i = 0; i < (1 << 15); i++){
                ff[i] = 0;
            }
            for(i = 1; i <= m; i++){
                ff[ (w[i].first >> 15 ) ]++;
            }
            for(i = 1; i < (1 << 15); i++){
                ff[i] += ff[i - 1];
            }
            for(i = m; i >= 1; i--){
                aux[ ff[ (w[i].first >> 15 ) ] ] = w[i];
                ff[ (w[i].first >> 15 ) ]--;
            }
            for(i = 1; i <= m; i++){
                w[i] = aux[i];
            }

            for(i = 1; i <= m; i++){
                sum = 0;
                for(u = i; u <= m; u++){
                    if(w[i].first != w[u].first){
                        break;
                    }
                    if(w[u].second > nr[ii]){
                        sum += d[jj][ w[u].second - nr[ii] ];
                    }
                }
                for(u = i; u <= m; u++){
                    if(w[i].first != w[u].first){
                        break;
                    }
                    if(w[u].second <= nr[ii]){
                        d[ii][ w[u].second ] -= sum;
                    }
                }
                i = u - 1;
            }
        }
    }
    for(ii = 0; ii < niv; ii++){
        for(i = 1; i <= nr[ii]; i++){
            sol += d[ii][i] * 1LL * (1 << ii);
        }
    }
    fout<< (1 << (niv - 1)) * 1LL * (1 << (niv - 1)) - sol;
    return 0;
}
