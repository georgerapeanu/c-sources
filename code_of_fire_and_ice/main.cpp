#include <bits/stdc++.h>

using namespace std;

///fliped x,y

struct point_t {
    int x,y;

    point_t() {
        x = y = 0;
    }

    point_t(int x,int y) {
        this->x = x;
        this->y = y;
    }

    bool operator == (const point_t &other)const {
        return x == other.x && y == other.y;
    }

    bool operator != (const point_t &other)const {
        return x != other.x || y != other.y;
    }

    bool operator < (const point_t &other)const {
        if(x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    int man_dist(const point_t &other)const {
        return abs(x - other.x) + abs(y - other.y);
    }
};

struct unit_t {
    int id;
    point_t pos;
};

struct building_t {
    point_t pos;
};

struct player_state_t {
    int gold;
    int income;
    vector<unit_t> units[4];
    vector<building_t> buildings[4];

    player_state_t() {
        gold = 0;
        income = 0;
        for(int i = 0; i < 4; i++) {
            units[i].clear();
            units[i].clear();
        }
    }
};

player_state_t me;
player_state_t op;

string elem[12];
bool build_already[12][12];
bool occupied[12][12];
vector<point_t> mine_spots;
int tox,toy;///add case when hq is (11,11) if necessary
int dump;

void init_read() {
    cin >> dump;
    cin.ignore();

    for(int i = 0; i < dump; i++) {
        int x,y;
        cin >> x >> y;
        cin.ignore();
        mine_spots.push_back({x,y});
    }
}

void read_states() {

    me = player_state_t();
    op = player_state_t();

    cin >> me.gold;
    cin.ignore();
    cin >> me.income;
    cin.ignore();
    cin >> op.gold;
    cin.ignore();
    cin >> op.income;
    cin.ignore();

    for(int i = 0;i < 12;i++){
        elem[i].clear();
        while(elem[i].size() < 12){
            elem[i] += ' ';
        }
    }

    for(int i = 0; i < 12; i++) {
        string line;
        cin >> line;
        for(int j = 0;j < 12;j++){
            elem[j][i] = line[j];
        }
    }

    cin >> dump;

    for(int i = 0; i < dump; i++) {
        int owner;
        int type;
        int x,y;
        cin >> owner >> type >> x >> y;
        cin.ignore();
        if(owner == 0) {
            me.buildings[type].push_back({point_t(x,y)});
        }
        else {
            op.buildings[type].push_back({point_t(x,y)});
        }
    }

    cin >> dump;

    for(int i = 0; i < dump; i++) {
        int owner;
        int id;
        int lvl;
        int x,y;
        cin >> owner >> id >> lvl >> x >> y;
        cin.ignore();
        if(owner == 0) {
            me.units[lvl].push_back({id,point_t(x,y)});
        }
        else {
            op.units[lvl].push_back({id,point_t(x,y)});
        }
    }

}

bool taken[20][20];

void init_stuff() {
    memset(taken,0,sizeof(taken));
    memset(occupied,0,sizeof(occupied));
    memset(build_already,0,sizeof(build_already));
    for(auto it:me.buildings) {
        for(auto it2:it) {
            build_already[it2.pos.x][it2.pos.y] = true;
            occupied[it2.pos.x][it2.pos.y] = true;
        }
    }
    
    for(auto it:me.units) {
        for(auto it2:it) {
            occupied[it2.pos.x][it2.pos.y] = true;
        }
    }
    
    for(auto it:op.buildings) {
        for(auto it2:it) {
            occupied[it2.pos.x][it2.pos.y] = true;
        }
    }
    
    for(auto it:op.units) {
        for(auto it2:it) {
            occupied[it2.pos.x][it2.pos.y] = true;
        }
    }
}

bool need = false;

void build_mine(player_state_t &me,point_t pos) {
    cout << "BUILD MINE " << pos.x << " " << pos.y << ";";
    me.gold -= (20 + 4 * me.buildings[1].size());
    me.buildings[1].push_back({pos});
    build_already[pos.x][pos.y] = true;
    occupied[pos.x][pos.y] = true;
    need = true;
}

void move(player_state_t &me,unit_t &it,const point_t &to) {
    cout << "MOVE " << it.id << " " << to.x << " " << to.y << ";";
    for(auto &it3:me.units) {
        for(auto &it2:it3) {
            if(it.id == it2.id) {
                it2.pos = to;
                break;
            }
        }
    }
    need = true;
}

const int cost[] = {0,10,20,30};
const int maintain[] = {0,1,4,20};


///TODO 
///for train_position get the closest to the enemy base possible,except maybe for skrimrishers
///add maybe some rand to it to

point_t get_train_pos(){
    for(int i = 11;i >= 0;i--){
        for(int j = 11;j >= 0;j--){
            if(elem[i][j] != 'O'){
                continue;
            }
            if(occupied[i][j] == false){
                return point_t(i,j);
            }
            if(i < 11 && elem[i + 1][j] != '#' && occupied[i + 1][j] == false){
                return point_t(i + 1,j);
            }
            if(j < 11 && elem[i][j + 1] != '#' && occupied[i][j + 1] == false){
                return point_t(i,j + 1);
            }
        }
    }
    return point_t(5,5);
}

void train(player_state_t &me,int lvl,point_t pos) {///TODO
    cout << "TRAIN " << lvl << " " << pos.x << " " << pos.y << ";";
    me.gold -= cost[lvl];
    me.income -= maintain[lvl];
    occupied[pos.x][pos.y] = true;
    need = true;
}

void build_stuff() {
    ///build mines if possible

    for(auto it:mine_spots) {
        if(tolower(elem[it.x][it.y]) == 'o' && build_already[it.x][it.y] == false && me.gold >= 20 + 4 * me.buildings[1].size()) {
            build_mine(me,it);
        }
    }
}

const int target_skirmrish = 6;

void train_troops() {
    ///maybe wait for mines?

    if(me.units[1].size() < target_skirmrish){
        train(me,1,get_train_pos());
    }
    else{
        for(int k = 3;k > 1;k--){
            if(me.income > maintain[k]){
                train(me,k,get_train_pos());
            }
        }
    }

}

void move_troops() {
    ///skirmrish
    sort(me.units[1].begin(),me.units[1].end(),[&](unit_t &a,unit_t &b){return a.pos.x + a.pos.y > b.pos.x + b.pos.y;});
    for(auto it:me.units[1]) {
        point_t best(20,20);

        for(int i = 0;i < 12;i++){
            for(int j = 0;j < 12;j++){
                if(taken[i][j] == false && elem[i][j] != 'O' && elem[i][j] != '#'){
                    if(best.man_dist(it.pos) > point_t(i,j).man_dist(it.pos)){
                        best = point_t(i,j);
                    }
                }
            }
        }
        taken[best.x][best.y] = true;
        move(me,it,best);
    }

    ///attack

    sort(me.units[2].begin(),me.units[2].end(),[&](unit_t &a,unit_t &b){return a.pos.x + a.pos.y > b.pos.x + b.pos.y;});
    for(auto it:me.units[2]){
        move(me,it,op.buildings[0][0].pos); 
    }
    
    sort(me.units[3].begin(),me.units[3].end(),[&](unit_t &a,unit_t &b){return a.pos.x + a.pos.y > b.pos.x + b.pos.y;});
    for(auto it:me.units[3]){
        move(me,it,op.buildings[0][0].pos);
    }
}

void flush_if_necessary() {
    if(need == true) {
        cout << endl;
        need = false;
    }
}

void play() {
    while(true) {
        read_states();
        init_stuff();
        build_stuff();
        train_troops();
        move_troops();
        flush_if_necessary();
    }
}

int main() {

    init_read();
    play();

    return 0;
}
