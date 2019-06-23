#include "connection.h"
#include <algorithm>
#include "misc.h"
Connection::Connection(){
    // I'm already done! 
    set_connection();
}


Connection::~Connection(){
    // TODO: Complete me!
    delete birthdate;
    delete email;
    delete phone;  //
    

}


Connection::Connection(string f_name, string l_name, \
        string bdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    string str, str1, str2, str3, str4;
    
    
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(bdate);
    
    str1 = email.substr(1,email.find(")")-1);
    str2 = email.substr(email.find(")")+1);
    
    this->email = new Email(str1, str2);
    
    str3 = phone.substr(1,phone.find(")")-1);
    str4 = phone.substr(phone.find(')')+2);
    
    this->phone = new Phone(str3, str4);
}


Connection::Connection(string filename){
    // TODO: Complete this method!
    set_connection(filename);
}

Connection::Connection(string f_name, string l_name){
    this->f_name = f_name;
    this->l_name = l_name;
}

void Connection::set_connection(){
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    string temp;
    string type;

    cout << "First Name: ";
    // code here
    std::getline(std::cin,f_name);
    
	cout << "Last Name: ";
    // code here
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    // code here
    std::getline (std::cin,temp);
    birthdate = new Date(temp); 
    
    cout << "Type of email address: ";
    // code here
    std::getline(std::cin,type);
    
    cout << "Email address: ";
    // code here
    std::getline(std::cin,temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    // code here
    std::getline(std::cin,type);
    
    cout << "Phone number: ";
    // code here
    std::getline(std::cin,temp);
    phone = new Phone(type, temp);
}


void Connection::set_connection(string filename){
    // TODO: Complete this method!
    // Look at connection_template files as examples.     
    // Phone number in files can have '-' or not.
    ifstream infile;
    infile.open(filename.c_str());
    string tempdate,type_e, type_p, str_e, str_p, str1, str2;
   
    getline(infile, this->f_name);
    getline(infile, this->l_name);
    getline(infile, tempdate);
    birthdate = new Date(tempdate);
    
    getline(infile, type_e, ')');
    str1 = type_e.substr(2, type_e.find(")"-1));    
    getline(infile, str_e);
    email = new Email(type_e, str_e);
    
    getline(infile, type_p, ')');
    str2 = type_p.substr(1);
    getline(infile, str_p);
    phone = new Phone(type_p, str_p);
}


bool Connection::operator==(const Connection& rhs){
    // TODO: Complete this method!
    // Note: Difference to Lab is that from now on the combination of fname-lname is unique for any connection
    if ((f_name == rhs.f_name) &&
        (l_name == rhs.l_name))
        return true;
    else
        return false;
}


bool Connection::operator!=(const Connection& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Connection::print_connection(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    unsigned int size = myfriends.size();
    for (unsigned int i = 0; i < size; i++) {
        cout << codeName(myfriends[i]->f_name, myfriends[i]->l_name)<<endl;

    }
}

void Connection::makeFriends(Connection* ptr){
    
    
    unsigned int size = myfriends.size();
    for (unsigned int i = 0; i < size; i++) {
        if((myfriends[i]->f_name==ptr->f_name)&&(myfriends[i]->l_name==ptr->l_name)){
            myfriends.erase(myfriends.begin()+i);
        }
    }
    myfriends.push_back(ptr);
}

void Connection::write_connection(ofstream &outfile){
         outfile << l_name << ", " << f_name << endl;
         outfile << birthdate->get_date() << endl;
         outfile << email->get_contact()<<endl;
         outfile << phone->get_contact()<<endl;
        unsigned int size = myfriends.size();
        for (unsigned int i = 0; i < size; i++) {
            outfile << codeName(myfriends[i]->f_name, myfriends[i]->l_name) << endl;
        }

         outfile << "----------------"<< endl;
}




//https://www.geeksforgeeks.org/std-find-in-cpp/#include<bits/stdc++.h>
//used to print/save/load friends