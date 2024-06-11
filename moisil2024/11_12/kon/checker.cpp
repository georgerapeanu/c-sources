/* 
 * TODO also not sure what happens if jury output is corrupted
 *
*/

#include <testlib.h>
#include <vector>
#include <queue>

using namespace std;

const long long ANSWER_MIN = 0;
const long long ANSWER_MAX = 1000000000000000000LL;

struct input_t{
  int n, k;
  vector<int> power;
  vector<vector<int> > graph;
};

struct answer_t{
  long long value;
  long long computed_value;
  vector<int> kons;
};

long long calculate_value(const input_t& input, const answer_t &answer) {
  vector<int> visited(input.n + 1, false);

  for(auto it:answer.kons) {
    visited[it] = true;
  }
 
  long long computed_answer = 0;

  for(int nod = 1; nod <= input.n;nod++) {
    if(visited[nod]) {
      continue;
    }
    long long local_answer = 0;
    queue<int> local_queue;
    local_queue.push(nod);
    visited[nod] = true;
    
    while(!local_queue.empty()) { 
      int current_node = local_queue.front();
      local_answer += input.power[current_node];
      local_queue.pop();
      for(auto it: input.graph[current_node]){
        if(!visited[it]) {
          local_queue.push(it);
          visited[it] = true;
        }
      }
    }
    computed_answer = max(computed_answer, local_answer);
  }
  return computed_answer;
}

answer_t readAnswer(const input_t& input, InStream& stream) {
  answer_t answer;
  answer.value = stream.readLong(ANSWER_MIN, ANSWER_MAX, "the minimum final cost");
  for(int i = 1;i <= input.k;i++){
    int node = stream.readInt(1, input.n, format("node %d", i));
    answer.kons.push_back(node);
  }
  sort(answer.kons.begin(), answer.kons.end());
  for(int i = 0;i + 1 < (int)answer.kons.size();i++) {
    if(answer.kons[i] == answer.kons[i + 1]){
      stream.quitf(_wa, "The same node was chosen two times");
    }
  }
  answer.computed_value = calculate_value(input, answer);
  return answer;
}

int main(int argc, char** argv) {
  registerTestlibCmd(argc, argv);

  input_t input;

  input.n = inf.readInt();
  input.k = inf.readInt();

  input.power = vector<int>(input.n + 1);
  input.graph = vector<vector<int>>(input.n + 1);


  for(int i = 1;i <= input.n;i++) {
    input.power[i] = inf.readInt();
  }

  for(int i = 1;i < input.n;i++) {
    int u = inf.readInt();
    int v = inf.readInt();
    input.graph[u].push_back(v);
    input.graph[v].push_back(u);
  }
  
  answer_t jury_answer = readAnswer(input, ans);
  answer_t contestant_answer = readAnswer(input, ouf);

  if(jury_answer.computed_value != jury_answer.value) {
    quitf(_fail, "Jury computed value %lld is different from jury output value %lld", jury_answer.computed_value, jury_answer.value);
  }
  if(jury_answer.computed_value > contestant_answer.computed_value) {
    quitf(_fail, "Jury computed value %lld is worse than contestant computed value %lld", jury_answer.computed_value, contestant_answer.computed_value);
  }
  
  int score = 0;
  
  if(jury_answer.computed_value == contestant_answer.value){
    score += 50;
    if(contestant_answer.value == contestant_answer.computed_value) {
      score += 50;
    }
  }

  if(score == 0) {
    quitf(_wa, "Wrong answer");
  }

  if(score > 0){
    quitp(_pc(score - 16), "Partially correct");
  }
  quitf(_ok, "Ok");

  return 0;
}
