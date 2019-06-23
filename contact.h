
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
// TODO: You may need to add other libraries here!
using namespace std;


class Contact {
    // TODO: private or protected? Look at your children!	
protected:
	string type;
public:
	 virtual void print() = 0;
    virtual string get_contact(string style="full") = 0;
	 virtual void set_contact() = 0;
	 
	 //added
	 virtual void set_contact(string str_type, string att) = 0;
};


class Email: public Contact{
private:
    string email_addr;
    string type;   //added
public:
    Email(string type, string email_addr);
    Email();
    // TODO: Complete me!
    void print();
    string get_contact(string style="full");
    void set_contact();
    
    //added
    void set_contact(string str_type, string att);

};


class Phone: public Contact{
private:
    // TODO: modify dataType! Can int store 10 digit phone-number? 
	//long int phone_num; 
	string phone_number;
	string type;  //added
	
public:
    Phone(string type, string phone_number);
    Phone();
    //~Phone();
    // TODO: Complete me!
    void print();
    string get_contact(string style="full");
    void set_contact();
    
    //added
    void set_contact(string str_type, string att);
    
    
};



















#endif
