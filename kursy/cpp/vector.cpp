#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<char> nazwa = {'a','b','c'};
  nazwa.push_back('g');
  for (unsigned i = 0; i < nazwa.size(); i++)
  {
    cout << nazwa[i];
  }
  nazwa.pop_back();
}