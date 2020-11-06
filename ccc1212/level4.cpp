#include <bits/stdc++.h>

using namespace std;

struct point_t {
    double x,y;

    point_t() {
        x = 0;
        y = 0;
    }

    point_t(double x,double y) {
        this->x = x;
        this->y = y;
    }

    point_t operator + (const point_t &other)const {
        return point_t(this->x + other.x,this->y + other.y);
    }

    point_t operator * (const double &val)const{
        return point_t(this->x * val,this->y * val);    
    }

};

struct rover_t {
    point_t p;
    double wheelBase;
    double direction;

    rover_t() {
        p = point_t();
        wheelBase = 0;
        direction = 0;
    }

    rover_t(double wheelBase) {
        p = point_t();
        this->wheelBase = wheelBase;
        this->direction = 0;
    }
};

const double PI = acos(-1);

double getTurnRadius(double wheelBase,double steeringAngle) {
    return wheelBase / sin(steeringAngle);
}

double rad2deg(double angle) {
    return angle / PI * 180;
}

double deg2rad(double angle) {
    return angle / 180 * PI;
}

double getInRange(double val,double l,double r){
    double len = r - l;

    if(val >= r){
        val -= l;
        val = val - double(int(val / len)) * len;
        val += l;
    }
    if(val < l){
        val = r - val;
        val = val - double(int(val / len)) * len;
        val = r - val;
    }

    return val;
}

rover_t getNewRover(rover_t &rover,double distance,double steeringAngle){

    steeringAngle = getInRange(steeringAngle,0,360);

    if(steeringAngle == 0){
        rover_t ans;
        ans.p = rover.p + point_t(sin(rover.direction),cos(rover.direction)) * distance;
        ans.wheelBase = rover.wheelBase;
        ans.direction = rover.direction;
        return ans;
    }

    double turnRadius = getTurnRadius(rover.wheelBase,deg2rad(steeringAngle));
    double ang = distance / turnRadius;
    rover_t ans;
   
    point_t turningPoint = rover.p + point_t(cos(rover.direction),-sin(rover.direction)) * turnRadius;  

    point_t tmp = point_t(-cos(rover.direction + ang),sin(rover.direction + ang));

    ans.p = turningPoint + point_t(-cos(rover.direction + ang),sin(rover.direction + ang)) * turnRadius;
    ans.wheelBase = rover.wheelBase;
    ans.direction = rover.direction + ang;

    ans.direction = getInRange(ans.direction,0,2 * PI);

    return ans;
}

int main() {

    double wheelBase = 3.60;
    double maxSteeringAngle = 14.00;
    double targetX = 0,targetY = 0;
    double targetRadius = 3.00;

    printf("%.2f\n",getTurnRadius(wheelBase,maxSteeringAngle));

    return 0;
}
