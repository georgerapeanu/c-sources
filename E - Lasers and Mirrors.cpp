#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

int n;
int p[1005];
bool viz[1005];
string ans[1005];
int line;

void put(int from,int where){

    if(from <= where){
        ans[line][from] = '/';
        ans[line][where] = '/';
    }

    else{
        ans[line][from] = '\\';
        ans[line][where] = '\\';
    }

    line--;
}

int main(){

    cin >> n;

    line = n - 1;

    for(int i = 0;i < n;i++){
        cin >> p[i];
        p[i]--;
        ans[i] = string(n,'.');
    }

    int dead_laser = -1;

    for(int i = 0;i < n;i++){
        if(!viz[i]){
            vector<int> cycle;
            int nod = i;
            while(!viz[nod]){
                cycle.push_back(nod);
                viz[nod] = 1;
                nod = p[nod];
            }

            reverse(cycle.begin(),cycle.end());

            if(cycle.size() > 1){
                if(dead_laser != -1){

                    for(int st = 0;st < (int)cycle.size();st++){
                        if(dead_laser <= cycle[st] && cycle[st] <= cycle[(st + 1) % cycle.size()]){
                            put(cycle[(st + 1) % cycle.size()],cycle[st]);
                            ans[line + 1][dead_laser] = '\\';

                            for(int i = st + 2;i < (int)cycle.size();i++){
                                put(cycle[i],cycle[i - 1]);
                            }

                            for(int i = (st == (int)cycle.size() - 1);i < st;i++){
                                put(cycle[i],cycle[i == 0 ? (int)cycle.size() - 1:i - 1]);
                            }

                            put(dead_laser,cycle[st == 0 ? (int)cycle.size() - 1:st - 1]);
                            goto done1;
                        }
                        else if(dead_laser >= cycle[st] && cycle[st] >= cycle[(st + 1) % cycle.size()]){
                            put(cycle[(st + 1) % cycle.size()],cycle[st]);
                            ans[line + 1][dead_laser] = '/';

                            for(int i = st + 2;i < (int)cycle.size();i++){
                                put(cycle[i],cycle[i - 1]);
                            }

                            for(int i = 0;i < st;i++){
                                put(cycle[i],cycle[i == 0 ? (int)cycle.size() - 1:i - 1]);
                            }

                            put(dead_laser,cycle[st == 0 ? (int)cycle.size() - 1:st - 1]);
                            goto done1;
                        }
                    }

                    assert(false);

                    done1:;
                }
                else{
                    dead_laser = cycle[0];
                    put(cycle[0],dead_laser);
                    dead_laser = cycle.back();
                    for(int i = 1;i < (int)cycle.size();i++){
                        put(cycle[i],cycle[i - 1]);
                    }
                }
            }
        }
    }

    cout << (dead_laser == -1 ? n : n - 1) << "\n";

    for(int i = 0;i < n;i++){
        cout << ans[i] << "\n";
    }

    return 0;
}