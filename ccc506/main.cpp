#include <bits/stdc++.h>

using namespace std;

const double INF = 1e6;
const double TIME_STEP = 0.10;

double speed = 0;
double dist = 0;
double _time = 0;
double current_speed_limit;
double distance_to_next;
double next_speed_limit;

string command;

bool parse_command() {
    cin >> command;
    if(command == "update") {
        return false;
    }
    if(command == "speed") {
        cin >> speed;
        speed *= 1000.00 / 3600.00;
    }
    else if(command == "distance") {
        cin >> dist;
    }
    else if(command == "time") {
        cin >> _time;
    }
    else if(command == "speedlimit") {
        cin >> current_speed_limit >> distance_to_next >> next_speed_limit;
        current_speed_limit *= 1000.00 / 3600.00;
        next_speed_limit *= 1000.00 / 3600.00;
        if(distance_to_next == 0 && next_speed_limit == 0) {
            next_speed_limit = INF;
        }
        if(current_speed_limit == 0) {
            current_speed_limit = INF;
        }
    }
    return true;
}

int main() {

    while(dist < 1500) {
        while(parse_command());

        if(current_speed_limit <= next_speed_limit || (speed == 0 || distance_to_next / speed > 4)) {
            printf("throttle %.2f\n",min(17.50,(current_speed_limit - speed) / TIME_STEP * (speed <= 1e-2 ? 100:speed)));
            printf("brake %.2f\n",0.00);
        }
        else if(speed > next_speed_limit) {
            printf("throttle %.2f\n",0.00);
            printf("brake %.2f\n",100.00);
        }
        else {
            printf("throttle %.2f\n",min(17.50,(next_speed_limit - speed) / TIME_STEP * (speed <= 1e-2 ? 100:speed)));
            printf("brake %.2f\n",0.00);
        }


    }
    return 0;
}
