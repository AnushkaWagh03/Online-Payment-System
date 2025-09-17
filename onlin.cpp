#include<iostream>
#include<fstream> //header file used for file
#include<string>

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
    User(string ID, string name,string email,int phoneNo){
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
    Customer(string ID="C001",string name="Defaultcustomer",string email="un@gmail.com",long long phoneNo=0) : User(ID,name,email,phoneNo) {
        balance = 0.0;
    }

    Customer(string ID, string name, string email, long long phoneNo) : User(ID, name, email, phoneNo) {
        loadBalance();
    }
// destrudctor
    ~Customer() {
        cout << "Customer object destroyed for: " << name << endl;
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

// 
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
    else if(choice=3){
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


    }
    else if(choice==5) {
        float amnt;
        cout<<"Enter the amount which you wants to add: ";
        cin>>amnt;
        customer1->addMoney(amnt);

    }
    else if(choice==6) {
        customer1->checkBalance();

    }
    else if(choice==7){
        double amnt;
        cout<<"Enter the deposit amount: ";
        cin>>amnt;
        wallet1->deposit(amnt);
    }
    else if(choice==8) {
        double amnt;
        cout<<"Enter the withdraw amount: ";
        cin>>amnt;
        wallet1->withdraw(amnt);
        
    }
    else if(choice==9){
        wallet1->displayWallet();
      

    }
    else if(choice==10){
        user1->logOut();
    }
    else if(choice==11) {
        merchant1->logOut();
    }
}

   // deallocate memory
delete user1;
delete wallet1;
delete customer1;
delete merchant1;

    return 0;
   
}
