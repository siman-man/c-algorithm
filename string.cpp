#include <cassert>
#include <iostream>
#include <string>

using namespace std;

string rotate(string str) {
  return str.substr(1) + str[0];
}

int main() {
  string str = "tokyo";
  assert(rotate(str) == "okyot");

  return 0;
}

