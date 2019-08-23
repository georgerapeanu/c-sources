#include <bits/stdc++.h>

using namespace std;

int n;
int v[55][55];
int tmp1[55][55];
int tmp2[55][55];

int my_ask(int x,int y,int xx,int yy,int v[][55]){
    if(v[x][y] != v[xx][yy]){
        return 0;
    }
    if(xx - x == 1){
        return (v[x][y + 1] == v[x][y + 2]) || (v[x + 1][y] == v[x + 1][y + 1]);
    }
    else{
        return (v[x][y + 1] == v[x + 1][y + 1]) || (v[x + 1][y] == v[x + 2][y]);
    }
}

int ask(int x,int y,int xx,int yy){
    cout << "? " << x << " " << y << " " << xx << " " << yy << endl;
    int ans;
    cin >> ans;
    return ans;
}

int main() {

    cin >> n;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            v[i][j] = -1;
        }
    }

    v[1][1] = 1;
    v[n][n] = 0;

    for(int i = 3;i <= n;i += 2){
        v[1][i] = ((ask(1,i - 2,1,i) == false) ^ v[1][i - 2]);
        v[i][1] = ((ask(i - 2,1,i,1) == false) ^ v[i - 2][1]);
    }

    for(int i = 2;i <= n;i++){
        for(int j = 2;j <= n;j++){
            if(i == n && j == n){
                continue;
            }
            if(i % 2 == j % 2){
                v[i][j] = ((ask(i - 1,j - 1,i,j) == false) ^ v[i - 1][j - 1]);
            }
        }
    }

    int px = -1,py = -1;
    for(int i = 1;i <= n;i += 2){
        if(v[i][i] == 1 && v[i + 2][i + 2] == 0){
            int a = (ask(i,i + 1,i + 1,i + 2) == false);
            int b = (ask(i + 1,i,i + 1,i + 2) == false);
            int c = (ask(i + 1,i,i + 2,i + 1) == false);
            for(int l = i;l <= i + 2;l++){
                for(int k = i;k <= i + 2;k++){
                    tmp1[l][k] = tmp2[l][k] = v[l][k];
                }
            }
            tmp1[i][i + 1] = 0;tmp2[i][i + 1] = 1;
            tmp1[i + 1][i + 2] = 0 ^ a;tmp2[i + 1][i + 2] = 1 ^ a;
            tmp1[i + 1][i] = 0 ^ a ^ b;tmp2[i + 1][i] = 1 ^ a ^ b;
            tmp1[i + 2][i + 1] = 0 ^ a ^ b ^ c;tmp2[i + 2][i + 1] = 1 ^ a ^ b ^ c;

            if(my_ask(i,i,i + 1,i + 2,tmp1) != my_ask(i,i,i + 1,i + 2,tmp2)){
                if(ask(i,i,i +1,i + 2) == my_ask(i,i,i + 1,i + 2,tmp1)){
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp1[l][k];
                        }
                    }
                }
                else{
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp2[l][k];
                        }
                    }
                }
            }
            else if(my_ask(i + 1,i,i + 2,i + 2,tmp1) != my_ask(i + 1,i,i + 2,i + 2,tmp2)){
                if(ask(i + 1,i,i +2,i + 2) == my_ask(i + 1,i,i + 2,i + 2,tmp1)){
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp1[l][k];
                        }
                    }
                }
                else{
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp2[l][k];
                        }
                    }
                }
            }
            else if(my_ask(i,i,i + 2,i + 1,tmp1) != my_ask(i,i,i + 2,i + 1,tmp2)){
                if(ask(i,i,i + 2,i + 1) == my_ask(i,i,i + 2,i + 1,tmp1)){
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp1[l][k];
                        }
                    }
                }
                else{
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp2[l][k];
                        }
                    }
                }
            }
            else if(my_ask(i,i + 1,i + 2,i + 2,tmp1) != my_ask(i,i + 1,i + 2,i + 2,tmp2)){
                if(ask(i,i + 1,i + 2,i + 2) == my_ask(i,i,i + 2,i + 2,tmp1)){
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp1[l][k];
                        }
                    }
                }
                else{
                    for(int l = i;l <= i + 2;l++){
                        for(int k = i;k <= i + 2;k++){
                            v[l][k] = tmp2[l][k];
                        }
                    }
                }
            }
            else assert(false);
            px = i + 1;
            py = i + 1;
            break;
        }
    }

    for(int i = px - 2,j = py - 1;i > 0 && j > 0;i--,j--){
        v[i][j] = (ask(i,j,i + 1,j + 1) == false) ^ v[i + 1][j + 1];
    }

    for(int i = px - 1,j = py - 2;i > 0 && j > 0;i--,j--){
        v[i][j] = (ask(i,j,i + 1,j + 1) == false) ^ v[i + 1][j + 1];
    }

    for(int i = 4;i <= n;i += 2){
        v[1][i] = ((ask(1,i - 2,1,i) == false) ^ v[1][i - 2]);
        v[i][1] = ((ask(i - 2,1,i,1) == false) ^ v[i - 2][1]);
    }

    for(int i = 2;i <= n;i++){
        for(int j = 2;j <= n;j++){
            if(i == n && j == n){
                continue;
            }
            if(v[i][j] != -1){
                continue;
            }
            if(i % 2 != j % 2){
                v[i][j] = ((ask(i - 1,j - 1,i,j) == false) ^ v[i - 1][j - 1]);
            }
        }
    }

    cout << "!" << endl;;

    for(int i = 1;i <= n;i++){
        string s;
        for(int j = 1;j <= n;j++){
            s += '0' + v[i][j];
        }
        cout << s << endl;
    }


    return 0;
}
