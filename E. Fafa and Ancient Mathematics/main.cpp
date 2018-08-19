#include <iostream>
#include <cassert>

using namespace std;
string A;
int P,M;
int ind,nod;
int dp1[10005][205];
int dp2[10005][205];
int cnt[10005];
bool sw;
int  dfs(){
    nod++;
    for(int c = 0;c <= P;c++){
        dp1[nod][c] = -(1 << 28);
        dp2[nod][c] = (1 << 28);
    }
    if('0' <= A[ind] && A[ind] <= '9'){
        cnt[nod] = 0;
        dp1[nod][0] = A[ind] - '0';
        dp2[nod][0] = A[ind] - '0';
        ind++;
        return nod;
    }
    assert(A[ind] == '(');
    ind++;
    int node = nod;
    int a = dfs();
    assert(A[ind] == '?');
    ind++;
    int b = dfs();
    assert(A[ind] == ')');
    ind++;
    cnt[node] = cnt[a] + cnt[b] + 1;
    for(int c = 0;c <= cnt[node] && c <= P;c++){
        if(!sw){
            for(int split = 0;split <= c;split++){
                if(split <= P && split <= cnt[a] && c - split <= cnt[b]){
                    dp1[node][c] = max(dp1[node][c],dp1[a][split] - dp2[b][c - split]);
                    dp2[node][c] = min(dp2[node][c],dp2[a][split] - dp1[b][c - split]);
                }
            }
            for(int split = 0;split < c;split++){
                if(split <= P && split <= cnt[a] && c - split - 1 <= cnt[b]){
                    dp1[node][c] = max(dp1[node][c],dp1[a][split] +  dp1[b][c - split - 1]);
                    dp2[node][c] = min(dp2[node][c],dp2[a][split] + dp2[b][c - split - 1]);
                }
            }
        }
        else{
            for(int split = 0;split <= c;split++){
                if(split <= P && split <= cnt[a] && c - split <= cnt[b]){
                    dp1[node][c] = max(dp1[node][c],dp1[a][split] + dp1[b][c - split]);
                    dp2[node][c] = min(dp2[node][c],dp2[a][split] + dp2[b][c - split]);
                }
            }
            for(int split = 0;split < c;split++){
                if(split <= P && split <= cnt[a] && c - split - 1 <= cnt[b]){
                    dp1[node][c] = max(dp1[node][c],dp1[a][split] - dp2[b][c - split - 1]);
                    dp2[node][c] = min(dp2[node][c],dp2[a][split] - dp1[b][c - split - 1]);
                }
            }
        }
        assert(dp1[node][c] >= dp2[node][c]);
    }
    return node;
}
int main()
{
    cin >> A >> P >> M;
    if(P > M){
        sw = 1;
        swap(P,M);
    }
    int tmp = dfs();
    cout << dp1[tmp][P];
    return 0;
}
