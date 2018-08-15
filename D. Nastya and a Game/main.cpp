#include <iostream>

using namespace std;

const long long LIM = 1LL << 62;

int N,K;
int V[200005];
int nxt[200005];

int main(){
    cin >> N >> K;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
    }

    for(int i = N;i >= 0;i--){
        nxt[i] = (V[i + 1] == 1 ? nxt[i + 1] : i + 1);
    }

    int len = 1;

    long long rez = 0;
    for(int st = 1;st <= N;st++){
        long long S = 0,P = 1;
        for(int dr = st;dr <= N;dr++){
            if(V[dr] == 1){
                rez += (P % K == 0 && P / K - S > 0 && P / K - S <= nxt[dr] - dr);
                S += nxt[dr] - dr;
                dr = nxt[dr] - 1;
            }
            else{
                if(P > LIM / V[dr])break;
                P *= V[dr];
                S += V[dr];
                rez += (P == S * K);
            }
        }
    }

    cout << rez;

    return 0;
}
