#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
string s;
int rez = 0;
int realpos(int pos){
    return pos % (int)s.size();
}
int main()
{
    cin >> s;
    for(char c = 'a';c <= 'z';c++){
        int tmp = 0;
        vector<int> pos;
        for(int i = 0;i < (int)s.size();i++){
            if(s[i] == c){
                pos.push_back(i);
            }
        }
        for(int dist = 0;dist < (int)s.size();dist++){
            map<pair<char,char>,int> M;
            for(auto it:pos){
                M[{s[it],s[realpos(it + dist)]}]++;
            }
            int ceva = 0;
            for(auto it:M){
                ceva += (it.second == 1);
            }
            tmp = max(tmp,ceva);
        }
        rez += tmp;
    }
    cout << fixed << setprecision(8) << double(rez) / double(s.size());
    return 0;
}
