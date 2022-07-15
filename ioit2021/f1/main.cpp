#include <bits/stdc++.h>

using namespace std;

class Car{
public:
  int a, b, c;
  int id;


  Car(int a, int b, int c, int id){
    this->a = a;
    this->b = b;
    this->c = c;
    this->id = id;
  }

  Car operator - (const Car &other)const{
    return Car(this->a - other.a, this->b - other.b, this->c - other.c, -1);
  }

  vector<long double> get_roots(){
    //printf("debug plm %d %d %d\n",a,b,c);
    long long delta = 1LL * this->b * this->b - 4LL * this->a * this->c;
    if(delta < 0){
      //printf("none\n");
      return {};
    }
    long double sdelta = sqrt((long double)delta);
    if(delta == 0){
      //printf("%Lf\n", ((long double)-this->b) / (2 * this->a));
      return {((long double)-this->b) / (2 * this->a)}; 
    }
    //printf("%Lf %Lf\n", ((long double)-this->b - sdelta) / (2 * this->a), ((long double)-this->b + sdelta) / (2 * this->a));
    return {((long double)-this->b - sdelta) / (2 * this->a), ((long double)-this->b + sdelta) / (2 * this->a)};
  }

  long double operator () (long double x){
    return this->a * x * x + this->b * x + this->c;
  }

  bool operator < (const Car &other)const{
    return id < other.id;
  }
};

const long double eps = 1e-7;
vector<long double> get_swaps(Car a, Car b){
  if(a.id > b.id){
    swap(a, b);
  }

  Car diff = a - b;
  if(diff.a != 0){
    vector<long double> roots = diff.get_roots();
    if(roots.size() == 0){
      return {};
    }else if(roots.size() == 1){
      if(diff(roots[0] - eps) < 0){
        return {roots[0] - eps, roots[0] + eps};
      }
      return {};
    }else{
      vector<long double> ans;
      if(diff(roots[0] - eps) < 0){
        ans.push_back(roots[0] - eps);
      }else{
        ans.push_back(roots[0] + eps);
      }
      
      if(diff(roots[1] + eps) < 0){
        ans.push_back(roots[1] + eps);
      }else{
        ans.push_back(roots[1] - eps);
      }
      return ans;
    }
  }else if(diff.b != 0){
    long double where = (((long double)-diff.c) / diff.b);
    if(diff(where - eps) < 0){
      return {where - eps};
    }else{
      return {where + eps};
    }
  }else{
    return {};
  }
}

class OrderManager{
  int n;
  vector<Car> order;
  vector<int> where;
  int last_swap;
  unordered_map<int,int> available_swaps;

  int swap_to_int(int x, int y){
    if(x > y){
      swap(x, y);
    }
    return x * n + y;
  }

  pair<int,int> int_to_swap(int swap){
    return {swap / n, swap % n};
  }

  void order_at(long double x){
    this->last_swap = 0;
    vector<pair<long double, Car> > local_order;

    for(int i = 0;i < n;i++){
      local_order.push_back({order[i](x), order[i]});
    }
    sort(local_order.begin(), local_order.end());
    for(int i = 0;i < n;i++){
      order[i] = local_order[i].second;
      where[local_order[i].second.id] = i;
    }
  }

  void do_swap(int __swap){
    if(available_swaps.count(__swap) == 0){
      return;
    }
    
    pair<int,int> params = this->int_to_swap(__swap);

    if(where[params.first] - where[params.second] != 1 && where[params.second] - where[params.first] != 1){
      return ;
    }

    //printf("done swap %d %d\n",params.first,params.second);

    available_swaps.erase(__swap);
    swap(order[where[params.first]], order[where[params.second]]);
    swap(where[params.first], where[params.second]);
    if(where[params.first] - 1 >= 0){
      do_swap(swap_to_int(params.first, order[where[params.first] - 1].id));
    }
    
    if(where[params.first] + 1 < n){
      do_swap(swap_to_int(params.first, order[where[params.first] + 1].id));
    }
    
    if(where[params.second] - 1 >= 0){
      do_swap(swap_to_int(params.second, order[where[params.second] - 1].id));
    }
    
    if(where[params.second] + 1 < n){
      do_swap(swap_to_int(params.second, order[where[params.second] + 1].id));
    }
  }

  public:

  OrderManager(const vector<Car> &cars){
    this->n = cars.size();
    this->order = cars;
    for(auto &it:order){
      it.a *= -1;
      it.b *= -1;
      it.c *= -1;
    }
    this->last_swap = -1e9;
    this->where = vector<int>(n, 0);
    this->available_swaps = {};
    this->order_at(0);
    //for(auto it:order){
    //  printf("%d ",it.id);
    //}
    //printf("\n");
  }

  void add_swap(long double t, int i, int j){
    if(t < this->last_swap){
      return ;
    }
    //printf("added swap at %.8f %d %d\n",(double)t, i, j);
    this->last_swap = t;
    this->available_swaps[swap_to_int(i, j)] = 1;
    this->do_swap(swap_to_int(i, j));
  }

  Car get(int pos){
    return order[pos];
  }
};

int main(){

  int n;
  vector<Car> cars;

  scanf("%d",&n);

  cars = vector<Car>(n, Car(0,0,0,0));

  int last_id = 0;
  for(auto &it:cars){
    scanf("%d %d %d", &it.a, &it.b, &it.c);
    it.id = last_id++;
  }

  OrderManager manager(cars);
  vector<pair<long double, pair<int, int> > > swaps;

  for(int i = 0;i < n;i++){
    for(int j = 0;j < i;j++){
      vector<long double> tmp = get_swaps(cars[i], cars[j]);
      for(auto it:tmp){
        swaps.push_back({it, {i, j}});
        //printf("between %d and %d there will be a swap at %Lf\n", i, j, it);
      }
    }
  }


  int q;
  scanf("%d", &q);

  for(int i = 0;i < q;i++){
    int t, p;
    scanf("%d %d", &p, &t);
    swaps.push_back({t, {-p, -i - 1}});
  }

  sort(swaps.begin(), swaps.end());
  vector<int> ans(q, 0);

  for(auto it:swaps){
    if(it.second.first >= 0 && it.second.second >= 0){
      manager.add_swap(it.first, it.second.first, it.second.second);
    }else{
      ans[-it.second.second - 1] = manager.get(-it.second.first - 1).id + 1;
//      printf("query for %d at %Lf is %d\n", -it.second.first, it.first, manager.get(-it.second.first - 1).id + 1);
    }
  }

  for(auto it:ans){
    printf("%d\n", it);
  }

  return 0;
}
