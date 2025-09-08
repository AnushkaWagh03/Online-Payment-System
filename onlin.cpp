#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Wallet;       
class Transaction; 

class User {
private:
    string id;
    string name;
    string password;
    string phone;

protected:
    Wallet* wallet;                        
    vector<Transaction*> transactions;    

public:
    User(string id, string name, string password, string phone, double balance);

    string getId();
    string getPhone();
    string getName();
    bool checkPassword(string pass);
    void showTransaction();
    double getBalance();
};

class Customer {

};

class Merchant {

};

class Wallet {
    

};

class Payment {
    
};

class Transaction {
    
public:
    void display() {
        cout << "Transaction details\n";
    }
};

class PaymentFlow {
   
};

class FileHandler {
   
};



User::User(string id, string name, string password, string phone, double balance) {
    this->id = id;
    this->name = name;
    this->password = password;
    this->phone = phone;
    this->wallet = new Wallet();   
    
}

string User::getId() {
    return id;
}

string User::getPhone() {
    return phone;
}

string User::getName() {
    return name;
}

bool User::checkPassword(string pass) {
    return this->password == pass;
}

void User::showTransaction() {
   
}





int main() {
   
    return 0;
}
