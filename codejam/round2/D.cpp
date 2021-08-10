#include <bits/stdc++.h>

using namespace std;

int t;
int n,m,f,s;

const int NMAX = 10;

string _s[NMAX + 5];
int v[NMAX + 5][NMAX + 5];
int dp[NMAX + 1][NMAX + 1][1 << NMAX];

int flip(int conf,int j){
    j--;
    return conf ^ (1 << j);
}

int flip2(int conf,int j){
    j--;
    return conf ^ (3 << j);
}

int get(int conf,int j){
    j--;
    return ((conf >> j) & 1);
}

int set_conf(int conf,int j,int value){
    if(get(conf,j) != value){
        conf = conf ^ (1 << (j - 1));
    }
    return conf;
}

void update(int i,int j,int conf,int value){
    if(dp[i][j][conf] > value){
        dp[i][j][conf] = value;
    }
}

int main(){

    cin >> t;

    for(int test = 1;test <= t;test++){
        
        cin >> n >> m >> f >> s;
        cout << "Case #" << test << ": ";

        for(int i = 1;i <= n;i++){
            cin >> _s[i];
            _s[i] = " " + _s[i];
        }

        for(int i = 1;i <= n;i++){
            string tmp;
            cin >> tmp;

            tmp = " " + tmp;
            for(int j = 1;j <= m;j++){
                v[i][j] = (_s[i][j] != tmp[j]);
            }
        }

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                for(int conf = 0;conf < (1 << m);conf++){
                    dp[i][j][conf] = 1e9;
                }
            }
        }

        dp[1][1][0] = (v[1][1] == 0 ? 0:f);
        dp[1][1][1] = (v[1][1] == 1 ? 0:f);
        for(int j = 2;j <= m;j++){
            for(int conf = 0;conf < (1 << (j - 1));conf++){
                for(int h = 0;h < 2;h++){
                    ///consider 1-index
                    update(1,j,set_conf(conf,j,v[1][j]),dp[1][j - 1][conf] + f * h);
                    if(get(set_conf(conf,j,v[1][j]),j - 1) != get(set_conf(conf,j,v[1][j]),j)){
                        update(1,j,flip2(set_conf(conf,j,v[1][j]),j - 1),dp[1][j - 1][conf] + f * h + s);
                    }
                    v[1][j] ^= 1;
                }
            }
        }

        for(int i = 2;i <= n;i++){
            for(int conf = 0;conf < (1 << m);conf++){
                for(int h = 0;h < 2;h++){
                    if(get(conf,1) == 0){
                        update(i,1,set_conf(conf,1,v[i][1]),dp[i - 1][m][conf] + f * h);
                    }else{
                        if(get(conf,1) != get(set_conf(conf,1,v[i][1]),1)){
                            update(i,1,flip(set_conf(conf,1,v[i][1]),1),dp[i - 1][m][conf] + f * h + s);
                        }
                    }
                    v[i][1] ^= 1;
                }
            }
            for(int j = 2;j <= m;j++){
                for(int conf = 0;conf < (1 << m);conf++){
                    for(int h = 0;h < 2;h++){
                        if(get(conf,j) == 0){
                            update(i,j,set_conf(conf,j,v[i][j]),dp[i][j - 1][conf] + f * h);
                            if(get(set_conf(conf,j,v[i][j]),j - 1) != get(set_conf(conf,j,v[i][j]),j)){
                                update(i,j,flip2(set_conf(conf,j,v[i][j]),j - 1),dp[i][j - 1][conf] + f * h + s);
                            }
                        }else{
                            if(get(conf,j) != get(set_conf(conf,j,v[i][j]),j)){
                                update(i,j,flip(set_conf(conf,j,v[i][j]),j),dp[i][j - 1][conf] + f * h + s);
                                if(get(set_conf(conf,j,v[i][j]), j - 1) != get(set_conf(conf,j,v[i][j]),j)){
                                    if(1 - get(flip2(set_conf(conf,j,v[i][j]),j - 1),j) != get(conf,j)){
                                        update(i,j,flip(flip2(set_conf(conf,j,v[i][j]),j - 1),j),dp[i][j - 1][conf] + f * h + 2 * s);
                                    }
                                }
                                if(get(set_conf(conf,j,v[i][j]),j) != get(conf,j)){
                                    if(1 - get(flip(set_conf(conf,j,v[i][j]),j),j) != get(conf,j - 1)){
                                        update(i,j,flip2(flip(set_conf(conf,j,v[i][j]),j),j - 1),dp[i][j - 1][conf] + f * h + 2 * s);
                                    }
                                }
                            }
                        }
                        v[i][j] ^= 1;
                    }
                }
            }
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                cerr << v[i][j];
            }
            cerr << "\n";
        }

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                for(int conf = 0;conf < (1 << m);conf++){
                    fprintf(stderr,"%d %d %d is %d\n",i,j,conf,dp[i][j][conf]);
                }
            }
        }

        cout << dp[n][m][0];
        cout << "\n";
    }

    return 0;
}
