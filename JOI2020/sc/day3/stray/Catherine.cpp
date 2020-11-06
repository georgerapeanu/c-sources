#include "Catherine.h"
//#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int _a,_b;

void Init(int A, int B) {
    _a = min(A,3);
    _b = B;
}

int lst = -1;
bool found_direction = false;

vector<vector<int> > good_secvs = 
{
    {0,1,0,0,1},
    {1,0,0,1,1},
    {0,0,1,1,0},
    {0,1,1,0,1},
    {1,1,0,1,0},
    {1,0,1,0,0}
};

vector<int> curr_secv;

int Move(vector<int> y) {
    if(_a == 3){
        if(y[0] == 0){
            if(y[1] == 0){
                return 2;
            }
            else{
                return 1;
            }
        }
        else if(y[1] == 0){
            if(y[2] == 0){
                return 0;
            }
            else{
                return 2;
            }
        }
        else{
            if(y[0] == 0){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
   // printf("%d %d\n",y[0],y[1]);
    
    if(found_direction){
        if(y[0] == 0){
        //    printf("deb1 %d\n",1);
            return lst = 1;
        }
        if(y[1] == 0){
     //       printf("deb1 %d\n",0);
            return lst = 0;   
        }

        if(y[1] != 1){
       //     printf("deb1 %d\n",0);
            return lst = 0;
        }

        if(y[0] != 1){
         //   printf("deb1 %d\n",1);
            return lst = 1;
        }

        //printf("deb1 %d\n",1 - lst);
        return lst = 1 - lst;
    }

    if((lst != -1) + y[0] + y[1] == 1){
        found_direction = true;
        if(lst != -1){
          //  printf("deb1.5 %d\n",-1);
            return -1;
        }
       // printf("deb2 %d\n",(y[0] == 1 ? 0:1));
        return lst = (y[0] == 1 ? 0:1);
    }

    if(y[0] + y[1] + (lst != -1) > 2){
        found_direction = true;
        if(y[0] == 0){
            if(lst == -1){
         //       printf("deb3 %d\n",1);
                return lst = 1;
            }
            else{
         //       printf("deb4 %d\n",-1);
                return -1;
            }
        }
        if(y[1] == 0){
            if(lst == -1){
         //       printf("deb5 %d\n",0);
                return lst = 0;
            }
            else{
         //       printf("deb6 %d\n",-1);
                return -1;
            }
        }
       // printf("deb7 %d\n",(((lst == 0) + y[0]) < ((lst == 1) + y[1]) ? 0:1));
        return lst = (((lst == 0) + y[0]) < ((lst == 1) + y[1]) ? 0:1);
    }

    if(lst == -1){
        if(y[0] == 2){
            lst = 0;
            curr_secv.push_back(0);
            curr_secv.push_back(0);
         //   printf("deb8 %d\n",0);
            return 0;
        }
        else if(y[0] == 1){
            lst = 0;
            curr_secv.push_back(1);
            curr_secv.push_back(0);
         //   printf("deb9 %d\n",0);
            return 0;
        }
        else{
            lst = 1;
            curr_secv.push_back(1);
            curr_secv.push_back(1);
         //   printf("deb10 %d\n",1);
            return 1;
        }
    }
    else{
        if(y[0] == 1){
            curr_secv.push_back(lst = 0);
        }
        else{
            curr_secv.push_back(lst = 1);
        }
        if(curr_secv.size() == 5){
            bool found = false;
            for(auto it:good_secvs){
                bool tmp = true;
                for(int i = 0;i < 5;i++){
                    tmp &= (it[i] == curr_secv[i]);
                }
                if(tmp){
                    found = true;
                    break;
                }
            }
            if(found == true){
                found_direction = true;
           //     printf("deb11 %d\n",-1);
                return -1;
            }
            else{
                found_direction = true;
           //     printf("deb12 %d\n",lst);
                return lst;
            }
        }
        else{
          //  printf("deb13 %d\n",lst);
            return lst;
        }
    }

    //printf("wtf\n");
    return -10;
}
