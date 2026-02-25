#include <iostream>
#include <string>
#include <vector>
using namespace std;
class BankAccount{
  public:
    string name;
    int account_id;
    bool account_type;//checkings or savings
    void deposit(int kwota){
      operation.push_back("D " + to_string(kwota) + '\n');
      balance += kwota;
    }
    void withdraw(int kwota){
      operation.push_back("WD " + to_string(kwota)+ '\n');
      balance -= kwota;
  
    }
    void display_balance(){
      operation.push_back("CH \n");
      cout << balance << endl;
    }

    vector<string> operation;
  private:
    int balance = 0;

};

int main(){
  BankAccount pko;
  pko.deposit(50);
  pko.display_balance();
  pko.withdraw(15);
  pko.display_balance();
  for (unsigned i = 0; i < pko.operation.size(); i++)
  {
      cout << pko.operation[i];
  }
}