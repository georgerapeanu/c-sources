#include <iostream>
#include <vector>

using namespace std;

int N,M;

int T[100005];
int phi[100005];
vector<int> divs[100006];
int nxt[100005];
int ant[100005];
bool erased[100005];

int main(){

    cin >> N >> M;

    long long maxE = 0;

    nxt[0] = 1;
    ant[1] = 0;
    for(int i = 2;i <= N;i++){
        nxt[i - 1] = i;
        ant[i] = i - 1;
        phi[i] += i - 1;
        for(int j = i;j <= N;j += i){
            divs[j].push_back(i);
            if(j > i){
                phi[j] -= phi[i];
            }
        }
        maxE += phi[i];
    }

    if(M < N - 1){
        cout << "Impossible";
        return 0;
    }

    if(maxE < M){
        cout << "Impossible";
        return 0;
    }

    cout << "Possible\n";

    for(int i = 1;i <= N;i++){
        for(auto it:divs[i]){
            for(int j = it;j <= N;j += it){
                if(erased[j]){
                    continue;
                }
                int n = nxt[j];
                int a = ant[j];
                nxt[a] = n;
                ant[n] = a;
                erased[j] = 1;
            }
        }

        for(int val = nxt[0];val;val = nxt[val]){
            if(val <= i){
                continue;
            }
            cout << val << " " << i << "\n";
            M--;
            if(!M){
                return 0;
            }
        }

        for(auto it:divs[i]){
            for(int j = it;j <= N;j += it){
                nxt[j - 1] = j;
                if(j != N){
                    ant[j + 1] = j;
                }
                erased[j] = 0;
            }
        }
    }

    return 0;
}
