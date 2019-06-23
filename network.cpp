
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <iostream>
#include <string>
#include <dirent.h> // directory+entry
#include <stdio.h>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;



Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);
}

Network::~Network(){
    // Copy from lab5 
    Connection *ptr = head;
    while(head!=NULL){
         ptr=head->next;
         delete head;
         head = ptr; 
         count--; 
    }
}


void Network::push_front(Connection* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){
    // Adds a new Connection (newEntry) to the back of LL
    // Copy from your lab5
    newEntry->next = NULL;
    newEntry->prev = tail;
    
    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
         
    tail = newEntry;
    count++;
}



Connection* Network::search(Connection* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Copy from lab5 
    Connection* ptr = head;
    //cout << "check"<<endl;2
    while(ptr!=NULL){
         if (*ptr == *searchEntry){
            return ptr;}
         ptr=ptr->next;
         
    }
    return NULL;
}


Connection* Network::search(string fname, string lname){
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 
    
    //from lab5
    //Connection* check = new Connection(fname, lname);
    Connection* ptr = head;
    //ptr = search(check);
    while(ptr!=NULL){
         if(ptr->f_name == fname && ptr->l_name == lname){
              //cout << "found" << endl;
              return ptr;}
         ptr = ptr->next;
    }
    //delete check;
    return NULL;
}


Connection* Network::search(string code){



}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;
    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 
    
    ofstream outfile;
    outfile.open(filename.c_str());
    //outfile << "Number of connections: " << count << endl;
    Connection* ptr = head;
    while(ptr != NULL){
         ptr->write_connection(outfile);
         ptr = ptr->next;
    }
    
}


void Network::loadDB(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    //Connection::Connection(fname, lname, bdate, email, phone) //uncommented from original skeletop code 
    
    // TODO: Update this method with new requirements 
    
    /*
    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    */
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, elec_mail, this_phone, namef, namel;

    //vector<Connection*> c;
    vector<vector<string> > friends;
    


    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        getline(infile, elec_mail);
        getline(infile, this_phone);
        Connection* newEntry = new Connection(fname, lname, bdate, elec_mail, this_phone);
        this->push_back(newEntry);

        //c.push_back(newEntry);
        vector<string> temp;
        getline(infile,buff);

        int nn=0;
        while(buff.compare(0,5,"-----")!=0){
            //temp.clear();
            temp.push_back(buff);
            nn++;
            getline(infile,buff);
            }            
        friends.push_back(temp);
    }


    infile.close();

    Connection* ptr = head;
    int i=0;
    while(ptr!=NULL){
        for(int j=0;j<friends[i].size();j++){
            ptr->makeFriends(search_code(friends[i][j]));
        }
        i++;
        ptr = ptr->next;
    }
}

    



bool Network::remove(string fname, string lname){
    // We modified the definition of == for Connection in Connection definition itself, 
    // So we should not be worried about changes we made in Connection to modify this method!
    // Copy from lab5
    Connection* check = new Connection(fname,lname);
    Connection* ptr;
    Connection* ptr2;

    ptr2 = head;
    while(ptr2!=NULL){
        unsigned int size = ptr2->myfriends.size();
        for (unsigned int i = 0; i < size; i++) {

            if(codeName(ptr2->myfriends[i]->f_name, ptr2->myfriends[i]->l_name) == codeName(fname,lname)){

                ptr2->myfriends.erase(ptr2->myfriends.begin()+i);
            }
        }
        ptr2=ptr2->next;
    }
    delete ptr2;
    


    ptr = search(check);
    if (search(check)!=NULL){
        if(ptr == NULL){
            delete check;
            delete ptr;
            return false;}
        else if(count == 1){
            head = NULL;
            tail = NULL;
        }
        else if(ptr == head){
            (head->next)->prev = NULL;
            head = head->next;   
        }
        else if(ptr == tail){
           (tail->prev)->next = NULL;
           tail = tail->prev;
        }
        else if((ptr!=head)&&(ptr!=tail)){ 
            (ptr->prev)->next = ptr->next;
            (ptr->next)->prev = ptr->prev;
        }
        count--;
        delete check;
        delete ptr;
        return true;
    }




}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
    //??????????????????????????????????????
    
    addr = "\"" + addr + "\"";
    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    attachment = "\"" + attachment + "\"";
    string cmd;
    cmd = "echo " + content + " | mail -s " + subject + " " + addr;
    cout << cmd << endl;
    system(cmd.c_str());
    system("./a.out"); 
    
}

Connection* Network::search_code(string friend_code){
    Connection* ptr = head;
    //cout << "check"<<endl;2
    while(ptr!=NULL){
         if (codeName(ptr->f_name,ptr->l_name)== friend_code){
            return ptr;
         }
         ptr=ptr->next;
         
    }
    return NULL;


}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library
        
        //cout << ("banner") << endl;

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "9. Connect \n";

        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;       //added
            saveDB(fileName);      //added
            
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){   //????????????????
            // TODO: Complete me!
            count = 0;
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format 
            DIR *d;
            char *p1,*p2;
            int ret;
            struct dirent *dir;
            d = opendir(".");
            if (d){
                while ((dir = readdir(d)) != NULL){
                    p1=strtok(dir->d_name,".");
                    p2=strtok(NULL,".");
                    if(p2!=NULL){
                        ret=strcmp(p2,"db");
                        if(ret==0){
                            printf("%s.db\t",p1); 
                        }
                    }
                }
                cout << endl;
                closedir(d);
            }
            
            // Take a look into sample_files.cpp 
            cout << "Enter the name of the load file: "; 
            cin >> fileName;
            if (FILE *file= fopen(fileName.c_str(), "r")){
                loadDB(fileName);
                fclose(file);
                cout << "Network loaded from " << fileName << " with " << count << " connections \n";
            }
            else{
            
            // If file with name FILENAME does not exist: 
                cout << "File " + fileName + " does not exist!" << endl;
            }
            // If file is loaded successfully, also print the count of connections in it: 
            
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            

            Connection *srch = new Connection();
            
            if (search(srch)==NULL){
                 push_front(srch); 
                 cout << "Adding a new connection \n"; //skeleton
            }
            else{
                 cout << "connection already exsists." << endl;
                delete srch;}
            
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Removing a connection \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin,lname);
            // if found, cout << "Remove Successful! \n";
            if (remove(fname, lname)==true){
                 cout << "Remove Successful!\n";
            }
            // if not found: cout << "Connection not found! \n";
            else {
                 cout << "connection not found!\n";
            }
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            getline(cin, fname);
            cout << "Last Name: ";
            getline(cin, lname);
            
            // if found: print connection
            Connection* ptr = search(fname, lname);
            if (ptr != NULL){
                 ptr ->print_connection();
             }
            
            // if not, cout << "Not found! \n";
            else{
                 cout << "Not found!\n";
            }
        }
        else if (opt==6){
            // Note: Completed!
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection* ptr = search(fname, lname);
            if (ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_connection();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else 
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Option currently not available\n";
            
            //osascript -e 'tell application "Messages" to send "Hello World" to "J D McIninch"'
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else if (opt==9){
            cout << "Make friends: \n";
            cout << "Connection 1: \n";
            cout << "First Name: ";
            getline(cin, fname);
            cout << "Last Name: ";
            getline(cin, lname);
            Connection *ptr1 = search(fname,lname);
            if (ptr1 == NULL){
                cout << "Connection not found" << endl;
            }

            else{
                cout << "Connection 2: \n";
                cout << "First Name: ";
                getline(cin, fname);
                cout << "Last Name: ";
                getline(cin, lname);
                Connection* ptr2 = search(fname,lname);
                if (ptr2 == NULL){
                    cout << "Connection not found" << endl;
                }
                else{
                    cout << endl;
                    ptr1->makeFriends(ptr2);
                    ptr2->makeFriends(ptr1);

                    ptr1->print_connection();
                    
                    cout << endl;
                    ptr2->print_connection();
                    
                }
             }


        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}


//http://www.cplusplus.com/reference/vector/vector/erase/
//used for different vector methods