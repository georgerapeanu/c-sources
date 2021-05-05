#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n;
string s[155];
int fst_l[155];
int fst_c[155];
int lst_l[155];
int lst_c[155];


bool viz[155][155];

int ans = 0;

void dfs(int x,int y){
    if(x < 1 || x > n || y < 1 || y > n || viz[x][y] == true || s[x][y] != 'G'){
        return;
    }
    viz[x][y] = true;

    dfs(x,y + 1);
    dfs(x,y - 1);
    dfs(x + 1,y);
    dfs(x - 1,y);
}

void btr(int x,int y){
    if(x > n){
        for(int i = 1;i <= n;i++){
            fst_l[i] = 0;
            lst_l[i] = 0;
            fst_c[i] = 0;
            lst_c[i] = 0;
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(s[i][j] == 'G'){
                    lst_l[i] = j;
                    lst_c[j] = i;
                    if(fst_l[i] == 0){
                        fst_l[i] = j;
                    }
                    if(fst_c[j] == 0){
                        fst_c[j] = i;
                    }
                }
            }
        }

        bool ok = true;

        int _x = 0;
        int _y = 0;

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(s[i][j] == '.'){
                    ok &= ((i < fst_c[j] || i > lst_c[j]) && (j < fst_l[i] || j > lst_l[i]));
                }
                viz[i][j] = 0;
                if(s[i][j] == 'G'){
                    _x = i;
                    _y = j;
                }
            }
        }

        if(_x == 0){
            return ;
        }

        dfs(_x,_y);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(s[i][j] == 'G'){
                    ok &= (viz[i][j]);
                }
            }
        }

        ans += ok;

        if(ans == MOD){
            ans = 0;
        }

        if(ok){
            for(int i = 1;i <= n;i++){
                cout << s[i] << "\n";
            }
            cout << "\n";
        }

        return ;
    }

    btr(x + (y / n),(y % n) + 1);
    if(s[x][y] == 'G'){
        s[x][y] = '.';
        btr(x + (y / n),(y % n) + 1);
        s[x][y] = 'G';
    }
}

int main(){
    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> s[i];
        s[i] = " " + s[i];
    }

    btr(1,1);

    cout << ans;

    return 0;
}
