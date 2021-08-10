///multumim de inputuri

#include "saumat.h"
#include <vector>
#include <cstdio>
using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 2e6;
const int LGMAX = 10;

int n,m;
vector<int> p;
vector<vector<int>> a;
int last[LGMAX];
int gr[NMAX + 5];
int values[NMAX + 5];
int fr[1 << LGMAX];
vector<int> positions;///TODO maybe try with deque
vector<int> tmp_positions;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

void update_with_positions(int curr){
    /*printf("update %d\n",curr);
    for(auto it:positions){
        printf("%d ",it);
    }
    printf("\n");
    */
    tmp_positions.clear();
    int mask = 0;
    int last = curr;
    for(int i = (int)positions.size() - 1;i >= 0;i--){
        int it = positions[i];
        if(gr[it]){
            tmp_positions.push_back(it);
            fr[mask] = add(fr[mask],last - it);
            mask |= values[it];
            last = it;
        }
    }
    fr[mask] = add(fr[mask],last + 1);
    positions.clear();
    for(int i = (int)tmp_positions.size() - 1;i >= 0;i--){
        positions.push_back(tmp_positions[i]);
    }
}

int solve(vector<int> P, int N, int M, vector<vector<int>> A){
    n = N;
    m = M;
    p = P;

    if(n > m){
        swap(n,m);
        a = vector<vector<int> >(n,vector<int>(m,0));

        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                a[i][j] = A[j][i];
            }
        }
    }else{
        a = A;
    }

    int cnt = 0;

    for(int i = 0;i < n;i++){
        for(int k = 0;k < m;k++){
            values[k] = 0;
            gr[k] = 0;
        }
        for(int j = i;j < n;j++){
            for(int i = 0;i < LGMAX;i++){
                last[i] = -1;
            }
            positions.clear();
            for(int k = 0;k < m;k++){
                values[k] |= a[j][k];
                for(int h = 0;h < LGMAX;h++){
                    if((values[k] >> h) & 1){
                        if(last[h] != -1){
                            gr[last[h]]--; 
                        }
                        last[h] = k;
                        gr[k]++;
                    }
                }
                if(gr[k]){
                    positions.push_back(k);
                }
                update_with_positions(k);
            }
        }
    }

    int ans = 0;

    /*for(int h = LGMAX - 1;h >= 0;h--){
        for(int i = 0;i < (1 << LGMAX);i++){
            if(((i >> h) & 1) == 0){
                fr[i] = scad(fr[i],fr[i ^ (1 << h)]);
            }
        }
    }*/

/*    for(int i = (1 << LGMAX) - 1;i >= 0;i--){
        if(fr[i] > 0){
            printf("deb %d %d\n",i,fr[i]);
        }
        for(int j = i;j < (1 << LGMAX);j = ((j + 1) | i)){
            if(j == i){
                continue;
            }
            fr[i] = scad(fr[i],fr[j]);
        }
    }
*/

    for(int i = 0;i < (1 << LGMAX);i++){
    /*    if(fr[i] > 0){
            printf("deb2 %d %d\n",i,fr[i]);
        }*/
        ans = add(ans,mult(fr[i],p[i]));
    }

    return ans;
}
