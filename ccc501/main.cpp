#include <bits/stdc++.h>

using namespace std;



int main(){

    while(true){
        string s;
        int p_x;
        int p_m;
        string tmp_s;
        int tmp;
        int x,y,v_x,v_y;
        string upd;

        cin >> s;
        cin >> p_x >> p_m;
        cin >> tmp_s;
        cin >> tmp;
        cin >> tmp;
        cin >> x >> y >> v_x >> v_y;
        cin >> upd;

        if(p_x < x && x < p_x + 150){
            cout << "move 0\n";
        }
        else if(x < p_x){
            cout << "move -36\n";
        }
        else{
            cout << "move 36\n";
        }
    }

    return 0;
}
