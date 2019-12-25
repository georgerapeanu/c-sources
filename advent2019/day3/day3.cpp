#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


vector<pair<int,int> > a;
vector<pair<int,int> > b;

map<pair<int,int>,int> chestie;
map<pair<int,int>,int> dist1;
map<pair<int,int>,int> dist2;

string s,t;

int main() {
    cin >> s;
    cin >> t;

    s = s + ',';
    t = t + ',';

    int num = 0;
    char dir = '\0';

    a.push_back({0,0});
    b.push_back({0,0});

    int d1 = 0;

    for(auto it:s) {
        if(it == ',') {
            if(dir == 'U') {
                for(int x = 1; x <= num; x++) {
                    pair<int,int> tmp = {a.back().first + x,a.back().second};
                    chestie[ {a.back().first + x,a.back().second}] |= 1;
                    d1++;
                    if(dist1.count(tmp) == 0) {
                        dist1[tmp] = d1;
                    }
                }
                a.push_back({a.back().first + num,a.back().second});
            }
            else if(dir == 'D') {
                for(int x = 1; x <= num; x++) {
                    pair<int,int> tmp = {a.back().first - x,a.back().second};
                    chestie[ {a.back().first - x,a.back().second}] |= 1;
                    d1++;
                    if(dist1.count(tmp) == 0) {
                        dist1[tmp] = d1;
                    }
                }
                a.push_back({a.back().first - num,a.back().second});
            }
            else if(dir == 'R') {
                for(int x = 1; x <= num; x++) {
                    pair<int,int> tmp = {a.back().first,a.back().second + x};
                    chestie[ {a.back().first ,a.back().second + x}] |= 1;
                    d1++;
                    if(dist1.count(tmp) == 0) {
                        dist1[tmp] = d1;
                    }
                }
                a.push_back({a.back().first,a.back().second + num});
            }
            else {
                for(int x = 1; x <= num; x++) {
                    pair<int,int> tmp = {a.back().first,a.back().second - x};
                    chestie[ {a.back().first ,a.back().second - x}] |= 1;
                    d1++;
                    if(dist1.count(tmp) == 0) {
                        dist1[tmp] = d1;
                    }
                }
                a.push_back({a.back().first,a.back().second - num});
            }
            num = 0;
        }
        else if('0' <= it && it <= '9') {
            num = num * 10 + (it - '0');
        }
        else {
            dir = it;
        }
    }

    int d2 = 0;

    for(auto it:t) {
        if(it == ',') {
            if(dir == 'U') {
                for(int x = 1; x <= num; x++) {
                    chestie[ {b.back().first + x ,b.back().second}] |= 2;
                    pair<int,int> tmp = {b.back().first + x,b.back().second};
                    d2++;
                    if(dist2.count(tmp) == 0) {
                        dist2[tmp] = d2;
                    }
                }
                b.push_back({b.back().first + num,b.back().second});
            }
            else if(dir == 'D') {
                for(int x = 1; x <= num; x++) {
                    chestie[ {b.back().first - x ,b.back().second}] |= 2;
                    pair<int,int> tmp = {b.back().first - x,b.back().second};
                    d2++;
                    if(dist2.count(tmp) == 0) {
                        dist2[tmp] = d2;
                    }
                }
                b.push_back({b.back().first - num,b.back().second});
            }
            else if(dir == 'R') {
                for(int x = 1; x <= num; x++) {
                    chestie[ {b.back().first ,b.back().second + x}] |= 2;
                    pair<int,int> tmp = {b.back().first,b.back().second + x};
                    d2++;
                    if(dist2.count(tmp) == 0) {
                        dist2[tmp] = d2;
                    }
                }
                b.push_back({b.back().first,b.back().second + num});
            }
            else {
                for(int x = 1; x <= num; x++) {
                    chestie[ {b.back().first, b.back().second - x}] |= 2;
                    pair<int,int> tmp = {b.back().first,b.back().second - x};
                    d2++;
                    if(dist2.count(tmp) == 0) {
                        dist2[tmp] = d2;
                    }
                }
                b.push_back({b.back().first,b.back().second - num});
            }
            num = 0;
        }
        else if('0' <= it && it <= '9') {
            num = num * 10 + (it - '0');
        }
        else {
            dir = it;
        }
    }

    int best = 1e9;

    chestie[ {0,0}] = 0;

    for(auto it:chestie) {
        if(it.second == 3) {
            best = min(best,dist1[it.first] + dist2[it.first]);
        }
    }

    printf("%d\n",best);

    return 0;
}
