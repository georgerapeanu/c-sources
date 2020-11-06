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

    point_t operator - (const point_t &other)const {
        return point_t(this->x - other.x, this->y - other.y);
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

double getTurnRadius(double wheelBase,double steeringAngle) {
    return wheelBase / sin(deg2rad(steeringAngle));
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

    double turnRadius = getTurnRadius(rover.wheelBase,steeringAngle);
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

    const string uid = "d59f8505-be9d-4852-8307-a55edb020780";
    double wheelBase = 3.60;
    double maxSteeringAngle = 14.00;
    double targetX = 80.00,targetY = 65.20;
    double targetRadius = 1.00;


    rover_t rover(wheelBase);

    double turnRadius = getTurnRadius(wheelBase,maxSteeringAngle);

    rover_t newRover = getNewRover(rover,turnRadius * PI / 2,maxSteeringAngle);

    point_t turnVector = newRover.p - rover.p;

    printf("deb %.2f %.2f %.2f\n",newRover.p.x,newRover.p.y,newRover.direction);

    printf("%.2f %.2f\n",targetY - turnVector.y,0.00);
    printf("%.2f %.2f\n",turnRadius * PI / 2,maxSteeringAngle);
    printf("%.2f %.2f\n",targetX - turnVector.x,0.00);

    return 0;
}
