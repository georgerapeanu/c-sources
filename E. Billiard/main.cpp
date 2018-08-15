#include <iostream>
using namespace std;
long long N,M;
long long X,Y;
long long vX,vY;

long long exgcd(long long N,long long M,long long &A,long long &B){
    if(!M){
        A = 1;
        B = 0;
        return N;
    }
    long long D = exgcd(M,N % M,B,A);
    B -= (N / M) * A;
    return D;
}

long long lgmult(long long A,long long B,long long MOD){
    long long rez = 0,sgn = (A < 0 ? -1 : 1) * (B < 0 ? -1 : 1);
    A *= (A < 0 ? -1 : 1);
    B *= (B < 0 ? -1 : 1);
    while(B){
        if(B & 1){
            rez += A;
            if(rez >= MOD){
                rez -= MOD;
            }
        }
        A += A;
        if(A >= MOD){
            A -= MOD;
        }
        B /= 2;
    }
    return rez * sgn;
}

int main(){
    cin >> N >> M >> X >> Y >> vX >> vY;

    if(!vX){
        if(X % N == 0){
            cout << X << " " << (vY > 0 ? M : 0);
        }
        else{
            cout << -1;
        }
        return 0;
    }

    if(!vY){
        if(Y % M == 0){
            cout << (vX > 0 ? N : 0) << " " << Y;
        }
        else{
            cout << -1;
        }
        return 0;
    }

    long long A,B,C,D;

    C = X * vY - vX * Y;
    D = exgcd(N,M,A,B);

    A *= vY;
    B *= -1 * vX;

    if(C % D != 0){
        cout << -1;
        return 0;
    }

    long long K;

    K = lgmult(N,A,N * M / D);
    K = lgmult(K,C / D,N * M / D);

    K -= X;
    K /= vX;

    K %= (N * M / D);

    if(K < 0){
        K += (N * M / D);
    }

    X += vX * K;
    Y += vY * K;

    cout << (X % (2 * N) != 0) * N << " " << (Y % (2 * M) != 0) * M << "\n";

    return 0;
}
