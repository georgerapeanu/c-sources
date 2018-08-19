#include <iostream>

using namespace std;

long long N,P,R;

long long lgpow(long long b,long long e){
    long long p = 1;
    while(e){
        if(e & 1){
            p = p * b % P;
        }
        b = b * b % P;
        e >>= 1;
    }
    return p;
}

int main(){
    cin >> N >> P >> R;
    if(N >= 2 * P){
        if(R != 0){
            cout << "-1 -1";
        }
        else{
            cout << "2 1";
        }
        return 0;
    }
    if(N >= P){
        if(R == 0){
            if(P == 2){
                if(N == 2){
                    cout << "-1 -1";
                }
                else{
                    cout << "3 1";
                }
            }
            else{
                cout << "2 1";
            }
        }
        else{
            long long fact = 1;

            for(long long i = 1;i <= N;i++){
                if(i != P){
                    fact = fact * i % P;
                }
            }

            cout << P << " " << lgpow(fact,P - 2) * R % P;
        }
        return 0;
    }

    if(R == 0){
        cout << "-1 -1";
        return 0;
    }

    long long fact = 1;

    for(long long i = 1;i <= N;i++){
        fact = fact * i % P;
    }

    R = R * lgpow(fact,P - 2) % P;

    for(long long i = 1;i <= N;i++){
        long long tmp = R * i % P;
        if(tmp < i){
            cout << i << " " << tmp;
            return 0;
        }
    }

    cout << "-1 -1";

    return 0;
}
