#include <iostream>
#include <cstdlib>
using namespace std;
int N;
int baga(int val){
    string ans;
    cout << val << endl;
    cin >> ans;
    if(ans == "Male"){
        return 0;
    }
    if(ans == "Female"){
        return 1;
    }
    exit(0);
}
int main(){
    cin >> N;
    int tmp = baga(0);
    int st = 0,dr = N;
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        int tmp2 = baga(mid);
        if(tmp2 == tmp ^ (mid % 2)){
            st = mid;
        }
        else{
            dr = mid;
        }
    }
    baga(st);
    baga(dr);
    return 0;
}
