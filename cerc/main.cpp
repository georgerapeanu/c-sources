#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int N;
struct punct{
    double x,y;
    punct operator + (const punct &other)const{
        return {x + other.x,y + other.y};
    }
    punct operator - (const punct &other)const{
        return {x - other.x,y - other.y};
    }
    double len(){
        return sqrt(x * x + y * y);
    }
};
int main(){
    cout << "Hello world!" << endl;
    return 0;
}
