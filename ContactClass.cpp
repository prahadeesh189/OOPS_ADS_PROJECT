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
        string getName();
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

string Contact::getName() {
    return Name;
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

    getchar();
    while(1){
        cout << "Name:    \t";
        getline(input, c.Name, '\n');

        if(c.Name.at(0) >= 65 && c.Name.at(0) <= 90){
            break;
        }
        else{
            cout << "First letter of the name must be capital, No symbols/numbers allowed";
            cout << endl;
        }
    }

    while(1){
        cout << "Number:  \t";
        input >> c.Number;
        //Valid phone numbers is of digits 7 to 15 acccording to international standards
        if(c.Number >= 1000000 && c.Number <= 999999999999999){
            break;
        }
        else{
            cout << "Enter a valid phone number" << endl;
        }
    }

    cout << "Address: \t";
    getchar();
    getline(input, c.Address, '\n');

    cout << "EmailID: \t";
    input >> c.EmailID;
    
    return input;
}



