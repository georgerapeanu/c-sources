#include <fstream>
#include <iostream>

using namespace std;

ifstream f("hacker.in");
ofstream g("hacker.ok");

int n,k;
string s;
string t;
int ans;

void btr(int pos){
    if(pos >= n){
        for(int i = 0;i < n - 1;i++){
            if(t.substr(n - 1 - i,i + 1) == t.substr(0,i + 1)){
                return ;
            }
        }
        ans++;
        ans %= int(666013);
        return ;
    }

    if(s[pos] != '?'){
        btr(pos + 1);
    }
    else{
        for(int i = 0;i < k;i++){
            t[pos] = '0' + i;
            btr(pos + 1);
        }
    }
}

int main(){

    f >> n >> k;
    f >> s;
    t = s;

    btr(0);

    g << ans;

    f.close();
    g.close();

    return 0;
}
