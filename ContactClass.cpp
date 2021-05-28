#include<iostream>
#include<string>
using namespace std;



class Contact {

    string Name;
    long int Number;
    string Address;
    string EmailID;

    public:
        Contact() {};
        ~Contact() {};

        Contact(string name, long int number, string address, string emailID) {
            Name = name;
            Number = number;
            Address = address;
            EmailID = emailID;
        };

        Contact(const Contact &contact ) {
            Name =  contact.Name;
            Number =    contact.Number;
            Address =   contact.Address;
            EmailID =   contact.EmailID;
        };

        friend ostream & operator << (ostream & output, Contact & c);
        friend istream & operator >> (istream & input , Contact & c);


        string toString();
        long int getNumber();
};

Contact toContact(string & line) {

    string index = "", name = "", number = "", address = "", email = "";

    // index
    int i=0;
    for (; i<line.length(); i++) {
        if (line[i] == '|') {
            break;
        }

        index += line[i];
    }
    i++;
    
    // name
    for (; i<line.length(); i++) {
        if (line[i] == '|') {
            break;
        }

        name += line[i];
    }
    i++;

    // number
    for (; i<line.length(); i++) {
        if (line[i] == '|') {
            break;
        }

        number += line[i];
    }
    i++;

    // address
    for (; i<line.length(); i++) {
        if (line[i] == '|') {
            break;
        }

        address += line[i];
    }
    i++;

    // email
    for (; i<line.length(); i++) {
        if (line[i] == '|') {
            break;
        }

        email += line[i];
    }
    i++;



    stringstream string_TO_int_stream;
    int ind;
    string_TO_int_stream << index;
    string_TO_int_stream >> ind;



    stringstream string_TO_int_stream_number;
    long int numb;
    string_TO_int_stream_number << number;
    string_TO_int_stream_number >> numb;




    Contact ct(name, numb, address, email);
    return ct;
}




long int Contact::getNumber() {
    return Number;
}

string Contact::toString() {
    string result = "";
    result = result + Name;
    result = result + "|";

    string Num;
    stringstream int_TO_string_stream;
    int_TO_string_stream << Number;
    int_TO_string_stream >> Num;

    result = result + Num;
    result = result + "|";

    result = result + Address;
    result = result + "|";

    result = result + EmailID;
    result = result + "|\n";







    // long int f = 1234567089;
    // long int h;


    // string s; 

    // stringstream int_TO_string_stream, string_TO_int_stream;  
    // int_TO_string << f;   
    // int_TO_string >> s;


    // cout << s <<endl;

    // string_TO_int << s;
    // string_TO_int >> h;

    // cout << h <<endl;


    return result;
}





ostream & operator << (ostream & output, Contact & c) {

    cout << endl;
    output << "Name:    \t" << c.Name << endl;
    output << "Number:  \t" << c.Number << endl;
    output << "Address: \t" << c.Address << endl;
    output << "EmailID: \t" << c.EmailID << endl;

    return output;
}

istream & operator >> (istream & input, Contact & c) {

    cout << "Name:    \t";
    input >> c.Name;

    cout << "Number:  \t";
    input >> c.Number;

    cout << "Address: \t";
    input >> c.Address;

    cout << "EmailID: \t";
    input >> c.EmailID;
    
    return input;
}



