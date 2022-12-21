#include <bits/stdc++.h>

using namespace std;

const int LIM = 100 * 100 * 3 + 50;

char sounds[LIM];
char line[LIM];

int main(){

  int t;

  scanf("%d\n", &t);

  while(t--){
    fgets(sounds, LIM, stdin);
    std::vector<string> words;

    string current_word = "";

    for(int i = 0;sounds[i] != '\0' && sounds[i] != '\n';i++){
      if(sounds[i] == ' '){
        if(current_word != ""){
          words.push_back(current_word);
        }
        current_word = "";
        continue;
      }
      current_word += sounds[i];
    }
    if(current_word != ""){
      words.push_back(current_word);
    }

    map<string,int> exists;

    while(true){
      fgets(line, LIM, stdin);
      if(strcmp(line, "what does the fox say?") == 0 || strcmp(line, "what does the fox say?\n") == 0){
        break;
      }

      std::string sound = "";
      for(int i = 0;line[i] != '\0' && line[i] != '\n';i++){
        if(line[i] == ' '){
          sound = "";
          continue;
        }
        sound += line[i];
      }
      exists[sound] = 1;
    }
    for(auto it:words){
      if(!exists[it]){
        printf("%s ", it.c_str());
      }
    }
  }
    
  return 0;
}
