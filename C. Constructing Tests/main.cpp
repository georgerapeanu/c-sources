#include <iostream>

using namespace std;
int x;
int T;
bool ok(int f1,int f2,bool afis){
    int a = f1 + f2;
    if(f1 == f2){
        return 0;
    }
    if(a & 1){
        return 0;
    }
    int N = a / 2;
    int NpeM = N - f1;
    if(NpeM > N){
        return 0;
    }
    int M = N / NpeM;
    while(N / M > NpeM){
        M++;
    }
    while(M && N / M < NpeM){
        M--;
    }
    if(M == 0 || N / M != NpeM){
        return 0;
    }
    if(afis){
        cout << N << " " << M << "\n";
    }
    return 1;
}
int main()
{
    cin >> T;
    while(T--){
        cin >> x;
        bool k = 0;
        if(x == 0){
            cout << "1 1\n";
            continue;
        }
        if(x == 1){
            cout << "-1\n";
            continue;
        }
        for(int d = 1;1LL * d * d <= x;d++){
            if(x % d == 0){
                if(ok(d,x / d,0)){
                    ok(d,x / d,1);
                    k = 1;
                    break;
                }
            }
        }
        if(!k){
            cout << "-1\n";
        }
    }
    return 0;
}
