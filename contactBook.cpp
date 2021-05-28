// #include<iostream>
#include<string>
#include<sstream> 
#include<fstream>
using namespace std;

#include "splaytree.cpp"
// #include "./file.cpp"
#include "./ContactClass.cpp"






SplayTree contactSplTree;






void getInfo(long int num) {

    Node searchResult =  contactSplTree.search( num );
    // cout << searchResult.key << "  " << searchResult.value << endl;

    if ((searchResult.value == -1) && (searchResult.key == -1)) {
        cout << "\nContact does not exists..." << endl;
        return;
    }



    
    ifstream fin_Data;
    fin_Data.open( dataDBPath , ios::app );
    
    while (fin_Data.eof() == false) {
        string line;
        fin_Data >> line;

        if (line.length() != 0) {

            for (int i = 0; i < (searchResult.value - 1); i++) {
                fin_Data >> line;
            }
            
            Contact contct = toContact(line);
            cout << contct;

            break;
        }   
    }
    
    fin_Data.close();
}



void CreateNewContact();
void deleteContact( long int numberDel);
void clone() {
    
    
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

void allContacts() {

}




void SplayTree::inOrderDisplay(Node * &root) {
    if (root != NULL) {
        inOrderDisplay(root->left);
        
            
        ifstream fin_Data;
        fin_Data.open( dataDBPath , ios::app );
        
        while (fin_Data.eof() == false) {
            string line;
            fin_Data >> line;

            if (line.length() != 0) {

                for (int i = 0; i < (root->value - 1); i++) {
                    fin_Data >> line;
                }
                
                Contact contct = toContact(line);
                cout << contct;

                break;
            }   
        }
        
        fin_Data.close();

        inOrderDisplay(root->right);
    }
}

void SplayTree::inOrderDisplayWrapper() {
    if (root == NULL) {
        cout << "\n Tree is Empty \n";
    }

    inOrderDisplay(root);
}













int main() {

    long int kee;
    int choice;

    // start
    clone();



    while (true) {

        cout << "\n****** MENU ******\n1 - Add New Contact\n2 - Delete Contact\n3 - Get Info\n4 - All Contacts\n";
        cout << "\nchoice: ";
        cin >> choice; 

        switch (choice) {
            case 1:
                cout << "\n--- New Contact ---" << endl;
                CreateNewContact();
                contactSplTree.preOrderWriteWrapper();
                break;
            case 2:
                cout << "Enter Delete Number: ";
                cin >> kee;
                deleteContact(kee);
                break;
            case 3:
                cout << "Enter Number: ";
                cin >> kee;
                getInfo(kee);
                break;
            case 4:
                cout << "\n------------\n";
                cout << "\nAll Contacts\n";
                // contactSplTree.inOrderWrapper();
                contactSplTree.inOrderDisplayWrapper();

                cout << "------------\n";
                break;
            case 5:
                cout << "\n------------\n";
                contactSplTree.displayWrapper();
                cout << "------------\n";
                
                break;
            case 0:
                cout << "\n EXITING..." << endl;
                // end
                contactSplTree.preOrderWriteWrapper();

                exit(1);
                break;
            
            default:
                cout << "\n INVALID CHOICE..." << endl;
                break;
        }
    }





















    // CreateNewContact();     cout << endl;
    // CreateNewContact();     cout << endl;
    // CreateNewContact();     cout << endl;
    // CreateNewContact();     cout << endl;
    // CreateNewContact();     cout << endl;
    // CreateNewContact();     cout << endl;
    // CreateNewContact();     cout << endl;



    // contactSplTree.displayWrapper();


    // contactSplTree.insert( 1234567001, 1);
    // contactSplTree.insert( 1234567002, 2);
    // contactSplTree.insert( 1234567003, 3);
    // contactSplTree.insert( 1234567004, 4);
    // contactSplTree.insert( 1234567005, 5);
    // contactSplTree.insert( 1234567006, 6);
    // contactSplTree.insert( 1234567007, 7);


    // Contact newContact1,  newContact1, newContact1, newContact1, newContact1, newContact1, newContact1, 




    // contactSplTree.displayWrapper();
    // cout << "\n\n\n";


    // contactSplTree.del(123456784);





    // contactSplTree.displayWrapper();
    // cout << "\n\n\n";




    // clone();



    // contactSplTree.clone( 1234567004, 4 );
    // contactSplTree.clone( 1234567002, 2 );
    // contactSplTree.clone( 1234567006, 6 );
    // contactSplTree.clone( 1234567001, 1 );
    // contactSplTree.clone( 1234567003, 3 );
    // contactSplTree.clone( 1234567005, 5 );
    // contactSplTree.clone( 1234567007, 7 );


    // contactSplTree.displayWrapper();
    
    // deleteContact(1234567004);
    // cout << "\n\n\n";
    
    // contactSplTree.displayWrapper();
    

    // cout << "\n\n\n";


    // getInfo(1234567004);




    // cout << "\n\n\n";

    // contactSplTree.displayWrapper();



    // contactSplTree.preOrderWriteWrapper();

    // cout << "\n\n\n";










    







    cout << endl;
}












// 1|dsh|1234567001|dfce|sdc|
// 2|sdfre|1234567002|sdfe|sede|
// 3|esfdre|1234567003|sdfre|aedw|
// 4|sdf|1234567004|efrf|esd|
// 5|aefre|1234567005|edfce|sedew|
// 6|eaffwed|1234567006|edf|edwfwr|
// 7|sefe|1234567007|edff|sed|


































void CreateNewContact() {
    Contact newContact;
    cin >> newContact;



    ifstream fin_metaData;
    fin_metaData.open ( metaDataDBPath ,ios::app);

    int count;
    fin_metaData >> count;
    fin_metaData.close();


    string index;

    stringstream int_TO_string_stream;
    int_TO_string_stream << count+1;   
    int_TO_string_stream >> index;

    string dataString = "";
    dataString += index;
    dataString += "|";
    dataString += newContact.toString();




    ofstream fout_data;
    fout_data.open ( dataDBPath , ios::app);
    fout_data << dataString;
    fout_data.close();




    ofstream fout_metaData;
    fout_metaData.open ( metaDataDBPath , std::ios::trunc);
        
    fout_metaData << count+1;
    fout_metaData.close();



    contactSplTree.insert( newContact.getNumber() , count+1 );

    cout << "\nNew Contact Addedd Successfully\n";
};


void deleteContact( long int numberDel) {

    int rslt =  contactSplTree.del(numberDel);

    if (rslt != 1) {
        cout << "\nContact does not exists...\n";
        return;
    }


    ifstream fin_Data;
    fin_Data.open( dataDBPath , ios::app );
    

    ofstream fout_tempData;
    fout_tempData.open ( tempDataDBPath , std::ios::trunc);
    

    
    bool afterFlag = false;

    while (fin_Data.eof() == false) {
        string line;
        fin_Data >> line;




        if (line.length() != 0) {
            

            string inde = "", number = "";
    
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
        fin_tempData >> line;

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




