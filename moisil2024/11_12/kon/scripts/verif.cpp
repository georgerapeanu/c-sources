#include <bits/stdc++.h>
using namespace std;

ifstream fok;
ifstream fout;
ifstream fin;

void Msg(int pct, string msg)
{
	/// pct = un numar intre 0 si 100 reprezentand scorul pe test (valorile negative au inteles special)
    cout << pct << ' ' << msg;
    try
    {
        fok.close();
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}

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

answer_t readAnswer(const input_t& input, istream& stream) {
  answer_t answer;
  if(!(stream >> answer.value)) {
      Msg(0, "Raspuns gresit.");
  }
  for(int i = 1;i <= input.k;i++){
    int node;
    if(!(stream >> node)) {
      Msg(0, "Raspuns gresit.");
    }
    if(node < 1 || node > input.n) {
      Msg(0, "Raspuns gresit.");
    }
    answer.kons.push_back(node);
  }

  sort(answer.kons.begin(), answer.kons.end());
  for(int i = 0;i + 1 < (int)answer.kons.size();i++) {
    if(answer.kons[i] == answer.kons[i + 1]){
      Msg(0, "Raspuns gresit.");
    }
  }
  answer.computed_value = calculate_value(input, answer);
  return answer;
}



int main(int argc, char* argv[])
{

	if ( argc != 4 ) {
        Msg(-2, "Eroare la evaluare: Lansare incorecta verif");
  }

	fin.open(argv[1]); // deschid fisierul in
	fout.open (argv[2]); // deschid fisierul out
	fok.open (argv[3]); // deschid fisierul ok

  if ( !fin ) {
    Msg(-2, "Eroare la evaluare: Nu exista fisierul " + string(argv[1]) );
  }
  
  if ( !fok ) {
    Msg(-2, "Eroare la evaluare: Nu exista fisierul " + string(argv[3]) );
  }

  if ( !fout ) {
    Msg(0, "Nu exista fisierul " + string(argv[2]));
  }
  
  input_t input;

  fin >> input.n;
  fin >> input.k;

  input.power = vector<int>(input.n + 1);
  input.graph = vector<vector<int>>(input.n + 1);


  for(int i = 1;i <= input.n;i++) {
    fin >> input.power[i];
  }

  for(int i = 1;i < input.n;i++) {
    int u, v;
    fin >> u >> v;
    input.graph[u].push_back(v);
    input.graph[v].push_back(u);
  }
  
  answer_t jury_answer = readAnswer(input, fok);
  answer_t contestant_answer = readAnswer(input, fout);

  if(jury_answer.computed_value > contestant_answer.computed_value) {
    Msg(0, "Eroare la testare. Te rog anunta comisia.");
  }
  
  int score = 0;
  
  if(jury_answer.computed_value == contestant_answer.value){
    score += 50;
    if(contestant_answer.value == contestant_answer.computed_value) {
      score += 50;
    }
  }
  
  if(score == 100) {
    Msg(score, "Corect.");
  } else if (score > 0) {
    Msg(score, "Costul este corect, dar selectia afisata nu il obtine.");
  } else {
    Msg(score, "Raspuns gresit.");
  }


  return 0;
}
