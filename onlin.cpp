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

class Customer : public User{
private:
float balance;

public:
 Customer() : User(){
  balance = 0.0;
 }

Customer(string ID, string name, strng email, int phoneNo) : User(ID, name, email, int phoneNo){
loadBalance():
}

void loadBalance(){
   ifstream file("balance.txt");
        string id;
        float bal;
        balance = 0.0;
        while (file >> id >> bal) {
            if (id == ID) {
                balance = bal;
                break;
            }
        }
        file.close();
}


class Merchant {
private:
    string merchantID;
    string name;
    string email;
    string password;
    bool loggedIn;
public:
    Merchant() {
        loggedIn = false;
    }

class Wallet {
private:
string walletID;
    string userID;      
    double balance;
};
public:
   Wallet() {
        walletID = "WALLET000";
        userID = "";
        balance = 0.0;
    }
 Wallet(string wID, string uID, double bal = 0.0) {
        this->walletID = wID;
        this->userID = uID;
        this->balance = bal;
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


int main() {
    return 0;
   
}
