#include <cstdio>
///#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
int REPR[2][1 << 22];
int T[1 << 22];
bool propag[23][1 << 22];
const int VOID = -1;

void init(){
    for(int i = 0;i < (1 << N);i++){
        T[i] = -1;
    }
    for(int i = 0;i <= 1;i++){
        for(int j = 0;j < (1 << N);j++){
            REPR[i][j] = VOID;
        }
    }
}

int fi(int x){
    if(T[x] < 0){
        return x;
    }
    return T[x] = fi(T[x]);
}

void u(int x,int y){
    if(x == VOID || y == VOID){
        return ;
    }

    x = fi(x);
    y = fi(y);

    if(x == y){
        return ;
    }

    if(T[x] < T[y]){
        T[x] += T[y];
        T[y] = x;
    }
    else{
        T[y] += T[x];
        T[x] = y;
    }
}

int main(){
    scanf("%d %d",&N,&M);

    if(N == 0){
        printf("1");
        return 0;
    }

    init();

    vector<int> roots;

    for(int i = 1;i <= M;i++){
        int a;
        scanf("%d",&a);
        REPR[0][a] = a;
        propag[N][((1 << N) - 1) ^ a] = 1;
        roots.push_back(a);
    }

    for(int lvl = N;lvl;lvl--){
        int real_bit = lvl - 1;
        for(int i = 0;i < (1 << N);i++){
            if(propag[lvl][i] == 0){
                continue;
            }
            propag[lvl - 1][i] = 1;
            if((i >> real_bit) & 1){
                propag[lvl - 1][i ^ (1 << real_bit)] = 1;
            }
        }
    }

    for(int i = 0;i < (1 << N);i++){
        if(propag[0][i] == 0){
            REPR[0][i] = VOID;
        }
    }

    /*for(int lvl = 0;lvl <= N;lvl++){
        for(int i = 0;i < (1 << N);i++){
            cout << propag[lvl][i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    for(int i = 0;i < (1 << N);i++){
        cout << REPR[0][i] << " ";
    }

    cout << "\n";*/

    for(int lvl = 1;lvl <= N;lvl++){
        int real_bit = lvl - 1;
        for(int i = 0;i < (1 << N);i++){
            if(propag[lvl][i] == 1){
                REPR[lvl & 1][i] = REPR[1 - (lvl & 1)][i];
                if((i >> real_bit) & 1){
                    if(REPR[lvl & 1][i] == VOID){
                        REPR[lvl & 1][i] = REPR[1 - (lvl & 1)][i ^ (1 << real_bit)];
                    }
                    else{
                        u(REPR[1 - (lvl & 1)][i ^ (1 << real_bit)],REPR[lvl & 1][i]);
                        REPR[lvl & 1][i] = fi(REPR[lvl & 1][i]);
                    }
                }
            }
            else{
                REPR[lvl & 1][i] = VOID;
            }
        }
        /*for(int i = 0;i < (1 << N);i++){
            cout << REPR[lvl & 1][i] << " ";
        }
        cout << "\n";*/

    }

    for(int i = 0;i < (1 << N);i++){
        if(propag[N][i]){
            u(REPR[N & 1][i],((1 << N) - 1) ^ i);
        }
    }

    //cout << "\n";

    for(auto &it:roots){
      //  cout << it << " ";
        it = fi(it);
       // cout << it << "\n";
    }

    sort(roots.begin(),roots.end());

    printf("%d",(int)(unique(roots.begin(),roots.end()) - roots.begin()));

    return 0;
}
