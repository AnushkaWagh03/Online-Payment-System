
import java.io.*;
import java.util.*;
class User{
    private String id;
    private String name;
    private String password;
    private String phone;
    protected Wallet wallet;   //Separate class which will manage balance(deposit/withdraw/check balance)
    protected ArrayList<Transaction>transactions;

    public User(String id,String name, String password, String phone,double balance) {
        this.id=id;
        this.name=name;
        this.password=password;
        this.phone=phone;
        this.wallet= new Wallet(balance);
        this.transactions=new Arraylist<>();
    }


public String getId(){
    return id;
}
public String getPhone() {
    return phone;
}
public String getName() {
    return name;
}
 public boolean checkPassword(String pass) {
     return this.password.equals(pass);
 }
 public void showTransaction(){
    if(transactions.isEmpty()) {
        System.out.println("No transaction is done till now.");
    }
    else {
        for (Transaction t : transactions) {
            t.display();
            
        }
    }
 }
 public double getbalance() {
    return wallet .getBalance();
 }
class Customer{

}


class Merchant{

}
class Wallet{

}
class Payment{

}
class Transaction{

}

class PaymentFlow{

}
class FileHandler{

}


public class online{
    public static void main(String[] args) {
        
    }
}