#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

ifstream fin ("rj.in");
ofstream fout ("rj.out");

int a[105][105], n, m;
int R[105][105], J[105][105];
int rx, ry, jx, jy;

queue <int> Qx, Qy;

const int dx[] = {+1, +1, +1, +0, -1, -1, -1, +0},
          dy[] = {+1, +0, -1, -1, -1, +0, +1, +1};

void Lee(int d[][105], int sx, int sy) {
    d[sx][sy] = 1;
    Qx.push(sx);
    Qy.push(sy);

    while (Qx.size()) {
        int x = Qx.front();
        int y = Qy.front();
        Qx.pop();
        Qy.pop();

        for (int k = 0; k < 8; ++k) {
            int xx = x + dx[k];
            int yy = y + dy[k];
            if (xx && yy && xx <= n && yy <= m && d[xx][yy] == 0) {
                d[xx][yy] = d[x][y] + 1;
                Qx.push(xx);
                Qy.push(yy);
            }
        }

    }
}

int main() {
    fin >> n >> m;
    fin.get();
    for (int i = 1; i <= n; ++i) {
        char v[105];
        fin.getline(v, 105);
        for (int j = 0; j < strlen(v); ++j) {
            if (v[j] == 'R') {
                rx = i;
                ry = j + 1;
            }
            else
                if (v[j] == 'J') {
                    jx = i;
                    jy = j + 1;
                }
            else
                if (v[j] == 'X') {
                    R[i][j + 1] = J[i][j + 1] = -1;
                }
        }
    }

    Lee(R, rx, ry);
    Lee(J, jx, jy);
    int MIN = 300, solx = 1, soly = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (R[i][j] > 0 && R[i][j] == J[i][j] && R[i][j] < MIN) {
                solx = i;
                soly = j;
                MIN = R[i][j];
            }
    fout << MIN << " " << solx << " " << soly;
}
