#include <string>
#include <iostream>

using namespace std;

class avl
{
    struct node
    {
        string name;
        long int phone;
        node *left;
        node *right;
        int height;

        node(string &elt, long int &phn, node *l, node *r, int h) : name(elt), phone(phn),  left(l), right(r), height(h)
        {
        }
    };
    node *root;

    void rotateLeft(node *&);
    void rotateRight(node *&);
    void doubleRotateLeft(node *&);
    void doubleRotateRight(node *&);
    int height(node *) const;
    node *findMin(node *) const;
    int max(int, int);
    void balance(node *&);
    node *searchElement(string, node *&);
    void insertElement(string, long int, node *&);
    long int removeElement(string, node *&);
    void print(node *&);

    void suggestElement(string, int, node *&, int*);
    node *locateMatch(string, int, node *&);

public:
    avl();
    void insert(string, long int);
    long int remove(string);
    bool search(string);
    void display();
    void suggest(string);
};

avl::avl()
{
    root = NULL;
}


int avl::max(int a, int b)
{
    return (a > b) ? a : b;
}


void avl::rotateRight(node *&R)
{
    node *k1 = R->left;
    R->left = k1->right;
    k1->right = R;
    R->height = max(height(R->left), height(R->right)) + 1;
    k1->height = max(height(k1->left), R->height) + 1;
    R = k1;
}


void avl::rotateLeft(node *&R)
{
    node *k1 = R->right;
    R->right = k1->left;
    k1->left = R;
    R->height = max(height(R->left), height(R->right)) + 1;
    k1->height = max(R->height, height(k1->right)) + 1;
    R = k1;
}

void avl::doubleRotateLeft(node *&R)
{
    rotateLeft(R->left);
    rotateRight(R);
}

void avl::doubleRotateRight(node *&R)
{
    rotateRight(R->right);
    rotateLeft(R);
}


int avl::height(node *N) const
{
    return (N == NULL) ? -1 : N->height;
}


struct avl::node *avl::findMin(node *N) const
{
    if (N == NULL)
    {
        return NULL;
    }
    else if (N->left == NULL)
    {
        return N;
    }
    return findMin(N->left);
}


void avl::balance(node *&N)
{
    if (N == NULL)
        return;

    if (height(N->left) - height(N->right) == 2)
        if (height(N->left->left) >= height(N->left->right))
            rotateRight(N);
        else
            doubleRotateLeft(N);
    else if (height(N->right) - height(N->left) == 2)
        if (height(N->right->right) >= height(N->right->left))
            rotateLeft(N);
        else
            doubleRotateRight(N);

    N->height = max(height(N->left), height(N->right)) + 1;
}


struct avl::node* avl::searchElement(string x, node *&N)
{
    if (N == NULL || x == N->name)
    {
        return N;
    }
    
    if (x < N->name)
    {
        return searchElement(x, N->left);
    }
    return searchElement(x, N->right);
}

void avl::insertElement(string x, long int phone, node *&N)
{
    if (N == NULL)
    {
        N = new node(x, phone, NULL, NULL, -1);
    }
    else if (x < N->name)
    {
        insertElement(x, phone, N->left);
    }
    else if (x > N->name)
    {
        insertElement(x, phone, N->right);
    }
    else
        ; // No duplicates

    balance(N);
    N->height = max(height(N->left), height(N->right)) + 1;
}

long int avl::removeElement(string x, node *&N)
{
    long int phn = -1;
    if (N == NULL)
        return phn;
    if (x < N->name)
        return removeElement(x, N->left);
    else if (N->name < x)
        return removeElement(x, N->right);
    else if (N->left != NULL && N->right != NULL) // Two children
    {
        N->name = findMin(N->right)->name;
        return removeElement(N->name, N->right);
    }
    else
    {
        node *oldNode = N;
        phn = N->phone;
        N = (N->left != NULL) ? N->left : N->right;
        delete oldNode;
        balance(N);
    }

    return phn;
}

void avl::print(node *&N)
{
    if (N != NULL)
    {
        print(N->left);
        cout << N->name << " : " << N->phone << endl;
        print(N->right);
    }
}

bool avl::search(string x)
{
    node *temp = searchElement(x, root);
    if(temp != NULL){
        return true;
    }
    return false;
}

void avl::insert(string x, long int phone)
{
    insertElement(x, phone, root);
}


long int avl::remove(string x)
{
    return removeElement(x, root);
}


void avl::display()
{
    if (root == NULL)
    {
        cout << "Tree is Empty\n";
        return;
    }
    cout << "\n";
    print(root);
    cout << "\n";
}

struct avl::node* avl::locateMatch(string x, int length, node *&N)
{
    if(N == NULL){
        return N;
    }
    else if (x < N->name.substr(0, length))
    {
        locateMatch(x, length, N->left);
    }
    else if (x > N->name.substr(0, length))
    {
        locateMatch(x, length, N->right);
    }
    return N;
}

void avl::suggestElement(string pattern, int length, node *&N, int *flag)
{
    if (N != NULL)
    {
        suggestElement(pattern, length, N->left, flag);

        if(pattern == N->name.substr(0, length)){
            *flag = 1;
            cout << N->name << " : " << N->phone << endl;
        }

        suggestElement(pattern, length, N->right, flag);
    }
}

void avl::suggest(string pattern)
{
    int size = pattern.size();
    node *match = locateMatch(pattern, size, root);

    int flag = 0;
    suggestElement(pattern, size, match, &flag);

    if(!flag){ // no match found
        cout << "No Results Found" << endl;
    }
    return;
}