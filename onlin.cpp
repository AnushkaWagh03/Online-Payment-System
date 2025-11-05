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
            break; }
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
 do {
            cout << "Enter Password: ";
            cin >> password;
            if(!isStrongPassword(password))
                cout << "Password too weak! Must be 8+ chars, include upper, lower, digit, special char.\n";
        } while(!isStrongPassword(password));

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Set Security Question (e.g., Your favorite color?): ";
        getline(cin, securityQuestion);
        cout << "Answer: ";
        getline(cin, securityAnswer);
role = "Customer";
cout << "Registration successful!\n";

saveToFile();
saveSecurityQA();
 }
 void saveToFile() {
    string encPwd = encryptPassword(password);
       try {
        ofstream fout("users.csv", ios::app);
        if (!fout) return;
         fout << userID << "," << name << "," << email << "," << phone << "," 
             << encPwd << endl;
        fout.close();
    } catch (...) {
  }
}
void saveSecurityQA() {
    try {
        ofstream fout("security.csv", ios::app);
        if (!fout) return;

        string encQ = encryptPassword(securityQuestion);
        string encA = encryptPassword(securityAnswer);

        fout << userID << "," << encQ << "," << encA << endl;
        fout.close();
    } catch (const exception &e) {
        cout << "Error saving security Q&A.\n";
    }
}

static User getUser(const string &uid) {
    try {
        ifstream fin("users.csv");
        if (!fin.is_open()) return User();
        string line;
        while(getline(fin, line)) {
            stringstream ss(line);
            string fID, fName, hiddenPwd, fEmail, fPhoneStr, fSecQ, fSecA, realPwd;
            getline(ss, fID, ',');
            getline(ss, fName, ',');
            getline(ss, hiddenPwd, ',');
            getline(ss, fEmail, ',');
            getline(ss, fPhoneStr, ',');
            getline(ss, fSecQ, ',');
            getline(ss, fSecA, ',');
            getline(ss, realPwd, ',');

            if(fID == uid) {
                string fPhone = sanitizePhone(fPhoneStr);
                string decryptedPwd;
                try {
                    decryptedPwd = decryptPassword(realPwd);
                } catch (...) {
                    decryptedPwd = ""; 
                }

                User u(fID, fName, decryptedPwd, fEmail, fPhone);
                u.securityQuestion = fSecQ;
                u.securityAnswer = fSecA;
                return u;
            }
        }
        return User();
    } catch (const exception &e) {
        return User();
    }
}
static string getSecurityQuestion(const string &uid) {
    try {
        ifstream fin("security.csv");
        string line;
        while(getline(fin,line)){
            stringstream ss(line);
            string fID, encQ, encA;
            getline(ss,fID,','); getline(ss,encQ,','); getline(ss,encA,',');
            if(fID == uid) return decryptPassword(encQ);
        }
    } catch(...) {}
    return "";
}

static bool verifySecurityAnswer(const string &uid, const string &ans) {
    try {
        ifstream fin("security.csv");
        string line;
        while(getline(fin,line)){
            stringstream ss(line);
            string fID, encQ, encA;
            getline(ss,fID,','); getline(ss,encQ,','); getline(ss,encA,',');
            if(fID == uid) return decryptPassword(encA) == ans;
        }
    } catch(...) {}
    return false;
}


    bool login(string uid, string pwd){
        if(uid==userID && pwd==password){
            logIn=true;
            cout << "Login successful!\n";
            return true;
        }
        cout << "Wrong credentials.\n";
        return false;
    }
    // Function overloading
    bool login(string pwd){
        if(pwd==password) {
            logIn=true;
            cout<<"Quick login successfully";
            return true;
        }
        cout<<"Incorrect password";
        return false;
    }

    bool verifyPassword(const string &pwd) const {
        return pwd == password;
    }
static void resetPassword(const string &uid) {
    try {
        if (!exists(uid)) {
            cout << "User not found!\n";
            return;
        }

        ifstream fin("users.csv");
        ofstream fout("temp.csv");
        if (!fin.is_open() || !fout.is_open()) {
            cout << "File error: Unable to access user data.\n";
            return;
        }

        string line;
        bool changed = false;
        while (getline(fin, line)) {
            stringstream ss(line);
            string fID, fName, hiddenPwd, fEmail, fPhoneStr, fSecQ, fSecA, encPwd;
            getline(ss, fID, ',');
            getline(ss, fName, ',');
            getline(ss, hiddenPwd, ',');
            getline(ss, fEmail, ',');
            getline(ss, fPhoneStr, ',');
            getline(ss, fSecQ, ',');
            getline(ss, fSecA, ',');
            getline(ss, encPwd, ',');

            if (fID == uid) {
               string question = getSecurityQuestion(uid);
if (question.empty()) {
    cout << "No security question found.\n";
    return;
}
cout << "Security Question: " << question << endl;

                cout << "Answer: ";
                string ans;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, ans);

                if (verifySecurityAnswer(uid, ans)) {
                    string newPwd;
                    cout << "Enter new password: ";
                    cin >> newPwd;
                    User temp;
                    if (!temp.isStrongPassword(newPwd)) {
                        cout << "Password too weak! Must be 8+ chars, include upper, lower, digit, special char.\n";
                        fout << line << endl; // unchanged
                        continue;
                    }

                    string encNew = encryptPassword(newPwd);
                    fout << fID << "," << fName << "," << "" << "," << fEmail << "," << fPhoneStr
                         << "," << fSecQ << "," << fSecA << "," << encNew << endl;
                    cout << "Password reset successful!\n";
                    changed = true;
                } else {
                    fout << line << endl;
                    cout << "Incorrect answer. Password not changed.\n";
                }
            } else {
                fout << line << endl;
            }
        
        }

        fin.close();
        fout.close();
        remove("users.csv");
        rename("temp.csv", "users.csv");

        if (!changed)
            cout << "No password updated.\n";

    } catch (const exception &e) {
        cout << "An error occurred during password reset: " << e.what() << endl;
    }
}

    // Friend function
    friend void showUserInfo(const User &u);

static string toHex(const string &s) {
    static const char* hexDigits = "0123456789ABCDEF";
    string out;
    out.reserve(s.size()*2);
    for(unsigned char c : s) {
        out.push_back(hexDigits[c >> 4]);
        out.push_back(hexDigits[c & 0x0F]);
    }
    return out;
}

static string fromHex(const string &hex) {
    string out;
    out.reserve(hex.size()/2);
    for(size_t i=0; i+1 < hex.size(); i += 2) {
        auto hexVal = [](char c)->int {
            if(c >= '0' && c <= '9') return c - '0';
            if(c >= 'A' && c <= 'F') return 10 + (c - 'A');
            if(c >= 'a' && c <= 'f') return 10 + (c - 'a');
            return 0;
        };
        unsigned char high = (unsigned char)hexVal(hex[i]);
        unsigned char low  = (unsigned char)hexVal(hex[i+1]);
        out.push_back((char)((high << 4) | low));
    }
    return out;
}

static string encryptPassword(const string &plain) {
    const string key = "MySecretKey123"; 
    string xored;
    xored.reserve(plain.size());
    for(size_t i=0;i<plain.size();++i)
        xored.push_back( plain[i] ^ key[i % key.size()] );
    return toHex(xored);
}

static string decryptPassword(const string &cipherHex) {
    const string key = "MySecretKey123"; 
    string x = fromHex(cipherHex);
    string plain;
    plain.reserve(x.size());
    for(size_t i=0;i<x.size();++i)
        plain.push_back( x[i] ^ key[i % key.size()] );
    return plain;
}

};

void showUserInfo(const User &u) {
    cout << "User ID: " << u.userID << ", Name: " << u.name << ", Email: " << u.email << ", Phone: " << u.phone << endl;
}

class Account {
public:
    string userID;
    double balance;

    Account() { 
        this->balance = 0;
    }
    Account(string uid, double bal){ 
        this->userID = uid; 
        this->balance = bal; 
    }

    virtual void deposit(double amt) { 
    if (amt <= 0) {
        cout << "Invalid amount.\n";
        return;
    }
    balance += amt;
    cout << fixed << setprecision(2);
cout << "Added Rupees " << amt << endl;

}

    virtual bool withdraw(double amt) {
    if (amt <= 0) {
        cout << "Invalid amount.\n";
        return false;
    }
    if (balance < amt) {
        cout << fixed << setprecision(2);
cout << "Insufficient balance. Current balance: Rupees " << balance << endl;
        return false;
    }
    balance -= amt;
    cout << fixed << setprecision(2);
cout << "Withdrew Rupees " << amt << endl;
    return true;
}


    virtual void saveToFile(const string &filename) {
        try {
            ofstream fout(filename, ios::app);
            if(!fout) {
                cout << "File error: Unable to write to " << filename << "\n";
                return;
            }
            fout << userID << "," << balance << endl;
            fout.close();
        } catch (const exception &e) {
            cout << "File error: Unable to write to " << filename << "\n";
        }
    }

    virtual void updateFile(const string &filename) {
        try {
            ifstream fin(filename);
            ofstream fout("temp.csv");
            if(!fin.is_open() || !fout.is_open()) {
                ofstream create(filename, ios::app);
                if(create) {
                    create << userID << "," << balance << endl;
                    create.close();
                }
                return;
            }
            string line;
            bool updated=false;
            while(getline(fin,line)){
                stringstream ss(line);
                string fID; double bal;
                getline(ss,fID,',');
                ss >> bal;
                if(fID==userID){ fout<<userID<<","<<balance<<endl; updated=true; }
                else fout<<fID<<","<<bal<<endl;
            }
            if(!updated) fout<<userID<<","<<balance<<endl;
            fin.close(); fout.close();
            remove(filename.c_str());
            rename("temp.csv", filename.c_str());
        } catch (const exception &e) {
           
        }
    }

    double getBalance() const { return balance; }
};

class BankAccount : public Account {
public:
    BankAccount(): Account() {
        this->userID="";
        this->balance=1000;
    }
    BankAccount(string uid, double bal=1000): Account() {
        this->userID=uid;
        this->balance=bal;
    }

   void deposit(double amt){ 
    Account::deposit(amt); 
    cout << fixed << setprecision(2);
    cout << "Added Rupees " << amt << " to bank.\n"; 
}

   bool withdraw(double amt){
    if(Account::withdraw(amt)){ 
        cout << fixed << setprecision(2);
        cout << "Withdrew Rupees " << amt << " from bank.\n"; 
        return true; 
    }
    return false;
}


    void saveToFile(){ Account::saveToFile("banks.csv"); }
    static BankAccount load(const string &uid){
        try {
            ifstream fin("banks.csv");
            if (!fin.is_open()) return BankAccount(uid,1000);
            string line;
            while(getline(fin,line)){
                stringstream ss(line);
                string fID; double bal;
                getline(ss,fID,','); ss>>bal;
                if(fID==uid) return BankAccount(fID, bal);
            }
            return BankAccount(uid,1000);
        } catch (const exception &e) {
            return BankAccount(uid,1000);
        }
    }
    void updateFile(){ Account::updateFile("banks.csv"); }
};

class Wallet : public Account {
public:
    Wallet():Account() {
        this->userID="";
        this->balance=0;
    }
    Wallet(string uid, double bal=0):Account(){
        this->userID=uid;
        this->balance=bal;
    }

    // Inline functions
   inline void deposit(double amt){ 
    Account::deposit(amt); 
    cout << fixed << setprecision(2);
    cout << "Added Rupees " << amt << " to wallet.\n";
}

inline bool withdraw(double amt){
    if(Account::withdraw(amt)){ 
        cout << fixed << setprecision(2);
        cout << "Withdrew Rupees " << amt << " from wallet.\n"; 
        return true; 
    }
    return false;
}

    inline double getBalance() const {
         return Account::getBalance(); 
    }
    void saveToFile(){ Account::saveToFile("wallets.csv"); }
    static Wallet load(const string &uid){
        try {
            ifstream fin("wallets.csv");
            if (!fin.is_open()) return Wallet(uid,0);
            string line;
            while(getline(fin,line)){
                stringstream ss(line);
                string fID; double bal;
                getline(ss,fID,','); 
                ss >> bal;
                if(fID==uid) return Wallet(fID, bal);
            }
            return Wallet(uid,0);
        } catch (const exception &e) {
            return Wallet(uid,0);
        }
    }

    // Operator overloading
    void updateFile(){ Account::updateFile("wallets.csv"); }
    Wallet operator+(const Wallet &w) const {
        return Wallet(this->userID + "&" + w.userID, this->balance + w.balance);
    }

    bool operator==(const Wallet &w) const {
        return this->userID == w.userID;
    }

    double operator-(const Wallet &w) const {
        return this->balance - w.balance;
    }
    
    friend ostream& operator<<(ostream &out, const Wallet &w) {
        out << fixed << setprecision(2);
        out << "Wallet User ID: " << w.userID << "\nBalance: Rupees" << w.balance << endl;
        return out;
    }
};


class Bank {
public:
   void transferBank(BankAccount &s, BankAccount &r, const string &sn, const string &rn, double amt) {
    if (s.withdraw(amt)) {
        r.deposit(amt);
        s.updateFile();
        r.updateFile();
        saveTransaction(s.userID, r.userID, amt, "Bank");
       cout << fixed << setprecision(2);
cout << "Bank transfer " << amt << " from " << sn << " to " << rn << " done!\n";

    }
}

    void transferWallet(Wallet &s, Wallet &r, const string &sn, const string &rn, double amt){
        try {
            if(s.withdraw(amt)){
                r.deposit(amt);
                s.updateFile();
                r.updateFile(); 
                saveTransaction(s.userID,r.userID,amt,"Wallet");
                cout << fixed << setprecision(2);
                cout<<"Wallet transfer "<<amt<<" from "<<sn<<" to "<<rn<<" done!\n";
            }
        } catch (const exception &e) {
            cout << "Transfer failed: " << e.what() << endl;
        }
    }
    void saveTransaction(string s,string r,double amt,string type){
        try {
            ofstream fout("transactions.csv",ios::app);
            if(!fout) return;
            time_t now=time(0);
            fout<<s<<","<<r<<","<<amt<<","<<type<<","<<now<<endl;
            fout.close();
        } catch (...) {
           
        }
    }
    static void showHistory(){
        try {
            ifstream fin("transactions.csv");
            if (!fin.is_open()) {
                cout<<"\nTransaction History:\n";
                return;
            }
            string line;
            cout<<"\nTransaction History:\n";
            while(getline(fin, line)){
                stringstream ss(line);
                string s, r, type;
                double amt;
                long long t;
                getline(ss, s, ',');
                getline(ss, r, ',');
                ss >> amt;
                ss.ignore();
                getline(ss, type, ',');
                ss >> t;
               cout << fixed << setprecision(2);
cout << "From: " << s << " To: " << r 
     << " | ₹ " << amt 
     << " | Type: " << type 
     << " | Time: " << ctime((time_t*)&t);

            }
        } catch (const exception &e) {
            cout << "\nTransaction History:\n";
        }
    }
};


 


