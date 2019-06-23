
#include "contact.h"

// TODO: Add needed libraries! 
#include <iostream>
#include <string>
#include <stdio.h>      
#include <stdlib.h>
#include <sstream>
#include <algorithm>

//Added by me
Email::Email(){
    set_contact();
}


Email::Email(string type, string email_addr){
    // TODO: Complete me!
    set_contact(type, email_addr);
}

/*
void Email::set_contact(string str_e, string str_p){
    
}
*/

void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    cin >> type;
    cout << "Enter email address: ";
    // some code here
    cin >> email_addr;
}

void Email::set_contact(string str_type, string att){
    email_addr = att;
    type = str_type;

}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}

void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}

//Added by me
Phone::Phone(){
    set_contact();
}

/*
Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    // The code has been covered in the discussion session
    string area_code, num_top, num_bottom, phone_num;
    area_code = (num.substr(0, 3).c_str());
    num_top = (num.substr(3,num.find('-')).c_str());
    num_bottom= (num.substr(7).c_str());
    phone_num = area_code+ num_top + num_bottom;
    */
    
    
    /* Note: Understand your own TA's bug!
     * This code has a bug, can you understand why?
    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    */
//}


Phone::Phone(string type, string phone){
    set_contact(type, phone);
}

void Phone::set_contact(string str_type, string att){
    
    att.erase(std::remove(att.begin(), att.end(), '-'), att.end());
    phone_number = att;
    type = str_type;

}



void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
	cin >> type;   //
	cout << "Enter the phone number: ";
	cin >> phone_number;  // phone_number.replace("-", "")
	
	
}



string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // The code has been covered in discussion session 
    //stringstream ss;
    
    //ss << phone_number;
    string area_code = phone_number.substr(0,3);
    string first = phone_number.substr(3,3);
    string last = phone_number.substr(6);
    string complete = area_code + "-"+ first + "-" + last;
    
    if (style=="full")
	    return "(" + type + ") " + complete; //also had ss.str();
    else 
        return phone_number;

    /* Note: Understand your own TA's bug!
     * This code has a bug, can you understand it!
    int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;
    */ 
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


