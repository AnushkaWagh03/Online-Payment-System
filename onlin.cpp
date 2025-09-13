#include<iostream>
#include<fstream> //header file used for file
#include<string>
using namespace std;
class User{  //the one who is using the system(customer)
   public:
    string ID;
    string name;
    string email;
    int phoneNo;

    protected:
    string password;
    bool logIn;


    public:
    User() {  
        //At start never it shoes u have already login first u 
        //need to enter the details and then it shows 
        logIn=false;
    }
    User(string ID, string name,string email,int phoneNo){
        this->ID=ID;  //Parametrized constructor
        this->name=name;
        this->phoneNo=phoneNo;
        this->email=email;
        this->password=password;
        this->logIn=false;
    }
    

    //Registration for the new user
    void newRegisterUser(){
        cout<<"Enter User ID: ";
        cin>>ID;
        cout<<"Enter Name: ";
        cin.ignore();
        getline(cin,name);  //name  cant be continuous by using 
        //get line two different words input will be taken
        cout<<"Enter Email-id: ";
        cin>>email;
        cout<<"Enter Phone Number: ";
        cin>>phoneNo;
        cout<<"Enter Password: ";
        cin>>password;


        void saveToFIle();//will user information in user.txt file
            cout<<"Congrats! User has registered successfully...";

        

    }
    void saveToFile() {
        try{
            ofstream fout("users.txt", ios::app);//will open file in append mode
            if(!fout){
                throw " Error: Coundn't open the file";
            
            }
            fout<<ID << " "<< name<< " "<< email<<" "<< phoneNo <<" "<<password<< endl;
      fout.close(); //add the above details and close the file

        }
        catch(const exception& e) {
            cout<<e.what() << endl;   //will be showing the error
        }   
        }

        bool login(string userID, string userPassword){
            try{
                ifstream fin("users.txt");
                if(!fin.is_open()) {
                    throw runtime_error("Error: Can't open the file");
                }

                string fID;
                string fName;
                string fEmail;
                string fPassword;
                string fPhone;
                bool userFound=false;


                
              while (fin >> fID >> fName >> fEmail >> fPhone >> fPassword) {
            if (fID == userID) {
                userFound = true;  // user ID exists

                if (fPassword == userPassword) {
                    cout << "Login successful! Welcome " << fName << ".\n";
                    logIn = true;
                    fin.close();
                    return true;
                }
            }
        }

        fin.close();

        if (!userFound) {
            cout << "User not found! Please register first.\n";
        } else {
            cout << "Wrong password!\n";
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
    return false;
}

        


        void logOut() {
            if(logIn) {
                logIn=false;
                cout<<"Logged out successfully";
            } 
            else {
                cout<<"You are not login ";
            }
        }

        void displayProfile() {
            cout<<"\n=====User Profile=====";
            cout<<"User ID: "<<ID<<endl;
            cout<<"Name: "<<endl;
            cout<<"Email: "<<endl;
            cout<<"Phone: "<<endl;
            
        }
    };

class Customer : public User {
private:
    float balance;

public:
    Customer() : User() {
        balance = 0.0;
    }

    Customer(string ID, string name, string email, long long phoneNo) : User(ID, name, email, phoneNo) {
        loadBalance();
    }

    ~Customer() {
        cout << "Customer object destroyed for: " << name << endl;
    }

void saveBalance() {
        try {
            ifstream fin("balance.txt");
            ofstream fout("temp.txt");

            string uid;
            float bal;
            bool found = false;

            while (fin >> uid >> bal) {
                if (uid == ID) {
                    fout << ID << " " << balance << endl;
                    found = true;
                } else {
                    fout << uid << " " << bal << endl;
                }
            }
 if (!found) {
                fout << ID << " " << balance << endl;
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
            if (id == ID) {
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

class Merchant {
private:
    string merchantID;
    string name;
    string email;
    string password;
    bool loggedIn;

    bool isDuplicateID(const string &id) {
        ifstream fin("merchants.txt");
        string fID, fName, fEmail, fPass;
        while (fin >> fID >> fName >> fEmail >> fPass) {
            if (fID == id) {
                return true;
            }
        }
        return false;
    }

public:
    Merchant() : loggedIn(false) {}

    Merchant(string id, string name, string email, string password) {
        this->merchantID = id;
        this->name = name;
        this->email = email;
        this->password = password;
        loggedIn = false;
    }

    ~Merchant() {
        cout << "Merchant object destroyed for: " << name << endl;
    }

    void registerMerchant() {
        cout << "\n--- Merchant Registration ---\n";

        do {
            cout << "Enter Merchant ID: ";
            cin >> merchantID;
            if (merchantID.empty()) {
                cout << "Merchant ID cannot be empty.\n";
                continue;
            }
            if (isDuplicateID(merchantID)) {
                cout << "Merchant ID already exists! Please choose another.\n";
                merchantID.clear();
            }
        } while (merchantID.empty());

        cin.ignore();
        do {
            cout << "Enter Name: ";
            getline(cin, name);
            if (name.empty()) {
                cout << "Name cannot be empty.\n";
            }
        } while (name.empty());

        do {
            cout << "Enter Email: ";
            cin >> email;
            if (email.empty()) {
                cout << "Email cannot be empty.\n";
            }
        } while (email.empty());

        string confirmPassword;
        do {
            cout << "Enter Password: ";
            cin >> password;
            cout << "Confirm Password: ";
            cin >> confirmPassword;

            if (password.empty()) {
                cout << "Password cannot be empty.\n";
            } else if (password != confirmPassword) {
                cout << "Passwords do not match. Please try again.\n";
                password.clear();
            }
        } while (password.empty() || password != confirmPassword);

        saveToFile();
        cout << "Merchant registered successfully!\n";
    }

    void saveToFile() {
        try {
            ofstream fout("merchants.txt", ios::app);
            if (!fout.is_open()) {
                throw runtime_error("Error: Could not open merchants.txt");
            }
            fout << merchantID << " " << name << " " << email << " " << password << endl;
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }

    bool login(const string &id, const string &pass) {
        try {
            ifstream fin("merchants.txt");
            if (!fin.is_open()) {
                throw runtime_error("Error: Could not open merchants.txt");
            }

            string fID, fName, fEmail, fPass;
            while (fin >> fID >> fName >> fEmail >> fPass) {
                if (fID == id && fPass == pass) {
                    loggedIn = true;
                    merchantID = fID;
                    name = fName;
                    email = fEmail;
                    password = fPass;
                    cout << "Login successful! Welcome, " << name << ".\n";
                    return true;
                }
            }
            cout << "Invalid Merchant ID or Password.\n";
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
        return false;
    }

    void logOut() {
        if (loggedIn) {
            loggedIn = false;
            cout << "Merchant logged out successfully.\n";
        } else {
            cout << "Merchant is not logged in.\n";
        }
    }

    void displayProfile() const {
        if (loggedIn) {
            cout << "\n--- Merchant Profile ---\n";
            cout << "Merchant ID : " << merchantID << endl;
            cout << "Name        : " << name << endl;
            cout << "Email       : " << email << endl;
        } else {
            cout << "Please login to view profile.\n";
        }
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
                if (fUserID == userID) {
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
void displayWallet() {
        cout << " Wallet Info :";
        cout << "Wallet ID: " << walletID << endl;
        cout << "User ID: " << userID << endl;
        cout << "Balance: " << balance << endl;
    }
};
int main() {
    //object is created user1
    User user1;
    Wallet wallet1("W111","C111",1000.0);
    Customer customer1("C111","Raj","raj@gmail.com",9454782922);
   Merchant merchant1("M111","Yogesh","yogesh@gmail.com","yogesh8437");
    int choice;
    while(1) {
        cout<<"\n Online Payment System"<<endl;
        cout<<"1.Registration for User: "<<endl;
        cout<<"2.Login for User: "<<endl;
        cout<<"3.Registration for Merchant: "<<endl;
        cout<<"4.Login for Merchant: "<<endl;
        cout<<"5.Add Money (Customer) : "<<endl;
        cout<<"6.Check Balance (Customer): "<<endl;
        cout<<"7.Deposit in the wallet: "<<endl;
        cout<<"8.Withdraw from wallet: "<<endl;
        cout<<"9.wallet Information: "<<endl;
        cout<<"10.Logout the User: "<<endl;
        cout<<"11.Logout the merchant: "<<endl;
      cout<<"Enter your choice: ";
      if (cin.fail()) {   // If we enter any wrong choice (like a character instead of number)
    cout << "Wrong choice. Please!!  Enter the choice from 1 to 11" << endl;
    cin.clear();       
    cin.ignore(1000, '\n'); 
    continue;            
}

      cin>>choice;
      if(choice==1) {
        user1.newRegisterUser();

      }
else if(choice==2) {
    string uid;
    string pass;
    cout<<"Enter the User ID: ";
    cin>>uid;
    cout<<"Enter the Password: ";
    cin>>pass;
    user1.login(uid,pass);

}
    else if(choice==3){
        merchant1.registerMerchant();
    }
    else if(choice==4){
        string merchantid;
        string merchantpassword;
        cout<<"Enter the Merchant ID: ";
        cin>>merchantid;
        cout<<"Enter the password: ";
        cin>>merchantpassword;
        merchant1.login(merchantid,merchantpassword);


    }
    else if(choice==5) {
        float amnt;
        cout<<"Enter the amount which you wants to add: ";
        cin>>amnt;
        customer1.addMoney(amnt);

    }
    else if(choice==6) {
        customer1.checkBalance();

    }
    else if(choice==7){
        double amnt;
        cout<<"Enter the deposit amount: ";
        cin>>amnt;
        wallet1.deposit(amnt);
    }
    else if(choice==8) {
        double amnt;
        cout<<"Enter the withdraw amount: ";
        cin>>amnt;
        wallet1.withdraw(amnt);
        
    }
    else if(choice==9){
        wallet1.displayWallet();
      

    }
    else if(choice==10){
        user1.logOut();
    }
    else if(choice==11) {
        merchant1.logOut();
    }
}
    return 0;
   
}
