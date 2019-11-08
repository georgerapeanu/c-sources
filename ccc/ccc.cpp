#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int VMAX = 1e9;
const int KMAX = 1e5;

int n,m;
int t;
int a[NMAX + 5][NMAX + 5];
int col[NMAX + 5][NMAX + 5];

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};
const int d8x[] = {-1,-1,0,1,1,1,0,-1};
const int d8y[] = {0,1,1,1,0,-1,-1,-1};
const long double eps = 1e-6;

int border[NMAX + 5];
bool is_border[NMAX + 5][NMAX + 5];
vector<pair<int,int> > comp[NMAX + 5];
pair<long double,long double> capital[NMAX + 5];
bool ok_place[NMAX + 5][NMAX + 5];

long double get_dist(pair<long double,long double> a,pair<long double,long double> b) {
    return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}

int my_int(long double val) {
    if(int(val) <= val) {
        //    printf("%.6f %d\n",double(val),int(val));
        return int(val);
    }
    //   printf("%.6f %d\n",double(val),int(val) - 1);
    return int(val) - 1;
}

pair<int,int> get_cell(long double a,long double b) {
    if(a - my_int(a) - 0.5 > 0) {
        a++;
    }
    if(b - my_int(b) - 0.5 > 0) {
        b++;
    }

    return {my_int(a),my_int(b)};
}

bool ok( pair<int,int> a) {
    if(a.first < 0 || a.first >= n || a.second < 0 || a.second >= m) {
        return false;
    }
    return true;
}

struct light_stuff_t {
    int x;
    int y;
    long double whx;
    long double why;
};

vector<light_stuff_t >  do_light_beam(int n,int m,int stx,int sty,int dx,int dy) {

    if(dx == 0 && dy == 0) {
        return {{stx,sty,stx,sty}};
    }

    long double x = stx;
    long double y = sty;

    vector<light_stuff_t> ans;
    ans.push_back({get_cell(x,y).first,get_cell(x,y).second,x,y});
    while(true) {
        int i = get_cell(x,y).first;
        int j = get_cell(x,y).second;

        if(ok({i,j}) == false) {
            break;
        }

        long double nx = 0,ny = 0;
        long double nx_cost = 0,ny_cost = 0;

        if(dx < 0) {
            nx = get_cell(x - 1,y).first + 0.5;
            nx_cost = (x - nx) / abs(double(dx));
        }
        else if(dx == 0) {
            nx = x;
            nx_cost = 1e9;
        }
        else {
            nx = get_cell(x + 1,y).first - 0.5;
            nx_cost = (nx - x) / abs(double(dx));
        }

        if(dy < 0) {
            ny = get_cell(x,y - 1).second + 0.5;
            ny_cost = (y - ny) / abs(double(dy));
        }
        else if(dy == 0) {
            ny = y;
            ny_cost = 1e9;
        }
        else {
            ny = get_cell(x,y + 1).second - 0.5;
            ny_cost = (ny - y) / abs(double(dy));
        }

//            printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",double(x),double(y),double(nx),double(ny),double(nx_cost),double(ny_cost));
        if(ny_cost - nx_cost > eps) {
            y += (nx_cost + eps) * dy;
            x += (nx_cost + eps) * dx;
            ans.push_back({get_cell(x,y).first,get_cell(x,y).second,x - dx * eps,y - dy * eps});
        }
        else if(abs(ny_cost - nx_cost) < eps) {
            long double bx = x;
            long double by = y;
            if(abs(dx) > abs(dy)) {
                y += (nx_cost + eps) * dy;
                x += (nx_cost + eps) * dx;
                if(ok(get_cell(x,by))) {
                    ans.push_back({get_cell(x,by).first,get_cell(x,by).second,x - eps * dx,by});
                }
                if(ok(get_cell(bx,y))) {
                    ans.push_back({get_cell(bx,y).first,get_cell(bx,y).second,bx,y - eps * dy});
                }
                ans.push_back({get_cell(x,y).first,get_cell(x,y).second,x - dx * eps,y - dy * eps});
            }
            else {
                y += (ny_cost + eps) * dy;
                x += (ny_cost + eps) * dx;
                if(ok(get_cell(bx,y))) {
                    ans.push_back({get_cell(bx,y).first,get_cell(bx,y).second,bx,y - eps * dy});
                }
                if(ok(get_cell(x,by))) {
                    ans.push_back({get_cell(x,by).first,get_cell(x,by).second,x - eps * dx,by});
                }
                ans.push_back({get_cell(x,y).first,get_cell(x,y).second,x - dx * eps,y - dy * eps});
            }
        }
        else {
            y += (ny_cost + eps) * dy;
            x += (ny_cost + eps) * dx;
            ans.push_back({get_cell(x,y).first,get_cell(x,y).second,x - dx * eps,y - dy * eps});
        }
    }

    return ans;
}

class dijkstra_solver {
public:
    vector<vector<pair<int,long double> > > graph;

    dijkstra_solver(int n) {
        graph.resize(n + 1);
    }

    void add_edge(int x,int y,long double cost) {
        graph[x].push_back({y,cost});
        graph[y].push_back({x,cost});
    }

    vector<long double> get(int orig,long double orig_cost) {
        vector<long double> ans(graph.size(),1e9);
        priority_queue<pair<long double,int>,vector<pair<long double,int> >,greater<pair<long double,int> > > pq;
        ans[orig] = orig_cost;
        pq.push({orig_cost,orig});

        while(pq.empty() == false) {
            long double cost = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            if(cost != ans[node]) {
                continue;
            }
            for(auto it:graph[node]) {
                if(ans[it.first] > ans[node] + it.second) {
                    ans[it.first] = ans[node] + it.second;
                    pq.push({ans[it.first],it.first});
                }
            }
        }
        return ans;
    }
};

int h;
int k;
struct solar_panel {
    int x;
    int y;
    int cost;
} sp[KMAX + 5];

struct ray_t {
    int dx;
    int dy;
    int dz;
} rays[KMAX + 5];

vector<int> cost[NMAX + 5];

bool can_reach(light_stuff_t fst,light_stuff_t snd,ray_t d) {

    if(ok({snd.x,snd.y}) == false) {
        return true;
    }

///    printf("can reach from %d %d %.6f %.6f to %d %d %.6f %.6f with %d %d %d\n",fst.x,fst.y,double(fst.whx),double(fst.why),snd.x,snd.y,double(snd.whx),double(snd.why),d.dx,d.dy,d.dz);

    long double ha = a[fst.x][fst.y] + 0.5;
    long double hb = 0;
    if(d.dx != 0) {
        hb = ha + (snd.whx - fst.whx) / d.dx * d.dz;
    }
    else {
        hb = ha + (snd.why - fst.why) / d.dy * d.dz;
    }
    /// printf("ha hb are and expected height %.6f %.6f %d",double(ha),double(hb),a[snd.x][snd.y]);

    if(hb <= 0.5 + a[snd.x][snd.y]) {
        ///  printf("ans false\n");
        return false;
    }

    ///printf("ans true\n");
    return true;
}

int main() {

    scanf("%d",&h);

    for(int i = 0; i < h; i++) {
        scanf("%d %d %d\n",&rays[i].dy,&rays[i].dz,&rays[i].dx);///in my system
    }

    scanf("%d %d",&n,&m);

    int mi = VMAX + 5;
    int ma = -VMAX - 5;
    long double avg = 0;

    int ma_country = -VMAX - 5;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d",&a[i][j]);
            scanf("%d",&col[i][j]);
            mi = min(mi,a[i][j]);
            ma = max(ma,a[i][j]);
            avg += a[i][j];
            ma_country = max(ma_country,col[i][j]);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            comp[col[i][j]].push_back({i,j});
            capital[col[i][j]].first += i;
            capital[col[i][j]].second += j;
            for(int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];
                if(x < 0 || x >= n || y < 0 || y >= m || col[i][j] != col[x][y]) {
                    border[col[i][j]]++;
                    is_border[i][j] = true;
                    break;
                }
            }
        }
    }

    for(int i = 0; i <= ma_country; i++) {
        capital[i].first /= double(comp[i].size());
        capital[i].second /= double(comp[i].size());
        capital[i].first = int(capital[i].first);
        capital[i].second = int(capital[i].second);

        pair<int,int> best_cap = comp[i].back();
        long double dist = 1e9;

        for(auto it:comp[i]) {
            if(is_border[it.first][it.second]) {
                continue;
            }
            if(dist > get_dist(it,capital[i])) {
                dist = get_dist(it,capital[i]);
                best_cap = it;
            }
        }
        capital[i] = best_cap;
    }

    /*
    dijkstra_solver pula(ma_country + 1);

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            for(int k = 0;k < 4;k++){
                int x = i + dx[k];
                int y = j + dy[k];
                if(ok({x,y}) == true && col[i][j] != col[x][y]){
                    pula.add_edge(col[i][j],col[x][y],int(get_dist(capital[col[i][j]],capital[col[x][y]])));
                }
            }
        }
    }

    for(int i = 0;i < k;i++){
        vector<long double> tmp = pula.get(sp[i].orig,sp[i].cost);

        for(int j = 0;j < (int)tmp.size();j++){
            cost[j].push_back(tmp[j]);
        }
    }

    for(int i = 0;i <= ma_country;i++){
        for(auto it:cost[i]){
            printf("%d ",int(it));
        }
        printf("\n");
    }*/

    for(int i = 1; i < n - 1; i++) {
        for(int j = 1; j < m - 1; j++) {
            if(is_border[i][j]) {
                continue;
            }
            int t_al = a[i][j];
            int t_col = col[i][j];
            bool valid = true;
            for(int k = 0; k < 8; k++) {
                int xx = i + d8x[k];
                int yy = j + d8y[k];
                if(ok({xx,yy}) && t_al == a[xx][yy] && t_col == col[xx][yy] && is_border[xx][yy] == false) {
                    ;
                }
                else {
                    valid = false;
                }
            }
            ok_place[i][j] = valid;
            if(valid) {
                sp[k] = {i,j,0};
                k++;
            }
        }
    }

    vector<pair<pair<int,int>,int>> ans;
    for(int i = 0; i < k; i++) {
        int hours = 0;
        for(int j = 0; j < h; j++) {
            auto cells = do_light_beam(n,m,sp[i].x,sp[i].y,-rays[j].dx,-rays[j].dy);
            bool reach = true;
            for(int l = 1; l < (int)cells.size(); k++) {
                reach &= can_reach(cells[0],cells[l], {-rays[j].dx,-rays[j].dy,-rays[j].dz});
            }
            hours += reach;
        }
        ans.push_back({{sp[i].x,sp[i].y},hours});
    }

    sort(ans.begin(),ans.end(),[&](pair<pair<int,int>,int> a,pair<pair<int,int>,int> b) {
        if(col[a.first.first][a.first.second] != col[b.first.first][b.first.second]) {
            return col[a.first.first][a.first.second] < col[b.first.first][b.first.second];
        }

        if(a.second != b.second) {
            return a.second > b.second;
        }

        if(a.first.first != b.first.first) {
            return a.first.first < b.first.first;
        }

        return a.first.second < b.first.second;

    });

    for(auto it:ans) {
        printf("%d %d %d\n",it.first.second,it.first.first,it.second);
    }

    return 0;
}
