#include <bits/stdc++.h>
using namespace std;

bool is_num_char(char token) {
  string num_chars = "0123456789";
  return num_chars.find(token) != string::npos;
}

class Calculator {
  public:
    Calculator(vector<char> code, int pos) {
      this->code = code;
      this->pos = pos;
    }
    
    double calculate() {
      return this->expr();
    }
  private:
    vector<char> code;
    int pos;
    
    char get_token(int diff) {
      return this->code[this->pos + diff];
    }

    double expr() {
      double value = this->term();
      while (true) {
        char token = this->get_token(1);
        if (token == '+') {
          this->pos += 2;
          value += this->term();
        }
        else if (token == '-') {
          this->pos += 2;
          value += this->term();
        }
        else {
          break;
        }
      }
      return value;
    }

    double term() {
      double value = this->factor();
      while (true) {
        char token = this->get_token(1);
        if (token == '*') {
          this->pos += 2;
          value *= this->factor();
        }
        else if (token == '/') {
          this->pos += 2;
          value /= this->factor();
        }
        else {
          break;
        }
      }
      return value;
    }

    double factor() {
      char token = this->get_token(0);
      if (is_num_char(token)) {
        vector<char> num_chars;
        while (true) {
          token = this->get_token(0);
          if (is_num_char(token)) {
            num_chars.push_back(token);
            this->pos += 1;
          }
          else {
            this->pos -= 1;
            break;
          }
        }
        string number_str(num_chars.begin(), num_chars.end());
        return stoi(number_str);
      }
      else if (token == '(') {
        this->pos +=1;
        double ans = this->expr();
        this->pos +=1;
        return ans;
      }
      else {
        cout << "Syntax Error" << endl;
        exit(1);
      }
    }
};

int main() {
  cout << "type \"quit\" enter to exit program" << endl;
  string input;
  while (true) {
    cout << "> ";
    cin >> input;
    if (input == "quit") { break; }
    vector<char> code(input.begin(), input.end());
    Calculator calc = Calculator(code, 0);
    cout << " = " << calc.calculate() << endl;
  }
}
