#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string s;

int suff_sum[1005];

int main(){
    cin >> s;

    s = " " + s;

    int st = 1,dr = (int)s.size() - 1;

    vector<int> lft;
    vector<int> rgt;

    while(st < dr){
        while(st < (int)s.size() && s[st] == ')'){
            st++;
        }
        while(dr > 0 && s[dr] == '('){
            dr--;
        }
        if(st < dr){
            lft.push_back(st);st++;
            rgt.push_back(dr);dr--;
        }
    }

    reverse(rgt.begin(),rgt.end());

    for(auto it:rgt){
        lft.push_back(it);
    }

    if(lft.empty()){
        cout << "0\n";
    }
    else{
        cout << "1\n" << lft.size() << "\n";

        for(auto it:lft){
            cout << it << " ";
        }
    }

    return 0;
}
