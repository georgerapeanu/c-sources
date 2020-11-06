#include <bits/stdc++.h>

using namespace std;

vector<string> vec_splitter(string s) {
    s += ',';
    vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}
void debug_out(
    vector<string> __attribute__ ((unused)) args,
    __attribute__ ((unused)) int idx,
    __attribute__ ((unused)) int LINE_NUM) {
    cerr << endl;
}
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", ";
    else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss;
    ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}
#ifdef XOX
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif


int n;
set<pair<int,int> > points;

map<int,int> active;

int main() {

    cin >> n;

    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        points.insert({a,0});
        active[a] = 0;
    }

    for(int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        points.insert({b,1});
        active[b] = i;
    }

    priority_queue<pair<int,pair<int,int>> > pq;

    set<pair<int,int> > ::iterator lst = points.end();

    for(set<pair<int,int> > :: iterator it = points.begin(); it != points.end(); it++) {
        if(lst != points.end()) {
            if(lst->second != it->second) {
                pq.push({it->first - lst->first,{lst->first,it->first}});
            }
        }
        lst =  it;
    }

    long long ans = 0;
    vector<int> ans_v;

    while(!pq.empty()) {
        int dist = pq.top().first;
        int a = pq.top().second.first;
        int b = pq.top().second.second;

        pq.pop();

        if(active.count(a) == 0 || active.count(b) == 0) {
            continue;
        }

        ans += dist;

        if(active[b] != 0) {
            ans_v.push_back(active[b]);
        }
        else {
            ans_v.push_back(active[a]);
        }

        active.erase(a);
        active.erase(b);
        points.erase(points.lower_bound({a,0}));
        points.erase(points.lower_bound({b,0}));

        set<pair<int,int> > :: iterator tmp;

        tmp = points.lower_bound({a,0});

        if(tmp != points.begin()) {
            tmp--;
            pair<int,int> fst = *tmp;
            tmp = points.lower_bound({b,0});
            if(tmp != points.end()) {
                pair<int,int> snd = *tmp;
                if(fst.second != snd.second) {
                    pq.push({snd.first - fst.first,{fst.first,snd.first}});
                }
            }
        }
    }

    printf("%lld\n",ans);
    for(auto it:ans_v) {
        printf("%d ",it);
    }

    return 0;
}
