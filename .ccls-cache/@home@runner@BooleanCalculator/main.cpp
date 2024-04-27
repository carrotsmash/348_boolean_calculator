#include <iostream>
#include <string>
#include <vector>
using namespace std;

char NOT(char a) { return (a == 'T') ? 'F' : 'T'; } //symbol: !

char AND(char a, char b) { return ((a == 'T') && (b == 'T')) ? 'T' : 'F'; } //symbol: &

char NAND(char a, char b) { return NOT(AND(a, b)); } //symbol: @

char XOR(char a, char b) { return (a != b) ? 'T' : 'F'; } //symbol: $

char OR(char a, char b) { return ((a == 'T') || (b == 'T')) ? 'T' : 'F'; } //symbol: |

vector<char> parse(vector<char> v){ //parse vector and outputs T or F for logic gates
  
  for(int i = 0; i < v.size(); i++){ //NOT gate
    if(v[i] == '!'){
      v[i+1] = NOT(v[i+1]);
      v.erase(v.begin() + i);
    }
  }

  for(int i = 0; i < v.size(); i++){ //NAND gate
    if(v[i] == '@'){
      v[i] = NAND(v[i-1], v[i+1]); //grabs chars around gate symbol '@'
      v.erase(v.begin() + i - 1); //make sure to erase correct spots, first erase the character behind v[i] that we have changed
      v.erase(v.begin() + i); //next erase i since we want to erase the character after v[i] which is now v[i-1]
    }
  }

  for(int i = 0; i < v.size(); i++){ //AND gate
    if(v[i] == '&'){
      v[i] = AND(v[i-1], v[i+1]);
      v.erase(v.begin() + i -1);
      v.erase(v.begin() + i);
    }
  }

  for(int i = 0; i < v.size(); i++){ //XOR gate
    if(v[i] == '$'){
      v[i] = XOR(v[i-1], v[i+1]);
      v.erase(v.begin() + i -1);
      v.erase(v.begin() + i);
    }
  }

  for(int i = 0; i < v.size(); i++){ //OR gate
    if(v[i] == '|'){
      v[i] = OR(v[i-1], v[i+1]);
      v.erase(v.begin() + i -1);
      v.erase(v.begin() + i);
    }
  }
  
  return v;
}

vector<char> grouping(vector<char> v){ //grouping parentheses will send a temp vector to parse function and output T or F back into the original vector, erasing all values besides the new T or F, if no grouping parentheses exists, the whole vector will be send to parse function and returned as T or F
  int idx_closing = v.size()-1; //track right hand parenthesis
  int idx_opening = 0; //track left hand parenthesis
  int contains_closing = 0; //track if there is a closing parenthesis
  int contains_opening = 0; //track if there is an opening parenthesis

  for(int i = 0; i < v.size(); i++){ //grab index of first closing parenthesis
    if(v[i] == ')'){
      idx_closing = i;
      contains_closing = 1;
      break;
    }
  }
  
  for(int i = idx_closing; i >= 0; i--){ //grab index of opening parenthesis tied to the above closing parenthesis
    if(v[i] == '('){
      idx_opening = i;
      contains_opening = 1;
      break;
    }
  }
  
  vector<char> a; //temp vector for grouping parentheses
  if(contains_opening && contains_closing){ //check to make sure a valid group exists
    for(int i = idx_opening+1; i < idx_closing; i++){ //push back all values between the opening and closing parenthesis
      a.push_back(v[i]);
    }
    for(int i = idx_opening; i <= idx_closing; i++){ //erase all values between the opening and closing parenthesis including the parentheses themselves
      v.erase(v.begin() + idx_opening);
    }
    a = parse(a); //calculate T or F for temp vector
    v.insert(v.begin() + idx_opening, a[0]); //insert the value of T or F into the original vector
  }
  else{ //if there are no valid parentheses, then we calculate the value of the entire vector
    v = parse(v);
  }
  
  return v;
}

int main() {
  string s; //store line in string and convert string to vector of chars without the spaces
  printf("Expression: ");
  string line;
  getline(cin, line);
  vector<char> v;
  for(int i = 0; i < line.size(); i++){ //convert string to vector of chars without the spaces
    if(line[i] != ' '){
      v.push_back(line[i]);
    }
  }

  while(v.size() > 1){ //if we are not at the final value T or F, continue to parse the vector
    v = grouping(v);
  }
  
  for(const char& c: v){//print vector of chars to check if it is correct
    cout << "Evaluation: ";
    if(c == 'T'){
      cout << "True";
    }
    else cout << "False";
  }
  return 0;
}