#include "artclass.h"
#include <cstdio>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

set<pair<pair<int,int>,int> > s;

bool viz[500][500];

double abs_gr(int a){
    if(a <= 255 / 2.0){
        a = 255 - a;
    }
    const double split = 200;
    const double split_val = 0.50;
    if(a <= split) return a / (split / split_val);
    return split_val + (1 - split_val) * (a - split) / (255 - split);
}

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
    
    double averageR = 0;
    double averageG = 0;
    double averageB = 0;
    double indiv_average = 0;
    double min_average = 0;
    double area = 0;
    int cnt = 0;
    double absolutes = 0;

    for(int i = 0;i < H;i++){
        for(int j = 0;j < W;j++){
            s.insert(make_pair(make_pair(R[i][j],G[i][j]),B[i][j]));
            averageR += R[i][j];
            averageG += G[i][j];
            averageB += B[i][j];
            absolutes += abs_gr(R[i][j]) * abs_gr(G[i][j]) * abs_gr(B[i][j]);

            indiv_average += max(R[i][j],max(G[i][j],B[i][j]));
            min_average += min(R[i][j],min(G[i][j],B[i][j]));
            cnt += ((R[i][j] >= B[i][j] - 40) && (G[i][j] >= R[i][j] - 40));
        }
    }

    absolutes /= H;
    absolutes /= W;

    averageR /= H;
    averageR /= W;
    averageR /= 255.0;

    averageG /= H;
    averageG /= W;
    averageG /= 255.0;

    averageB /= H;
    averageB /= W;
    averageB /= 255.0;

    indiv_average /= H;
    indiv_average /= W;
    indiv_average /= 255.0;

    min_average /= H;
    min_average /= W;
    min_average /= 255.0;

    double average = (averageR + averageG + averageB) / 3.0;
    double averageRGB = (0.20 * averageR + 0.55 * averageG + 0.25 * averageB);

    int num = s.size();
    
    int comp = 0;
    const int delta = 30;

    for(int i = 0;i < H;i++){
        for(int j = 0;j < W;j++){
            if(viz[i][j] == false){
                queue< pair<int,int> > q;
                q.push({i,j});
                viz[i][j] = true;
                comp++;

                while(!q.empty()){
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();

                    for(int k = 0;k < 4;k++){
                        int xx = x + dx[k];
                        int yy = y + dy[k];
                        if(xx < 0 || xx >= H || yy < 0 || yy >= W || viz[xx][yy]){
                            continue;
                        }
                        if(abs(R[x][y] - R[xx][yy]) +
                           abs(G[x][y] - G[xx][yy]) +
                           abs(B[x][y] - B[xx][yy]) <=
                           delta){
                            viz[xx][yy] = true;
                            q.push({xx,yy});
                        }
                    }
                }
            }
        }
    }

    if(comp <= 400){
        return 4;
    }
    else{
        if(absolutes >= 0.30){
            return 1;
        }
        else{
            if((double)num / comp <= 2 && averageRGB >= 0.38){
                return 3;
            }
            else{
                return 2;
            }        
        }
    }

    printf("%d ",num);
    printf("%d ",comp);
    printf("%.4f ",average);
    printf("%.4f ",indiv_average);
    printf("%.4f ",min_average);
    printf("%.4f ",double(indiv_average - min_average));
    printf("%.4f ",averageR);
    printf("%.4f ",averageG);
    printf("%.4f ",averageB);
    printf("%.4f ",averageRGB);
    printf("%.4f ",absolutes);
    printf("%.4f ",(double)num / comp);
    printf("%.4f ",(double)cnt / (H * W));

    

    return -1;
}
