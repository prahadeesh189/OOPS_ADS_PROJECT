#include<iostream>
#include<string>
#include<sstream> 
#include<fstream>

using namespace std;

#include "./splaytree.cpp"
#include "./avlTree.cpp"

SplayTree contactSplTree;
avl alphabets[26];

void splayClone() {
        
    ifstream fin_splayHistory;
    fin_splayHistory.open ( splayHistoryPath , std::ios::app);

    while (fin_splayHistory.eof() == false) {
        string line;
        fin_splayHistory >> line;

        if (line.length() != 0) {

            string key = "", value = "";

            int i=0;

            // key
            for (; i<line.length() ; i++) {
                if (line[i] == '|') {
                    break;
                }

                key += line[i];                
            }
            i++;

            // value
            for (; i<line.length() ; i++) {
                if (line[i] == '\n') {
                    break;
                }

                value += line[i];                
            }

            long int k;
            int val;

            stringstream  string_TO_int_stream_key;  
            string_TO_int_stream_key << key;
            string_TO_int_stream_key >> k;


            stringstream  string_TO_int_stream_val;  
            string_TO_int_stream_val << value;
            string_TO_int_stream_val >> val;


            contactSplTree.clone( k, val );
        }
    }

    fin_splayHistory.close();
}

void avlClone(){
    for(int i = 0;i < 26;i++){
        avl a;
        alphabets[i] = a;
    }

    char i;
    long int phone;

    ifstream fin_Data;
    fin_Data.open( dataDBPath , ios::app );

    string line;
    while(fin_Data.eof() == false){
        getline(fin_Data, line, '\n');

        if(line.length() == 0){
            break;
        }

        Contact contct = toContact(line);
        string name = contct.getName(); 
        phone = contct.getNumber(); 
        alphabets[name.at(0) - 65].insert(name, phone);
    }

    fin_Data.close();

    return;
}

void getInfo(long int num) {

    Node searchResult =  contactSplTree.search( num );

    if ((searchResult.value == -1) && (searchResult.key == -1)) {
        cout << "\nContact does not exist..." << endl;
        return;
    }
    
    ifstream fin_Data;
    fin_Data.open( dataDBPath , ios::app );

    string line;
    for(int i = 0;i < searchResult.value; i++){
        getline(fin_Data, line, '\n');
    }
    Contact contct = toContact(line);
    cout << contct;
    
    fin_Data.close();
}

void deleteContact( long int numberDel) {

    int rslt =  contactSplTree.del(numberDel);

    if (rslt != 1) {
        cout << "\nContact does not exist...\n";
        return;
    }

    ifstream fin_Data;
    fin_Data.open( dataDBPath , ios::app );

    ofstream fout_tempData;
    fout_tempData.open ( tempDataDBPath , std::ios::trunc);
    
    bool afterFlag = false;

    while (fin_Data.eof() == false) {
        string line;
        getline(fin_Data , line);
        // cout << line << endl;

        if (line.length() != 0) {
            

            string inde = "", number = "", name = "";
    
            // index
            int i=0;
            for (; i<line.length(); i++) {
                if (line[i] == '|') {
                    break;
                }

                inde += line[i];
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

            stringstream string_TO_int_stream;
            int ind;
            string_TO_int_stream << inde;
            string_TO_int_stream >> ind;

            stringstream string_TO_int_stream_number;
            long int numb;
            string_TO_int_stream_number << number;
            string_TO_int_stream_number >> numb;

            if (numb == numberDel ) {
                afterFlag  = true;
                alphabets[name.at(0) - 65].remove(name);
                continue;
            }

            if (afterFlag != 1) {
                fout_tempData << line << "\n";

            }
            else {
                string stringIndex = "";

                // index
                int i=0;
                for (; i<line.length(); i++) {
                    if (line[i] == '|') {
                        break;
                    }

                    stringIndex += line[i];
                }
                i++;

                stringstream string_TO_int_stream_ind;
                int index_1;
                string_TO_int_stream_ind << stringIndex;
                string_TO_int_stream_ind >> index_1;
                index_1--;

                string ind_string;

                stringstream int_TO_string_stream;  
                int_TO_string_stream << index_1;   
                int_TO_string_stream >> ind_string;

                Contact ctp = toContact(line);

                string dtLine = "";

                dtLine += ind_string;
                dtLine += "|";
                dtLine += ctp.toString();

                fout_tempData << dtLine;
            }
        }
    };


    fout_tempData.close();
    fin_Data.close();

    ofstream fout_Data;
    fout_Data.open( dataDBPath , std::ios::trunc );

    ifstream fin_tempData;
    fin_tempData.open ( tempDataDBPath , ios::app);

    while (fin_tempData.eof() == false) {
        string line;
        getline(fin_tempData , line);

        if (line.length() != 0) {
            fout_Data << line << endl;
        }
    }

    fin_tempData.close();
    fout_Data.close();

    ifstream fin_metaData;
    fin_metaData.open ( metaDataDBPath ,ios::app);

    int count;
    fin_metaData >> count;
    fin_metaData.close();


    ofstream fout_metaData;
    fout_metaData.open ( metaDataDBPath , std::ios::trunc);
        
    fout_metaData << count-1;
    fout_metaData.close();
}

void CreateNewContact() {
    Contact newContact;
    cin >> newContact; // get details from the user

    if(alphabets[newContact.getName().at(0) - 65].search(newContact.getName()) == true){
        cout << endl << "******Contact Name already exists ******" << endl;
        return;
    }

    ifstream fin_metaData;
    fin_metaData.open ( metaDataDBPath ,ios::app);

    int count;
    fin_metaData >> count; // get current count of the contacts
    fin_metaData.close();

    string index;
    stringstream int_TO_string_stream;
    int_TO_string_stream << count+1;   
    int_TO_string_stream >> index;

    string dataString = "";
    dataString += index;
    dataString += "|";
    dataString += newContact.toString();

    ofstream fout_data; // add new contact to the file
    fout_data.open ( dataDBPath , ios::app);
    fout_data << dataString;
    fout_data.close();

    ofstream fout_metaData; // update the current count of the contacts
    fout_metaData.open ( metaDataDBPath , std::ios::trunc);
    fout_metaData << count+1;
    fout_metaData.close();

    // Add the contact to the splay tree
    contactSplTree.insert( newContact.getNumber() , count+1 );

    // Add the name to the avl tree
    alphabets[newContact.getName().at(0) - 65].insert(newContact.getName() ,newContact.getNumber());

    cout << "\nNew Contact Added Successfully\n";
};
