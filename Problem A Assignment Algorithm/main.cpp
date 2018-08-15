#include <iostream>
#include <algorithm>

using namespace std;

string S[55];
int fr[2];
int R,K;

int init_airplane(){
    for(int i = 1;i <= R + 3;i++){
        for(int j = 1;j <= 11;j++){
            if(j <= 5){
                fr[0] += (S[i][j] == '#');
            }
            else if(j >= 7){
                fr[1] += (S[i][j] == '#');
            }
        }
    }
}

int free_seats(int row){
    int ans = 0;
    for(int i = 1;i <= 11;i++){
        ans += (S[row][i] == '-');
    }
    return ans;
}

int minDistToExit(int row){
    return min(min(row - 1,abs(row - R - 3)),abs(row - R / 2 - 2));
}

vector<int> ExtractRows(){
    vector<int> ans;
    if(free_seats(2)){
        ans.push_back(2);
    }
    if(free_seats(3 + R / 2)){
        ans.push_back(3 + R / 2);
    }
    if(!ans.empty()){
        return ans;
    }

    for(int i = 1;i <= R + 3;i++){
        ans.push_back(i);
    }
    return ans;
}

int select_row(vector<int> rows){
    int best_row = 1;
    for(auto it:rows){
        if(free_seats(best_row) < free_seats(it)){
            best_row = it;
        }
        else if(free_seats(best_row) == free_seats(it) && minDistToExit(best_row) > minDistToExit(it)){
            best_row = it;
        }
    }
    return best_row;
}

int select_seat(int row){
    if(S[row][5] == '-' || S[row][7] == '-'){
        if(S[row][5] == '-' && S[row][7] == '-'){
            if(fr[0] <= fr[1]){
                return 5;
            }
            return 7;
        }
        return (S[row][5] == '-' ? 5:7);
    }
    else if(S[row][3] == '-' || S[row][9] == '-'){
       if(S[row][3] == '-' && S[row][9] == '-'){
            if(fr[0] <= fr[1]){
                return 3;
            }
            return 9;
        }
        return (S[row][3] == '-' ? 3:9);
    }
    else if(S[row][1] == '-' || S[row][11] == '-'){
        if(S[row][1] == '-' && S[row][11] == '-'){
            if(fr[0] <= fr[1]){
                return 1;
            }
            return 11;
        }
        return (S[row][1] == '-' ? 1:11);
    }
    else if(S[row][6] == '-'){
        return 6;
    }
    else{
        if(S[row][2] == '-' && S[row][10] == '-'){
            if(fr[0] <= fr[1]){
                return 2;
            }
            return 10;
        }
        return (S[row][2] == '-' ? 2:10);
    }
}

int main(){
    cin >> R >> K;

    for(int i = 1;i <= R + 3;i++){
        cin >> S[i];
        S[i] = " " + S[i];
    }

    init_airplane();

    for(int i = 1;i <= K;i++){
        int row = select_row(ExtractRows());
        int seat = select_seat(row);
        S[row][seat] = 'a' + i - 1;
        if(seat <= 5){
            fr[0]++;
        }
        else if(seat >= 7){
            fr[1]++;
        }
    }

    for(int i = 1;i <= R + 3;i++){
        cout << S[i].substr(1) << "\n";
    }

    return 0;
}
