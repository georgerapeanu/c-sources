#include <iostream>

using namespace std;
int lvl[100005];
bool ok[100005];
int rez = 0;
int N;
int main(){
    cin >> N;
    ok[1] = 1;
    lvl[1] = 1;
    rez = 1;
    for(int i = 2;i <= N;i++){
        int p;
        cin >> p;
        lvl[i] = 1 + lvl[p];
        if(ok[lvl[i]]){
            ok[lvl[i]] = 0;
            rez--;
        }
        else{
            ok[lvl[i]] = 1;
            rez++;
        }
    }
    cout << rez;
    return 0;
}
