#include <iostream>

using namespace std;

struct data{
    int target;
    int x,y;
    data *ant;
    int dist;
};

queue<data*> Q;

int main(){
    cout << "Hello world!" << endl;
    return 0;
}
