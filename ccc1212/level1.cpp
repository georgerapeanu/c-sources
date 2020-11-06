#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

double getTurnRadius(double wheelBase,double steeringAngle){
    return wheelBase / sin(steeringAngle);
}

double rad2deg(double angle){
    return angle / PI * 180;
}

double deg2rad(double angle){
    return angle / 180 * PI;
}

int main(){

    double wheelBase;
    double steeringAngle;

    cin >> wheelBase >> steeringAngle;
    cout << fixed << setprecision(2) << getTurnRadius(wheelBase,deg2rad(steeringAngle));

    return 0;
}
