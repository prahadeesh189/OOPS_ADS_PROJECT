#include<iostream>
#include<string>

using namespace std;

#include "./contactBook.cpp"

int main() {

    long int kee;
    string name;
    int choice;

    // start
    splayClone();
    avlClone();

    while (true) {

        cout << "\n****** MENU ******\n1 - Add New Contact\n2 - Delete Contact\n3 - Get Info\n4 - Search Names\n5 - All Contacts\n6 - Search Timeline\n";
        cout << "\nChoice: ";
        cin >> choice; 

        switch (choice) {
            case 1:
                cout << "\n--- New Contact ---" << endl;
                CreateNewContact();
                contactSplTree.preOrderWriteWrapper();
                break;
            case 2:
                cout << "Enter the Name of the Contact to be deleted: ";
                cin >> name;
                kee = alphabets[name.at(0) - 65].remove(name);
                deleteContact(kee);
                break;
            case 3:
                while(1){
                    int no;
                    cout << "Enter pattern to search names: ";
                    cin >> name;
                    cout << endl << "*************" << endl;
                    alphabets[name.at(0) - 65].suggest(name);
                    cout << "*************" << endl << endl;

                    while(1){
                        cout << "Enter 0 to exit from autosuggestion, 1 to continue search" << endl;
                        cout << "Enter option: ";
                        cin >> no;
                        if(no == 0 || no == 1){
                            cout << endl;
                            break;
                        }
                        else{
                            cout << "Enter valid option" << endl;
                        }
                        cout << endl;
                    }

                    if(no == 0){
                        break;
                    }

                }
                
                cout << "Enter phone number to view full details of the contact: ";
                cin >> kee;
                getInfo(kee);
                break;
            case 4:
                cout << "Enter pattern to search names: ";
                cin >> name;
                cout << endl << "*************" << endl;
                alphabets[name.at(0) - 65].suggest(name);
                cout << "*************" << endl << endl;
                break;
            case 5:
                cout << "\n------------\n";
                cout << "All Contacts\n";
                contactSplTree.inOrderDisplayWrapper();
                cout << "------------\n";
                break;
            case 6 :
                cout << "\n****** Search Timeline ******\n" << endl;

                contactSplTree.preOrderDisplayWrapper();

                cout << endl;
                break;
            case 0:
                cout << "\n EXITING..." << endl;
                contactSplTree.preOrderWriteWrapper();
                exit(1);
                break;
            default:
                cout << "\n INVALID CHOICE..." << endl;
                break;
        }
    }
    cout << endl;
}