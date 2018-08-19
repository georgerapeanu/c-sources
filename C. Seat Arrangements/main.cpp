#include <iostream>

using namespace std;
int N,M,K;
string V[2005];
int main()
{
    cin >> N >> M >> K;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
        V[i] = " " + V[i];
    }
    int rez = 0;
    for(int i = 1;i <= N;i++){
        int last = 0;
        for(int j = 1;j <= M;j++){
            if(V[i][j] == '*'){
                last = j;
            }
            if(j - last >= K){
                rez++;
            }
        }
    }
    if(K > 1){
        for(int j = 1;j <= M;j++){
            int last = 0;
            for(int i = 1;i <= N;i++){
                if(V[i][j] == '*'){
                    last = i;
                }
                if(i - last >= K){
                    rez++;
                }
            }
        }
    }
    cout << rez;
    return 0;
}
