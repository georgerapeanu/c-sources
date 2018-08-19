#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

class LinearFunction{
public:
	long long a;
	long long b;

	LinearFunction(){
		a = b = 0;
	}

	LinearFunction(long long a, long long b){
		this->a = a;
		this->b = b;
	}

    LinearFunction operator + (const LinearFunction &other)const{
		return LinearFunction(a + other.a,b + other.b);
	}

	LinearFunction operator - (const LinearFunction &other)const{
		return LinearFunction(a - other.a,b - other.b);
	}

	long long operator () (long long x)const{
		return a * x + b;
	}

	bool operator < (const LinearFunction &other)const{
        if(a != other.a){
            return a < other.a;
        }
        return b < other.b;
	}
};

///max convex hull
class ConvexHull{
private:
    vector<LinearFunction> fun;
public:

    DynamicConvexHull(){
        fun.clear();
    }

	void add(LinearFunction f){
        fun.push_back(f);
	}

	void build(){
        sort(fun.begin(),fun.end());
        int ind = 0;
        for(int i = 1; i < (int)fun.size();i++){
            while(ind >= 0 && fun[ind].a == fun[i].a && fun[ind].b <= fun[i].b){
                ind--;
            }

            while(ind >= 1 && (fun[ind].b - fun[i].b) * (fun[ind].a - fun[ind - 1].a) <= (fun[ind - 1].b - fun[ind].b) * (fun[i].a - fun[ind].a)){
                ind--;
            }

            fun[++ind] = fun[i];
        }
        fun.resize(ind + 1);
	}

	long long operator () (long long x){

	    if(fun.empty()){
            return 0;
	    }

        int st = 0,dr = (int)fun.size() - 1;
        while(dr - st > 1){
            int mid = (st + dr) / 2;
            if(fun[mid].b - fun[mid + 1].b <= x * (fun[mid + 1].a - fun[mid].a)){
                st = mid;
            }
            else{
                dr = mid;
            }
        }

        if(st + 1 < (int)fun.size() && fun[st].b - fun[st + 1].b <= x * (fun[st + 1].a - fun[st].a)){
           st++;
        }

        return fun[st](x);
	}

    void merge_with(const ConvexHull &other,bool rebuild){
        for(auto it:other.fun){
            this->add(it);
        }
        if(rebuild){
            this->build();
        }
    }

    int sz(){
        return fun.size();
    }

    void compose(const ConvexHull &other,bool rebuild){
        ConvexHull ans;
        int i = 0;
        int j = 0;
        while(i < (int)fun.size() - 1 || j < (int)other.fun.size() - 1){
            ans.add(fun[i] + other.fun[j]);

            if(i == (int)fun.size() - 1){
                j++;
                continue;
            }

            if(j == (int)other.fun.size() - 1){
                i++;
                continue;
            }

            if((fun[i].b - fun[i + 1].b) * (other.fun[j + 1].a - other.fun[j].a) <= (other.fun[j].b - other.fun[j + 1].b) *  (fun[i + 1].a - fun[i].a)){
                i++;
            }
            else{
                j++;
            }
        }
        ans.add(fun[i] + other.fun[j]);
        if(rebuild){
            ans.build();
        }
        *this = ans;
    }

    void compose(LinearFunction &a){
        for(auto &it:fun){
            it = it + a;
        }
    }

    void write(int st,int dr){///[st,dr)
        int id = 0;
        for(int i = st;i < dr;i++){
            while(id != (int)fun.size() - 1 && fun[id].b - fun[id + 1].b <= i * (fun[id + 1].a - fun[id].a)){
                id++;
            }
            fprintf(stdout,"%I64d ",fun[id](i));
        }
    }
};