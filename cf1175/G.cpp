#include <bits/stdc++.h>

using namespace std;

double get_sect(pair<long long,long long> a,pair<long long,long long> b) {
    return ((double)b.second - a.second) / (a.first - b.first);
}

///missed cases because of 0-chance of getting them in this problem
class LinearMinConvexHull {
public:
    deque<double> sect;
    deque< pair<long long,long long> > lines;

    bool bad_back(pair<long long,long long> line) {
        if((int)lines.size() <= 1) {
            return false;
        }

        if(sect.back() >= get_sect(lines[(int)lines.size() - 2],line)) {
            return true;
        }

        return false;
    }

    bool bad_front(pair<long long,long long> line) {
        if((int)lines.size() <= 1) {
            return false;
        }

        if(sect.front() <= get_sect(lines[1],line)) {
            return true;
        }

        return false;
    }

    void del_back_line() {
        lines.pop_back();
        if(sect.size()) {
            sect.pop_back();
        }
    }

    void del_front_line() {
        lines.pop_front();
        if(sect.size()) {
            sect.pop_front();
        }
    }

    void ins_back_line(pair<long long,long long> line) {
        lines.push_back(line);
        if((int)lines.size() >= 2) {
            sect.push_back(get_sect(lines[(int)lines.size() - 2],lines[(int)lines.size() - 1]));
        }
    }

    void ins_front_line(pair<long long,long long> line) {
        lines.push_front(line);
        if((int)lines.size() >= 2) {
            sect.push_front(get_sect(lines[0],lines[1]));
        }
    }

public:

    void add_back(pair<long long,long long> line) {
        while(bad_back(line)) {
            del_back_line();
        }
        ins_back_line(line);
    }

    void add_front(pair<long long,long long> line) {
        while(bad_front(line)) {
            del_front_line();
        }
        ins_front_line(line);
    }

    pair<long long,long long> get_best_line(long long x) {
        if((int)lines.size() == 1) {
            return lines[0];
        }
        int st = -1,dr = sect.size();
        while(dr - st > 1) {
            int mid = (st + dr) / 2;
            if(sect[mid] <= x) {
                st = mid;
            }
            else {
                dr = mid;
            }
        }
        return lines[dr];
    }
};

class UndoMinConvexHull {
public:

    int len;
    vector<pair<long long,long long> > lines;
    vector<pair<pair<int,int>,pair<long long,long long> > > undo_log;///((pos,len),(a,b))

    UndoMinConvexHull() {
        len = 0;
        lines.clear();
        undo_log.clear();
    }

    void add_line(pair<long long,long long> line) {
        int st = -1,dr = len - 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;

            if(get_sect(lines[mid],lines[mid + 1]) <= get_sect(lines[mid],line)) {
                st = mid;
            }
            else {
                dr = mid;
            }
        }

        ///dr intersected line

        dr++;

        if((int)lines.size() <= dr) {
            lines.push_back({0,0});
        }

        undo_log.push_back({{dr,len},lines[dr]});
        lines[dr] = line;
        len = dr + 1;
    }

    void undo() {
        len = undo_log.back().first.second;
        lines[undo_log.back().first.first] = undo_log.back().second;
        undo_log.pop_back();
    }

    pair<long long,long long> best_line(long long x) {
        int st = -1,dr = len - 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;

            if(get_sect(lines[mid],lines[mid + 1]) <= x) {
                st = mid;
            }
            else {
                dr = mid;
            }
        }

        return lines[dr];
    }

};

///b slopes less than a slopes
///merges into a
///deletes b
void merge_hulls(LinearMinConvexHull &a,LinearMinConvexHull &b) {
    if(a.lines.size() < b.lines.size()) {
        while(a.lines.size()) {
            b.add_front(a.lines.back());
            a.lines.pop_back();
        }
        a.sect.clear();
        a.lines.swap(b.lines);
        a.sect.swap(b.sect);
    }
    else {
        while(b.lines.size()) {
            a.add_back(b.lines.front());
            b.lines.pop_front();
        }
        b.sect.clear();
    }
}

int n,k;
int a[20002];
long long dp[102][20002];

int st[20002],len;
LinearMinConvexHull hulls[20002];

int main() {
    scanf("%d %d",&n,&k);

    int ma = 0;

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        ma = max(ma,a[i]);
        dp[1][i] = 1LL * ma * i;
    }

    UndoMinConvexHull main_hull;
    for(int h = 2; h <= k; h++) {
        for(int i = 1; i <= n; i++) {
            st[++len] = a[i];
            hulls[len].add_front({-(i - 1),dp[h - 1][i - 1]});
            while(len > 1 && st[len - 1] <= st[len]) {
                main_hull.undo();
                merge_hulls(hulls[len - 1],hulls[len]);
                st[len - 1] = st[len];
                len--;
            }
            pair<long long,long long> line = hulls[len].get_best_line(a[i]);
            main_hull.add_line({a[i],1LL * line.first * a[i] + line.second});
            line = main_hull.best_line(i);
            dp[h][i] = 1LL * line.first * i + line.second;
        }
        while(len) {
            hulls[len].lines.clear();
            hulls[len].sect.clear();
            len--;
        }
        while(main_hull.len) {
            main_hull.undo();
        }
    }

    printf("%lld\n",dp[k][n]);

    return 0;
}
