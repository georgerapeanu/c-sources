#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

const long double eps = 1e-6;

int n;
int v[10][10];

bool taken[100];

void btr(int i,int j,long double current_ratio){
    if(i > n){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                cout << v[i][j] << " ";
            }
            cout << "\n";
        }
        exit(0);
    }

    if(i == j){
        for(int a = 1;a <= n * n;a++){
            if(taken[a]){
                continue;
            }
            taken[a] = true;
            v[i][j] = a;
            btr(i + (j == n),j % n + 1,current_ratio);
            taken[a] = false;
        }
        return;
    }

    if(i == 2 && j == 3 && v[1][1] == 5 && v[1][2] == 6 && v[1][3] == 4 && v[2][1] == 3 && v[3][1] == 8 && v[2][2] == 7)cout << current_ratio << " " << taken[1] << " " << taken[2] << "\n";

    for(int a = 1;a <= n * n;a++){
        if(taken[a]){
            continue;
        }
        taken[a] = true;
        for(int b = a + 1;b <= n * n;b++){
            if(taken[b]){
                continue;
            }
            taken[b] = true;
            v[i][j] = a;
            v[j][i] = b;
            if(j == n){
                if(abs((current_ratio * v[i][j]) / v[j][i] - 1) > eps){
                    goto done1;
                }
                long double new_ratio = 1;

                for(int k = 1;k <= i;k++){
                    new_ratio = (new_ratio * v[i + 1][k]) / v[k][i + 1];
                }
                btr(i + 1,i + 1,new_ratio);
            }
            else{
                btr(i,j + 1,(current_ratio * v[i][j]) / v[j][i]);
            }

            done1:;
            v[i][j] = b;
            v[j][i] = a;
            if(j == n){
                if(abs((current_ratio * v[i][j] / v[j][i]) - 1) > eps){
                    goto done2;
                }
                long double new_ratio = 1;

                for(int k = 1;k <= i;k++){
                    new_ratio = (new_ratio * v[i + 1][k]) / v[k][i + 1];
                }
                btr(i + 1,i + 1,new_ratio);
            }
            else{
                btr(i,j + 1,(current_ratio * v[i][j]) / v[j][i]);
            }
            done2:;
            taken[b] = false;
        }
        taken[a] = false;
    }
}

int main(){
    cin >> n;
    btr(1,1,1);
    return 0;
}
