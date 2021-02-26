#include <cstdio>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
pair<int,int> points[NMAX + 5];
set<int> active_x;
set<int> active_y[NMAX + 5];
map<int,int> to_norm;
int real_coord[NMAX + 5];

long long best = 4e18;

long long sqr(long long a){
    return 1LL * a * a;
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;

    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    if(buff[ind] == '-'){
        sgn = -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans * sgn;
}

int main(){

    n = i32();

    for(int i = 1;i <= n;i++){
        points[i].first = i32();
        points[i].second = i32();
        int x = points[i].first;
        int y = points[i].second;
        points[i].first = x + y;
        points[i].second = x - y;
        to_norm[points[i].first] = 1;
    }

    int lst = 0;

    for(auto &it:to_norm){
        it.second = ++lst;
        real_coord[lst] = it.first;
    }

    for(int i = 1;i <= n;i++){
        points[i].first = to_norm[points[i].first];
    }

    for(int i = 1;i <= n;i++){
        set<int> :: iterator it;
        active_x.insert(points[i].first);
        it = active_x.find(points[i].first);

        set<int> :: iterator it2 = it;

        while(true){
            if(it2 == active_x.end() || sqr(real_coord[*it2] - real_coord[points[i].first]) >= best){
                break;
            }
            set<int> :: iterator it3 = active_y[*it2].lower_bound(points[i].second);
            if(it3 != active_y[*it2].end()){
                best = min(best,sqr(real_coord[*it2] - real_coord[points[i].first]) + sqr(points[i].second - *it3));
            }
            if(it3 != active_y[*it2].begin()){
                it3--;
                best = min(best,sqr(real_coord[*it2] - real_coord[points[i].first]) + sqr(points[i].second - *it3));
            }
            it2++;
        }

        it2 = it;
        while(true){
            if(it2 == active_x.begin()){
                break;
            }
            it2--;
            if(sqr(real_coord[*it2] - real_coord[points[i].first]) >= best){
                break;
            }
            set<int> :: iterator it3 = active_y[*it2].lower_bound(points[i].second);
            if(it3 != active_y[*it2].end()){
                best = min(best,sqr(real_coord[*it2] - real_coord[points[i].first]) + sqr(points[i].second - *it3));
            }
            if(it3 != active_y[*it2].begin()){
                it3--;
                best = min(best,sqr(real_coord[*it2] - real_coord[points[i].first]) + sqr(points[i].second - *it3));
            }
        }
        active_y[points[i].first].insert(points[i].second);
        if(i == 1){
            continue;
        }
        printf("%lld\n",best / 2);
    }

    return 0;
}

