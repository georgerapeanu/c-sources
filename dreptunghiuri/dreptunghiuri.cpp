#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

FILE *f = fopen("dreptunghiuri.in","r");
FILE *g = fopen("dreptunghiuri.out","w");

int n,m;

///we set the bounding box.there will be at least a point on every edge(condition 1)
///after that,it is a necessary and sufficient condition for a rectangle to have its diagonlas equal and to intersect in the middle of both(condition 2)
///because of (condition 1) the intersection point has to be (h/2,w/2)
///because of (condition 2),any shift from the horizontal line y=h/2 has to be mirrored.(so there will be an equal delta_h on both sides)
///also because of (condition 2), diagonals are equal so h^2 + (2*delta_h)^2 = w^2 + (2 * delta_w)^2
///to avoid dealing with parity cases, we just use deltah_2=2*delta_h
///if there is a pair of delta's for a set (h,w) then we add to the count of local answers the product of the number of solutions(+/- delta if != 0)
///we subtract 3 because there will be 2 degenerate cases were the 2 diagonals overlap and are a diagonal of the bounding box itself,and the case where
///the rectangle is the bounding box is counted twice

int main(){

    fscanf(f,"%d %d",&n,&m);

    n--;m--;///because this uses dimensions,not count of points

    long long ans = 0;

    for(int h = 1;h <= n;h++){
        for(int w = 1;w <= m;w++){
            long long total = -3;
            int deltaw_2 = (w % 2);
            for(int deltah_2 = h % 2;deltah_2 <= h;deltah_2 += 2){
                long long deltaw_p_2 = -1LL * h * h + 1LL * deltah_2 * deltah_2  + 1LL * w * w;
                
                while(deltaw_2 < w && 1LL * deltaw_2 * deltaw_2 < deltaw_p_2){
                    deltaw_2 += 2;
                }
                
                if(1LL * deltaw_2 * deltaw_2 != deltaw_p_2){
                    continue;
                }
                total +=  (1 + (deltah_2 != 0)) * (1 + (deltaw_2 != 0));
            }
            ans += total * (n - h + 1) * (m - w + 1);
        }
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
