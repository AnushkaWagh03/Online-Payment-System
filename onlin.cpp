#include<iostream>
#include<fstream> //header file used for file
#include<string>
#include <ctime>
=======

using namespace std;
class User{  //the one who is using the system(customer)
   private:
    string ID;
    string name;
    string email;
    long long phoneNo;

    protected:
    string password;
    string role; //Customer/Mercant/Admin
    bool logIn;


    public:
    User() { 
        //Default constructor 
        //At start never it shoes u have already login first u 
        //need to enter the details and then it shows 
        logIn=false;
        role="Customer"; //default role
    }
    //Parametrised  constructor
    User(string ID, string name,string email,long long phoneNo,string password="",string role="Customer"){
        this->ID=ID;  //Parametrized constructor
        this->name=name;
        this->phoneNo=phoneNo;
        this->email=email;
        this->password=password;
        this->logIn=false;
        this->role=role;
    }
    //Destructor
    ~User() {
        cout<<"user object with ID"<<ID<< "is being destroyed\n";
    }
    //Friend function
    friend void showDetails(User &u);

     //New Registration
  void newRegisterUser() {
    try{
    cout<<"Enter User ID: ";
    cin>>ID;
cout<<endl;
cout<<"Enter Name: ";
cin.ignore();
getline(cin,name);
cout<<endl;
cout<<"Enter Email-ID: ";
cin>>email;
cout<<endl;
cout<<"Enter Phone Number: ";
if(!(cin >>phoneNo)) {  //will check where the phone no is numeric
    throw invalid_argument("Phone number must be numeric!");
}
cout<<endl;
cout<<"Enter Password: ";
cin>>password;
cout<<endl;
cout<<"Enter Role: ";
cout<<"1.Customer\n 2.Merchant\n 3.Admin";
cin>>role;
cout<<endl;

saveToFile();
cout<<"Congragulations!! User has registered successfully";

  }
  catch(const exception& e) {
    cout<<"Registration is failed:"<<e.what() <<endl;
    cin.clear();
    cin.ignore(1000,'\n');
  }

 }
//Information is saved into the file
  void saveToFile(){
    try{
    ofstream fout("users.txt",ios::app);   //ofstream-writes into the file
    if(!fout) {            //ios::app- append the file means new date is added down
        throw runtime_error("Error: Could not open file for saving!");

    }
    fout<<ID<< " "<<name<<" "<<email<<" "<<phoneNo<<" "<<password<<" "<<role<<endl;
fout.close();
}

  catch(const exception& e) {
    cout<<"Save File "<<e.what()<<endl;
  }
}

//Login Function
bool login(string userId, string userPassword) {
    try {
        ifstream fin("users.txt");  //ifstream-read the file
     if(!fin.is_open()) {
        throw runtime_error("Error: Couldn't open the file for login!");

     }
     string fID;
     string fName;
     string fEmail;
     string fRole;
     string fPassword;
     int fPhoneNo;
     bool userFound=false;

     while(fin>>fID>>fName>>fEmail>>fPhoneNo>>fPassword>>fRole){
        if(fID==userId) {
            userFound=true;
            if(fPassword==userPassword) {
                cout<<"Login succesfully! Welcome "<<fName<< " ("<<fRole << ").\n";
                logIn=true;
                role=fRole;
                fin.close();
                return true;
            }
                else {
                    throw runtime_error("Wrong Password");


                }
            }


        }
        if(!userFound) {
            throw runtime_error("User not found! Firstly Please Register");

        }
        fin.close();

     }
 catch(const exception& e) {
        cout<<e.what()<<endl;
     }
     return false;
    }

 //logout
 void logout() {
    if(logIn) {
        logIn=false;
        cout<<"Logged out successfully \n";

    }else {
        cout<<"You are not logged in.\n";
    }
 }

 //Change Password
 void changePassword(string oldPassword,string newPassword){
    try{
        if(!logIn) {
            throw runtime_error("You must log in first!!");
        }

 if(oldPassword==password) {
            password=newPassword;
            cout<<"Password chnage successfully\n";

        } else {
            throw runtime_error("Old paassword is incorrect");

        }
        } catch(const exception& e) {
            cout<<e.what()<<endl;
        }
    } 
    //Role functions
 void setRole(string newRole) {
    role=newRole;

 }
 string getRole(){
    return role;

 } 
 bool isAdmin() {
    return role=="Admin";
 }
 bool isCustomer() {
    return role=="Customer";
 }
 bool isMerchant() {
    return role=="Merchant";
 }

 //Displaay the profile
 void displayProfile() {
    cout<<"\n====User Profile====\n";
    cout<<"User ID: "<<ID<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Phone: "<<phoneNo<<endl;
    cout<<"Role: "<<role<<endl;

 }
 // Getter for User ID
string getID() const {
    return ID;
}
string getName() const {
    return name;
}
};

//Friend function definition- It is a non-member function which is given special access to class's private and protected members.
void showDetails(User &u) {
    cout << "[Friend] User ID: " << u.ID << ", Name: " << u.name << ", Email: " << u.email << endl;
}


class Customer : public User {
private:
    float balance;

public:
// default constructor with default arguments
    Customer() : User("C001","Defaultcustomer","un@gmail.com",0,"","Customer") {
    balance = 0.0;
}

Customer(string ID, string name, string email, long long phoneNo)
    : User(ID, name, email, phoneNo, "", "Customer") {
    loadBalance();
}

  
// destrudctor
    ~Customer() {
        cout << "Customer object destroyed for: " << getName() << endl;
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

// load exiting balance 
// when coustomer logs in
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

// increace money after receving money
    void receiveMoney(float amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

// add money to wallet
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

// if money updated then reloads correct value
    void syncWallet() {
        loadBalance();
    }
};

//Inheritance is used
class Merchant : public User{
private:
double earnings;
double balance;
    string merchantID;
   

   string bussinessName;

   public: 
   //Default constructor
   Merchant() : User() {
    this->merchantID="";
    this->bussinessName="";
    this->earnings=0.0;
    this->balance=0.0;
    this->setRole("Merchant");
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
//Operator overloading
//These will print wallet details  directly using cout  Wallet w1("W1","U1",1000)     cout<<w1    these will print wallet information
 friend ostream& operator<<(ostream& out, const Wallet& w) {
        out << "\n==== Wallet Info ====\n";
        out << "Wallet ID: " << w.walletID << endl;
        out << "User ID: " << w.userID << endl;
        out << "Balance: " << w.balance << endl;
        return out;
    }

    //+ operator will add money to the wallet

    Wallet operator+(double amount) const {
        Wallet temp = *this;  
        if (amount > 0) {
            temp.balance += amount;
        }
        return temp;
    }

    //- operator will withdraw the money from the wallet
    //the same work is done by withdraw function but if we use opearor overloading the details won't be save 
    Wallet operator-(double amount) const {
        Wallet temp = *this;
        if (amount > 0 && amount <= temp.balance) {
            temp.balance -= amount;
        }
        return temp;
    }

    // Compare two wallets by balance
    bool operator==(const Wallet& other) const {
        return this->balance == other.balance;
    }
};
<<<<<<< HEAD
=======
int main() {
    //object is created user1 using dynamic memory allocation
 User* user1 = new User();
Wallet* wallet1 = new Wallet("W111", "C111", 1000.0);
Customer* customer1 = new Customer("C111", "Raj", "raj@gmail.com", 9454782922);
Merchant* merchant1 = new Merchant();
);
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
        user1->newRegisterUser();
      }
         
    else if(choice==2) {
    string uid;
    string pass;
    cout<<"Enter the User ID: ";
    cin>>uid;
    cout<<"Enter the Password: ";
    cin>>pass;
    user1->login(uid,pass);

  }
    else if(choice==3){
        merchant1->registerMerchant();
    }
    else if(choice==4){
        string merchantid;
        string merchantpassword;
        cout<<"Enter the Merchant ID: ";
        cin>>merchantid;
        cout<<"Enter the password: ";
        cin>>merchantpassword;
        merchant1->login(merchantid,merchantpassword);
>>>>>>> 40bbad12abb56e79caec398adbf910b7f4898d35


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
    // Default Constructor
    Payment() {
        this->paymentId = "";
        this->senderId = "";
        this->receiverId = "";
        this->amount = 0.0;
        this->status = "Pending";
        this->dateTime = getCurrentDateTime();
    }

    // Parameterized Constructor
    Payment(string paymentId, string senderId, string receiverId, double amount) {
        this->paymentId = paymentId;
        this->senderId = senderId;
        this->receiverId = receiverId;
        this->amount = amount;
        this->status = "Pending";
        this->dateTime = getCurrentDateTime();
    }

    // Destructor
    ~Payment() {
        cout << "Payment object with ID " << this->paymentId << " is destroyed.\n";
    }

  

  //Funcion overloading- multiple function with same name but different parameter list 
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

   

    // Get Payment Status
    string getPaymentStatus() {
        return this->status;
    }

   
    void getPaymentDetails() {
        cout << "\n==== Payment Details ====\n";
        cout << "Payment ID  : " << this->paymentId << endl;
        cout << "Sender ID   : " << this->senderId << endl;
        cout << "Receiver ID : " << this->receiverId << endl;
        cout << "Amount      : ₹" << this->amount << endl;
        cout << "Status      : " << this->status << endl;
        cout << "Date & Time : " << this->dateTime << endl;
    }
};



int main() {
    // Create objects
    User* user1 = new User();
    Customer* customer1 = new Customer("C111", "Raj", "raj@gmail.com", 9876543210);
    Merchant* merchant1 = new Merchant();
    Wallet* wallet1 = new Wallet("W111", "C111", 1000.0);
    Payment* payment1 = new Payment();

 string input;
int choice;

while (true) {
    cout << "\n==== Online Payment System ====\n";
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

    // Check if the input is fully numeric
    bool isNumber = !input.empty();
    for (char c : input) {
        if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }

    if (!isNumber) {
        cout << "Invalid input! Please enter a number from 0 to 13 only.\n";
        continue; // reject non-numeric input
    }

   choice = stoi(input);

    // Check range
    if (choice < 0 || choice > 13) {
        cout << "Choice out of range! Please enter a number from 0 to 13 only.\n";
        continue;
    }

    if (choice == 0) break; // Exit

    // Switch-case safely
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
}
