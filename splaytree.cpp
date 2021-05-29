#include<iostream>
using namespace std;

#include "./file.cpp"
#include "./ContactClass.cpp"

typedef struct Node {
    long int key;
    int value;
    Node * left;
    Node * right;
}Node;

class SplayTree {
    
    void preOrder(Node * &root);
    void inOrder(Node * &root);
    void postOrder(Node * &root);
    void display(Node * &root);
    void cloneInsert(Node * &root , long int key, int value);
    void delArrangeKey(Node * & root, int value);
    void preOrderWrite(Node * &root);
    void inOrderDisplay(Node * &root);
    void preOrderDisplay(Node * &root);

    Node * root;   

    public:   
        SplayTree();
        
        void insert(long int key, int value);
        int del( long int key);

        void preOrderWrapper();
        void inOrderWrapper();
        void postOrderWrapper();
        void splay(Node * &root, long int key);
        void zig(Node * &node);
        void zag(Node * &node);
        void displayWrapper();
        void clone(long int key, int value);

        void preOrderWriteWrapper();
        void inOrderDisplayWrapper();
        void preOrderDisplayWrapper();

        Node search(long int key);
};

Node SplayTree::search(long int key) {
    splay( root, key );

    if (key == root->key) {
        return *root;
    }

    Node none;
    none.key = none.value = -1;
    none.left = none.right = NULL;
    return none;
}

void SplayTree::preOrderWrite(Node * &root) {
    if (root != NULL) {  
        ofstream fout_splayHistory;
        fout_splayHistory.open ( splayHistoryPath , std::ios::app);
        fout_splayHistory << root->key << "|" << root->value << endl;
        fout_splayHistory.close();

        preOrderWrite(root->left);
        preOrderWrite(root->right);
    }
}

void SplayTree::preOrderWriteWrapper() {
    ofstream fout_splayHistory;
    fout_splayHistory.open ( splayHistoryPath , std::ios::trunc);
    fout_splayHistory << "";
    fout_splayHistory.close();

    preOrderWrite(root);
}

void SplayTree::inOrderDisplay(Node * &root) {
    if (root != NULL) {
        inOrderDisplay(root->left);
        
            
        ifstream fin_Data;
        fin_Data.open( dataDBPath , ios::app );

        string line;
        for(int i = 0;i < root->value; i++){
            getline(fin_Data, line, '\n');
        }
        Contact contct = toContact(line);
        cout << contct;
        
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


void SplayTree::preOrderDisplay(Node * &root) {
    if (root != NULL) {       
            
        ifstream fin_Data;
        fin_Data.open( dataDBPath , ios::app );

        string line;
        for(int i = 0;i < root->value; i++){
            getline(fin_Data, line, '\n');
        }
        Contact contct = toContact(line);
        cout << contct;
        
        fin_Data.close();


        preOrderDisplay(root->left);
        preOrderDisplay(root->right);
    }
}

void SplayTree::preOrderDisplayWrapper() {
    if (root == NULL) {
        cout << "\n Tree is Empty \n";
    }

    preOrderDisplay(root);
}






























SplayTree::SplayTree() {
    root = NULL;
}

void SplayTree::zig(Node * &node) {
    Node * nodeLeft = node->left;
    node->left = nodeLeft->right;
    nodeLeft->right = node;
    node = nodeLeft;
}

void SplayTree::zag(Node * &node) {
    Node * nodeRight = node->right;
    node->right = nodeRight->left;
    nodeRight->left = node;
    node = nodeRight;
}

void SplayTree::cloneInsert(Node * & root, long int key, int value) {

    if (root == NULL) {
        root = new Node();
        root->key = key;
        root->value = value;
        root->left = root->right = NULL;
        return;
    }

    if (key < root->key) {
        cloneInsert( root->left , key, value);
    }
    else if (key > root->key) {
        cloneInsert( root->right , key, value);
    }
}

void SplayTree::clone(long int key, int value) {
    cloneInsert(root, key, value);
}

void SplayTree::splay(Node * &root, long int key) {

    if (root == NULL || root->key == key) {
        return;
    }


    if (key < root->key) {
        if (root->left == NULL) {
            return;
        }

        if (key < root->left->key) {

            splay( root->left->left , key);

            zig(root);
            if (root->left == NULL)
                return;
            zig(root);
            return;
        }
        else {

            splay( root->left->right , key);

            if (root->left->right != NULL) {
                zag(root->left);
            }
            if (root->left == NULL)
                return;            
            zig(root);
            return;
        }
    }
    else if (key > root->key) {
        if (root->right == NULL) {
            return;
        }

        if (key > root->right->key) {

            splay( root->right->right , key);

            zag(root);
            if (root->right == NULL) 
                return;
            zag(root);
            return;
        }
        else {
            

            splay( root->right->left , key);

            if (root->right->left != NULL) {
                zig(root->right);
            }
            if (root->right == NULL) 
                return;

            zag(root);
            return;
        }
    }
}

void SplayTree::insert(long int key, int value) {


    if (root == NULL) {
        root = new Node();
        root->key = key;
        root->value = value;
        root->left = root->right = NULL;
        return;
    }


    splay( root , key);

    if (root->key == key) {
        return;
    }

    Node * insertNode = new Node();
    insertNode->key = key;
    insertNode->value = value;


    if (key < root->key) {
        insertNode->right = root;
        insertNode->left = root->left;
        root->left = NULL;
    }
    else {
        insertNode->left = root;
        insertNode->right = root->right;
        root->right = NULL;
    }

    root = insertNode;
    return;
}

void SplayTree::delArrangeKey(Node * & root, int value) {
    if (root != NULL) {
 

        if (root->value > value) {
            root->value--;
        }

        delArrangeKey( root->left  , value ); 
        delArrangeKey( root->right , value );
    }
}

int SplayTree::del(long int key) {
    if (root == NULL) {
        return 0;
    }

    int tempValue;
    Node * temp, * temp2; 
    splay(root , key);

    if (key != root->key){
        return 0;
    }
    else {

        if ( root->left == NULL ) {
            temp = root;
            temp2 = root->right;
        }
        else {
            temp = root;
            temp2 = root->left;
            splay(temp2 , key);

            temp2->right = temp->right;   
        }

        tempValue = temp->value;
        delete temp;
        root = temp2;  

        delArrangeKey( root , tempValue ); 
        return 1;
    }
}

void SplayTree::display(Node * &root) {

    if (root != NULL) {

        if (root->left == NULL && root->right == NULL) {
            cout << root->key << " -> "<< root->value << "\t\t" << "L:" << "NULL" << "\t\t" << "R:" << "NULL" <<endl;
        }
        else if (root->left != NULL && root->right == NULL) {
            cout << root->key << " -> "<< root->value << "\t\t" << "L:" << root->left->key << "\t\t" << "R:" << "NULL"<<endl;
        }
        else if (root->left == NULL && root->right != NULL) {
            cout << root->key << " -> "<< root->value << "\t\t" << "L:" << "NULL" << "\t\t" << "R:" << root->right->key<<endl;
        }
        else if (root->left != NULL && root->right != NULL) {
            cout << root->key << " -> "<< root->value << "\t\t" << "L:" << root->left->key << "\t\t" << "R:" << root->right->key<<endl;
        }


        display(root->left);
        display(root->right);
    }
}

void SplayTree::displayWrapper() {

    if (root == NULL) {
        cout << "\n Tree is Empty \n";
    }

    display(root);
}

void SplayTree::preOrder(Node * &root) {
    if (root != NULL) {
        cout<< root->key << endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

void SplayTree::preOrderWrapper() {
    preOrder(root);
    cout << endl;
}

void SplayTree::postOrder(Node * &root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout<< root->key << endl;
    }
}

void SplayTree::postOrderWrapper() {
    postOrder(root);
    cout << endl;
}

void SplayTree::inOrder(Node * &root) {
    if (root != NULL) {
        inOrder(root->left);
        cout<< root->key << endl;
        inOrder(root->right);
    }
}

void SplayTree::inOrderWrapper() {
    inOrder(root);
    cout << endl;
}

