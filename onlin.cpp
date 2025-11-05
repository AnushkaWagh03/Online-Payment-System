#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <map>
#include <regex>
#include <limits>
#include <exception>
#include <cctype>

using namespace std;

class User {
public:
    string userID, name, password, email;
    string phone; 
    string role, securityQuestion, securityAnswer;
    bool logIn;
    // default constructor
    User(): logIn(false), phone("") { }
    // Parametrised constructor 
    User(string uid, string nm, string pwd, string mail, string ph) {
        userID = uid;
        name = nm;
        password = pwd;
        email = mail;
        phone = ph;
        role = "Customer";
        logIn = false;
    }
    ~User() {
        
    }
 bool isValidEmail(string email) {
    int atPos = email.find('@');
    int dotPos = email.find('.', atPos + 1); 
    if (atPos > 0 && dotPos > atPos + 1 && dotPos < email.length() - 1) {
        return true;
    }
    return false;
}

static string sanitizePhone(const string &raw) {
    string digits;
    for (char c : raw) {
        if (isdigit((unsigned char)c)) digits.push_back(c);
    }
    if (digits.length() > 10) {
        return digits.substr(digits.length() - 10);
    }
    return digits;
}

bool isValidPhone(const string &ph) {
    string p = sanitizePhone(ph);
    if (p.length() != 10)
        return false;
    if (p[0] < '6' || p[0] > '9')
        return false;

    if (p == "0000000000" || p == "1111111111" || p == "2222222222" ||
        p == "3333333333" || p == "4444444444" || p == "5555555555" ||
        p == "6666666666" || p == "7777777777" || p == "8888888888" ||
        p == "9999999999")
        return false;
 bool allZeroAfterFirst = true;
    for (size_t i = 1; i < p.size(); ++i) {
        if (p[i] != '0') {
            allZeroAfterFirst = false;
            break;
        }
    }
    if (allZeroAfterFirst)
        return false;

    return true;
}

bool isValidName(const string &nm) {
    if (nm.empty()) return false;
    for (char c : nm) {
        if (!isalpha(c) && c != ' ')  
            return false;
    }
    return true;
}

    bool isStrongPassword(const string &pwd) {
        if(pwd.length() < 8) return false;
        bool hasUpper=false, hasLower=false, hasDigit=false, hasSpecial=false;
        for(char c : pwd){
            if(isupper((unsigned char)c)) hasUpper=true;
            else if(islower((unsigned char)c)) hasLower=true;
            else if(isdigit((unsigned char)c)) hasDigit=true;
            else hasSpecial=true;
        }
        return hasUpper && hasLower && hasDigit && hasSpecial;
    }
 bool isValidUserID(const string &uid) {
        if(uid.length() < 8) return false;
        bool hasLetter=false, hasDigit=false;
        for(char c : uid){
            if(isalpha((unsigned char)c)) hasLetter=true;
            else if(isdigit((unsigned char)c)) hasDigit=true;
        }
        return hasLetter && hasDigit;
    }
static bool exists(const string &uid) {
    ifstream fin("users.csv");
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fID;
        getline(ss, fID, ',');
        if (fID == uid) return true;
    }
    return false;
}
 static bool emailExists(const string &mail) {
    ifstream fin("users.csv");
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fID, fName, fPwd, fEmail;
        getline(ss, fID, ',');
        getline(ss, fName, ',');
        getline(ss, fPwd, ',');
        getline(ss, fEmail, ',');
        if (fEmail == mail) return true;
    }
    return false;
}

static bool phoneExists(const string &rawPh) {
    string target = sanitizePhone(rawPh);
    if (target.empty()) return false;
    ifstream fin("users.csv");
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fID, fName, fPwd, fEmail, fPhoneStr;
        getline(ss, fID, ',');
        getline(ss, fName, ',');
        getline(ss, fPwd, ',');
        getline(ss, fEmail, ',');
        getline(ss, fPhoneStr, ',');
        if (!fPhoneStr.empty()) {
            string fSan = sanitizePhone(fPhoneStr);
            if (fSan == target) return true;
        }
 }
    return false;
}


    void newRegisterUser() {
        do {
            cout << "Enter User ID: ";
            cin >> userID;
            if(!isValidUserID(userID))
                cout << "User ID must be at least 8 chars, include letters and numbers.\n";
            else if(exists(userID))
                cout << "User ID already exists! Try another.\n";
        } while(!isValidUserID(userID) || exists(userID));

       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input

while (true) {
    cout << "Enter Name (letters and spaces only): ";
    getline(cin, name);

    while (!name.empty() && isspace(name.front())) name.erase(name.begin());
    while (!name.empty() && isspace(name.back())) name.pop_back();

    if (name.empty()) {
        cout << "Name cannot be empty.\n";
        continue;
    }

    bool valid = true;
    for (char c : name) {
        if (!isalpha(static_cast<unsigned char>(c)) && c != ' ') {
            valid = false;
            break;
   }
    }

    if (!valid) {
        cout << "Invalid name! Only alphabets and spaces allowed.\n";
        continue;
    }

    break; 
}


        do {
            cout << "Enter Email: ";
            getline(cin, email);
            if(!isValidEmail(email))
                cout << "Invalid email format! Try again.\n";
            else if(emailExists(email))
                cout << "Email already exists! Try another.\n";
        } while(!isValidEmail(email) || emailExists(email));

        string rawPhone;
        do {
            cout << "Enter Phone Number (must include +91 followed by space ): ";
            getline(cin, rawPhone);
            if(!isValidPhone(rawPhone))
                cout << "Invalid phone number! Must be 10 digits and start with 6-9.\n";
            else if(phoneExists(rawPhone))
                cout << "Phone number already exists! Try another.\n";
        } while(!isValidPhone(rawPhone) || phoneExists(rawPhone));
        
        phone = sanitizePhone(rawPhone);









 


class Customer : public User {
private:
    float balance;

public:
    Customer() : User("C001","Defaultcustomer","un@gmail.com",0,"","Customer") {
    balance = 0.0;
}

Customer(string ID, string name, string email, long long phoneNo)
    : User(ID, name, email, phoneNo, "", "Customer") {
    loadBalance();
}

~Customer() {
    cout << "Customer object destroyed for: " << getName() << endl;
}
//Inline function- is defined in class tells compiler instead of jumping to function's code 
//during a call, directly insert the function's body where it is called
inline float getBalance()const {
    return balance;
}
inline void setBalance(float amount) {
    balance=amount;
}
inline void incremenetBalance(float amount) {
    balance+=amount;
}

// save balance change after payment add money
void saveBalance() {
    try {
        ifstream fin("balance.txt");
        ofstream fout("temp.txt");

        string uid;
        float bal;
        bool found = false;

        while (fin >> uid >> bal) {
            if (uid == getID()) {
                fout << getID() << " " << balance << endl;
                found = true;
            } else {
                fout << uid << " " << bal << endl;
            }
        }
        if (!found) {
            fout << getID() << " " << balance << endl;
        }

        fin.close();
        fout.close();

        remove("balance.txt");
        rename("temp.txt", "balance.txt");
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
}

void loadBalance() {
    ifstream fin("balance.txt");
    if (!fin.is_open()) {
        balance = 0.0;
        return;
    }

    string id;
    float bal;

    while (fin >> id >> bal) {
        if (id == getID()) {
            balance = bal;
            fin.close();
            return;
        }
    }
    fin.close();
    balance = 0.0;
}

void receiveMoney(float amount) {
    if (amount > 0) {
        balance += amount;
    }
}

void addMoney(float amount) {
    if (amount > 0) {
        balance += amount;
        saveBalance();
        cout << "₹" << amount << " added successfully.\n";
    } else {
        cout << "Invalid amount.\n";
    }
}

void checkBalance() {
    cout << "Your current balance is ₹" << balance << endl;
}

void syncWallet() {
    loadBalance();
}
};

class Merchant : public User{
private:
double earnings;
double balance;
string merchantID;
string bussinessName;

public: 
   Merchant() : User() {
    this->merchantID="";
    this->bussinessName="";
    this->earnings=0.0;
    this->balance=0.0;
    this->setRole("Merchant");
   }

   // Add missing function for registration
   void newRegisterUser() {
       User::newRegisterUser();  // reuse base class registration
   }
};

class Wallet {
private:
string walletID;
string userID;      
double balance;

public:
   Wallet() {
        walletID = "WALLET000";
        userID = "";
        balance = 0.0;
    }
 Wallet(string walletID, string userID, double balance = 0.0) {
        this->walletID = walletID;
        this->userID = userID;
        this->balance = balance;
    }
  void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited " << amount << " successfully.\n";
            saveToFile();
        } else {
            cout << "Invalid amount!\n";
        }
    }
bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        cout << "Withdrew " << amount << " successfully.\n";
        saveToFile();
        return true;
    }
double getBalance() const {
        return balance;
    }
void saveToFile() {
        try {
            ofstream fout("wallets.txt", ios::app);
            if (!fout) throw runtime_error("Error: Couldn't open the wallet file");

            fout << walletID << " " << userID << " " << balance << endl;
            fout.close();
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
    }
           
      bool loadWallet(string uID) {
        try {
            ifstream fin("wallets.txt");
            if (!fin.is_open()) throw runtime_error("Error: Can't open the wallet file");

            string fWalletID, fUserID;
            double fBalance;

            while (fin >> fWalletID >> fUserID >> fBalance) {
                if (fUserID == uID) {
                    walletID = fWalletID;
                    userID = fUserID;
                    balance = fBalance;
                    fin.close();
                    return true;
                }
            }
            fin.close();
            return false;  // Wallet not found
        } catch (const exception &e) {
            cout << e.what() << endl;
            return false;
        }
    }     
//Operator overloading  but in function overloading the files details wont be save 
friend ostream& operator<<(ostream& out, const Wallet& w) {
        out << "\nWallet Info\n";
        out << "Wallet ID: " << w.walletID << endl;
        out << "User ID: " << w.userID << endl;
        out << "Balance: " << w.balance << endl;
        return out;
    }

Wallet operator+(double amount) const {
        Wallet temp = *this;  
        if (amount > 0) {
            temp.balance += amount;
        }
        return temp;
    }

Wallet operator-(double amount) const {
        Wallet temp = *this;
        if (amount > 0 && amount <= temp.balance) {
            temp.balance -= amount;
        }
        return temp;
    }

bool operator==(const Wallet& other) const {
        return this->balance == other.balance;
    }
};


class Payment {
private:
    string paymentId;
    string senderId;
    string receiverId;
    double amount;
    string status;   // Success / Fail / Refunded
    string dateTime;

   
    string getCurrentDateTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        return string(dt);
    }

public:
    Payment() {
        this->paymentId = "";
        this->senderId = "";
        this->receiverId = "";
        this->amount = 0.0;
        this->status = "Pending";
        this->dateTime = getCurrentDateTime();
    }

    Payment(string paymentId, string senderId, string receiverId, double amount) {
        this->paymentId = paymentId;
        this->senderId = senderId;
        this->receiverId = receiverId;
        this->amount = amount;
        this->status = "Pending";
        this->dateTime = getCurrentDateTime();
    }

    ~Payment() {
        cout << "Payment object with ID " << this->paymentId << " is destroyed.\n";
    }

    void processPayment() {
        if (this->amount > 0) {
            this->status = "Success";
            cout << "Payment of ₹" << this->amount << " from "
                 << this->senderId << " to " << this->receiverId
                 << " is successful!\n";
        } else {
            this->status = "Fail";
            cout << "Payment Failed! Invalid amount.\n";
        }
    }

    void processPayment(string sId, string rId, double amt) {
        this->senderId = sId;
        this->receiverId = rId;
        this->amount = amt;
        this->dateTime = getCurrentDateTime();

        if (this->amount > 0) {
            this->status = "Success";
            cout << "Payment of ₹" << this->amount << " from "
                 << this->senderId << " to " << this->receiverId
                 << " is successful! [Overloaded Function]\n";
        } else {
            this->status = "Fail";
            cout << "Payment Failed! Invalid amount.\n";
        }
    }
//Function overloading
    void refundPayment() {
        if (this->status == "Success") {
            this->status = "Refunded";
            cout << "Refund of ₹" << this->amount
                 << " done to " << this->senderId << endl;
        } else {
            cout << "Refund not possible! Transaction was not successful.\n";
        }
    }

    void refundPayment(double refundAmount) {
        if (this->status == "Success" && refundAmount > 0 && refundAmount <= this->amount) {
            cout << "Partial Refund of ₹" << refundAmount
                 << " done to " << this->senderId << endl;
            this->status = "Partially Refunded";
        } else {
            cout << "Partial refund not possible!\n";
        }
    }

    string getPaymentStatus() {
        return this->status;
    }

    void getPaymentDetails() {
        cout << "\n Payment Details\n";
        cout << "Payment ID  : " << this->paymentId << endl;
        cout << "Sender ID   : " << this->senderId << endl;
        cout << "Receiver ID : " << this->receiverId << endl;
        cout << "Amount      : ₹" << this->amount << endl;
        cout << "Status      : " << this->status << endl;
        cout << "Date & Time : " << this->dateTime << endl;
    }
};


int main() {
    //dynamic memory allocated
    User* user1 = new User();
   Customer* customer1=new Customer();
    
    Merchant* merchant1 = new Merchant();
    Wallet* wallet1=new Wallet();
    Payment* payment1 = new Payment();

 string input;
 int choice;

 while (true) {
    cout << "\nOnline Payment System\n";
    cout << "1. Register User\n";
    cout << "2. Login User\n";
    cout << "3. Register Merchant\n";
    cout << "4. Login Merchant\n";
    cout << "5. Add Money (Customer)\n";
    cout << "6. Check Balance (Customer)\n";
    cout << "7. Deposit in Wallet\n";
    cout << "8. Withdraw from Wallet\n";
    cout << "9. Wallet Information\n";
    cout << "10. Make Payment\n";
    cout << "11. Refund Payment\n";
    cout << "12. Logout User\n";
    cout << "13. Logout Merchant\n";
    cout << "0. Exit\n";

    cout << "Enter your choice (0-13): ";
    cin >> input;

    bool isNumber = !input.empty();
    for (char c : input) {
        if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }

    if (!isNumber) {
        cout << "Invalid input! Please enter a number from 0 to 13 only.\n";
        continue;
    }

   choice = stoi(input);

    if (choice < 0 || choice > 13) {
        cout << "Choice out of range! Please enter a number from 0 to 13 only.\n";
        continue;
    }

    if (choice == 0) break;

    switch (choice) {
        case 1: user1->newRegisterUser(); break;
        case 2: {
            string uid, pass;
            cout << "Enter User ID: "; cin >> uid;
            cout << "Enter Password: "; cin >> pass;
            user1->login(uid, pass);
            break;
        }
        case 3: merchant1->newRegisterUser(); break;
        case 4: {
            string mid, pass;
            cout << "Enter Merchant ID: "; cin >> mid;
            cout << "Enter Password: "; cin >> pass;
            merchant1->login(mid, pass);
            break;
        }
        case 5: {
            float amt;
            cout << "Enter amount to add: "; cin >> amt;
            customer1->addMoney(amt);
            break;
        }
        case 6: customer1->checkBalance(); break;
        case 7: {
            double amt;
            cout << "Enter deposit amount: "; cin >> amt;
            wallet1->deposit(amt);
            break;
        }
        case 8: {
            double amt;
            cout << "Enter withdraw amount: "; cin >> amt;
            wallet1->withdraw(amt);
            break;
        }
        case 9: cout << *wallet1; break;
        case 10: {
            string sId, rId;
            double amt;
            cout << "Enter Sender ID: "; cin >> sId;
            cout << "Enter Receiver ID: "; cin >> rId;
            cout << "Enter Amount: "; cin >> amt;
            payment1->processPayment(sId, rId, amt);
            break;
        }
        case 11: payment1->refundPayment(); break;
        case 12: user1->logout(); break;
        case 13: merchant1->logout(); break;
    }
 }

 delete user1;
 delete customer1;
 delete merchant1;
 delete wallet1;
 delete payment1;

 return 0;
}

