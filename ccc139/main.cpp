#include <bits/stdc++.h>

using namespace std;

int n,m;
int sx,sy;
char st_dir;
char mode;
int width;
bool viz[1005][1005];

////TODO BUGGY IF N <= 3 OR M <= 3, OR N > 1000 OR M > 1000

vector<pair<int,int> > serpentine_travel(int n,int m,int sx,int sy,char st_dir,int width) {
    vector<pair<int,int> > ans;

    if(st_dir == 'N' || st_dir == 'S') {
        swap(n,m);
        swap(sx,sy);
    }

    bool x_sw = false;
    bool y_sw = false;

    bool sw_mowers = false;

    if(sx == 2) {
        sx = 1;
        sw_mowers = true;
    }
    if(sx == n - 1) {
        sx = n;
        sw_mowers = true;
    }

    if(sx != 1) {
        x_sw = true;
    }

    if(sy != 1) {
        y_sw = true;
    }

    int ly = 1;
    int dy = 1;

    for(int i = 1; i <= n; i += width) {
        for(int j = ly; 1 <= j && j <= m; j += dy) {
            if(sw_mowers == false) {
                for(int k = i; k <= i + width - 1; k++) {
                    if(viz[k][j] == false && k <= n) {
                        ans.push_back({k,j});
                        viz[k][j] = true;
                    }
                    else {
                        ans.push_back({0,0});
                    }
                }
            }
            else {
                for(int k = i + width - 1; k >= i; k--) {
                    if(viz[k][j] == false && k <= n) {
                        ans.push_back({k,j});
                        viz[k][j] = true;
                    }
                    else {
                        ans.push_back({0,0});
                    }
                }
            }
            ly = j;
        }
        sw_mowers ^= 1;
        dy *= -1;
    }

    for(auto &it:ans) {
        if(x_sw) {
            it.first = n - it.first + 1;
        }
        if(y_sw) {
            it.second = m - it.second + 1;
        }
    }


    if(st_dir == 'N' || st_dir == 'S') {
        for(auto &it:ans) {
            swap(it.first,it.second);
        }
    }

    return ans;
}

vector<pair<int,int> > circular_travel(int n,int m,int sx,int sy,char st_dir,int width) {
    vector<pair<int,int> > ans;

    if(st_dir == 'N' || st_dir == 'S') {
        swap(n,m);
        swap(sx,sy);
    }

    bool x_sw = false;
    bool y_sw = false;
    bool sw_mowers = false;
    /*
        if(sx == 2){
            sx = 1;
            sw_mowers = true;
        }

        if(sx == n - 1){
            sx = n;
            sw_mowers = true;
        }

        if(sx != 1){
            x_sw = true;
        }

        if(sy != 1){
            y_sw = true;
        }
      */

    ///MANUAL OVERWRITE FOR LAST LEVEL
    x_sw = false;
    y_sw = true;
    sw_mowers = true;

    for(int l = 1,r = n; l <= r; l += width,r -= width) {
        if(l + width - 1 >= r) {
            for(int j = 1; j <= m; j++) {
                if(sw_mowers == false) {
                    ///the first ones get 0
                    for(int k = 1; k <= width - (r - l + 1); k++) {
                        ans.push_back({0,0});
                    }
                    for(int k = l; k <= r; k++) {
                        if(viz[k][j] == false && k <= n) {
                            ans.push_back({k,j});
                        }
                        else {
                            ans.push_back({0,0});
                        }
                    }
                }
                else {
                    for(int k = r; k >= l; k--) {
                        if(viz[k][j] == false && k <= n) {
                            ans.push_back({k,j});
                        }
                        else {
                            ans.push_back({0,0});
                        }
                    }
                    for(int k = 1; k <= width - (r - l + 1); k++) {
                        ans.push_back({0,0});
                    }
                }
            }
            break;
        }
        for(int j = 1; j <= m; j++) {
            if(sw_mowers == false) {
                for(int k = l; k <= l + width - 1; k++) {
                    if(k <= n && viz[k][j] == false) {
                        viz[k][j] = true;
                        ans.push_back({k,j});
                    }
                    else {
                        ans.push_back({0,0});
                    }
                }
            }
            else {
                for(int k = l + width - 1; k >= l; k--) {
                    if(k <= n && viz[k][j] == false) {
                        viz[k][j] = true;
                        ans.push_back({k,j});
                    }
                    else {
                        ans.push_back({0,0});
                    }
                }
            }
        }
        sw_mowers ^= 1;
        if(r <= l + width - 1) {
            break;
        }
        else if(r - width + 1 <= l + width - 1) {
            for(int j = m; j; j--) {
                if(sw_mowers == false) {
                    for(int k = l + width; k < l + width + width; k++) {
                        if(k > n || viz[k][j]) {
                            ans.push_back({0,0});
                        }
                        else {
                            ans.push_back({k,j});
                        }
                    }
                }
                else {
                    for(int k = l + width + width - 1; k >= l + width; k--) {
                        if(k > n || viz[k][j]) {
                            ans.push_back({0,0});
                        }
                        else {
                            ans.push_back({k,j});
                        }
                    }
                }
            }
            break;
        }
        for(int j = m; j; j--) {
            if(sw_mowers == false) {
                for(int k = r - width + 1; k <= r; k++) {
                    if(k <= n && viz[k][j] == false) {
                        viz[k][j] = true;
                        ans.push_back({k,j});
                    }
                    else {
                        ans.push_back({0,0});
                    }
                }
            }
            else {
                for(int  k = r; k >= r - width + 1; k--) {
                    if(k <= n && viz[k][j] == false) {
                        viz[k][j] = true;
                        ans.push_back({k,j});
                    }
                    else {
                        ans.push_back({0,0});
                    }
                }
            }
        }
        sw_mowers ^= 1;
    }

    for(auto &it:ans) {
        if(x_sw) {
            it.first = n - it.first + 1;
        }
        if(y_sw) {
            it.second = m - it.second + 1;
        }
    }

    if(st_dir == 'N' || st_dir == 'S') {
        for(auto &it:ans) {
            swap(it.first,it.second);
        }
    }

    return ans;
}

int cell_to_pos(int n,int m,pair<int,int> cell) {
    if(cell.first < 1 || cell.second < 1 || cell.first > n || cell.second > m) {
        return 0;
    }
    return (cell.first - 1) * m + cell.second;
}

int main() {

    scanf("%d %d %d %d %c %c %d",&n,&m,&sx,&sy,&st_dir,&mode,&width);

    vector<pair<int,int> > tmp;

    if(mode == 'S') {
        tmp = serpentine_travel(n,m,sx,sy,st_dir,width);
    }
    else {
        tmp = circular_travel(n,m,sx,sy,st_dir,width);
    }

    for(auto it:tmp) {
        printf("%d ",cell_to_pos(n,m,it));
    }

    return 0;
}
