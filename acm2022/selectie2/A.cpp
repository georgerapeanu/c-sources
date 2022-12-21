#include <bits/stdc++.h>

using namespace std;

int main(){

  string line;
  getline(cin ,line);

  vector<string> words;

  string current_word = "";

  for(auto &it:line){
    if(it == '.' || it == ',' || it == ' '){
      if(current_word != ""){
        words.push_back(current_word);
      }
      current_word = "";
      continue;
    }
    current_word += it;
  }
      
  if(current_word != ""){
    words.push_back(current_word);
  }

  map<string, int> position; 

  for(int i = 0;i < (int)words.size();i++){
    position[words[i]] = i;
  }

  vector<vector<int> > graph(words.size());
  vector<vector<int> > graphT(words.size());
  vector<bool> preceed(words.size());
  vector<bool> succeed(words.size());

  bool preceeded = false;
  string last_word = "";

  for(auto &it:line){
    if(it == '.' || it == ',' || it == ' '){///end of the word
      if(current_word != ""){
        last_word = current_word;
        if(preceeded){
          preceed[position[current_word]] = true;
        }
      }

      if(it == ','){
        preceeded = true;
        if(last_word != ""){
          succeed[position[last_word]] = true; 
        }
      } else if(current_word != ""){
        preceeded = false;
      }

      if(it == '.'){
        last_word = '.';
      }

      current_word = "";
      continue;
    }
    current_word += it;
  }

  return 0;
}
