#include <iostream>
#include <cstdio>

using namespace std;
struct dr{
    int x1,x2,y1,y2;
    int area(){
        return (x2 - x1) * (y2 - y1);
    }
    int sect(dr &other){
        int minX = 1005;
        int minY = 1005;
        int maxX = -1005;
        int maxY = -1005;
        for(int i = - 1000;i <= 1000;i++){
            for(int j = - 1000;j <= 1000;j++){
                if(x1 <= i && i <=x2 && y1 <= j && j <= y2){
                    if(other.x1 <= i && i <= other.x2 && other.y1 <= j && j <= other.y2){
                        minX = min(minX,i);
                        maxX = max(maxX,i);
                        minY = min(minY,j);
                        maxY = max(maxY,j);
                    }
                }
            }
        }
        if(minX > maxX || minY > maxY){
            return 0;
        }
        return (maxX - minX) * (maxY - minY);
    }
}D1,D2,D3;
int main()
{
    freopen("billboard.in","r",stdin);
    freopen("billboard.out","w",stdout);
    cin >> D1.x1 >> D1.y1 >> D1.x2 >> D1.y2;
    cin >> D2.x1 >> D2.y1 >> D2.x2 >> D2.y2;
    cin >> D3.x1 >> D3.y1 >> D3.x2 >> D3.y2;
    cout << D1.area() + D2.area() - D3.sect(D1) - D3.sect(D2);
    return 0;
}
