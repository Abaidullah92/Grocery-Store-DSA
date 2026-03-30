#ifndef Grocery_store
#define Grocery_store
#include<iostream>
#include <string>
#include<fstream>

using namespace std;

class GroceryItem {
public:
    string barcode;
    string title;
    double unitPrice;
    int quantityAvailable;

    GroceryItem(string b, string t, double p, int q) {
        barcode = b;
        title = t;
        unitPrice = p;
        quantityAvailable = q;
    }
};

class Customer {
public:
    string CNIC;
    string name;
    string mobileNumber;
    string address;

    Customer(string c, string n, string m, string a) {
        CNIC = c;
        name = n;
        mobileNumber = m;
        address = a;
    }
       
};

// BInary Serch Tree For Customer 
 
class BSTNode {
public:
    Customer customer;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Customer c) : customer(c), left(nullptr), right(nullptr) {}
};


class CustomerBST {

public:
    BSTNode* root;
    CustomerBST() : root(nullptr) {}

    void insert(Customer c) {
        root = insertRec(root, c);
    }

    BSTNode* insertRec(BSTNode* node, Customer c) {
        if (node == nullptr) {
            return new BSTNode(c);
        }
        if (c.CNIC < node->customer.CNIC) {
            node->left = insertRec(node->left, c);
        }
        else {
            node->right = insertRec(node->right, c);
        }
        return node;
    }

    void searchAndDisplay(string cnic) {
        searchRec(root, cnic);
    }

    void searchRec(BSTNode* node, string cnic) {
        if (node == nullptr) {
            cout << "Customer not found!" << endl;
            return;
        }
        cout << "Checking CNIC: " << node->customer.CNIC << endl;
        if (node->customer.CNIC == cnic) {
            cout << "Customer Found: " << node->customer.name << ", " << node->customer.mobileNumber << ", "
                << node->customer.address << endl;
        }
        else if (cnic < node->customer.CNIC) {
            searchRec(node->left, cnic);
        }
        else {
            searchRec(node->right, cnic);
        }
    }

    BSTNode* deleteCustomer(BSTNode* root,  string& CNIC) {
        if (root == nullptr) {
            return root;

        }

        if (CNIC < root->customer.CNIC) {
            root->left = deleteCustomer(root->left, CNIC);
        }
        else if (CNIC > root->customer.CNIC) {
            root->right = deleteCustomer(root->right, CNIC);
        }
        else {
            // Node with one child or no child
            if (root->left == nullptr) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }

            BSTNode* temp = minValueNode(root->right);
            root->customer = temp->customer; // Copy customer data from successor
            root->right = deleteCustomer(root->right, temp->customer.CNIC);
        }
        return root;
    }
    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* temp = node;
        while (temp && temp->left!= nullptr)
            temp = temp->left;
        return temp;
    }

    void display(BSTNode* node) {
        if (node != nullptr) {
            display(node->left);
            cout << "CNIC: " << node->customer.CNIC << ", Name: " << node->customer.name
                 << ", Mobile: " << node->customer.mobileNumber << ", Address: " << node->customer.address << endl;
            display(node->right);
        }
    }
};


// Binary Search Tree for Grocery Items
class GroceryBSTNode {
public:
    GroceryItem grocery;
    GroceryBSTNode* left;
    GroceryBSTNode* right;
    GroceryBSTNode(GroceryItem g) : grocery(g) , left(nullptr) , right(nullptr) {}
};

class GroceryItemBST {
public:
    GroceryBSTNode* root;

    GroceryItemBST() : root(nullptr) {}

    void insert(GroceryItem newItem) {
        root = insertRec(root, newItem);
    }

    GroceryBSTNode* insertRec(GroceryBSTNode* node, GroceryItem newitem) {
        if (node == nullptr) {
            return new GroceryBSTNode(newitem);

        }
        if (newitem.barcode < node->grocery.barcode) {
            node->left = insertRec(root->left, newitem);

        }
        else {
            node->right = insertRec(root->right, newitem);

        }
    
        return node;
    }

    void searchGroceryItems(string Barcode) {
        searchRec(root, Barcode);
    }

    void searchRec(GroceryBSTNode* node, string barcode) {
        if (node == nullptr) {
            cout << "Grocery Item not found!" << endl;
            return;
        }
        cout << "Checking Barcode: " << node->grocery.barcode << endl; 
        if (node->grocery.barcode == barcode) {
            cout << "Grocery Item Found: " << node->grocery.title << ", " << node->grocery.quantityAvailable << ", "
                << node->grocery.unitPrice << endl;
        }
        else if (barcode < node->grocery.barcode) {
            searchRec(node->left, barcode);
        }
        else {
            searchRec(node->right, barcode);
        }
    }


    GroceryBSTNode* deleteItem(GroceryBSTNode* root, string barcode) {
        if (root == nullptr) {
            return root;
        }

        if (barcode < root->grocery.barcode) {
            root->left = deleteItem(root->left, barcode);
        }
        else if (barcode > root->grocery.barcode) {
            root->right = deleteItem(root->right, barcode);
        }
        else {
            // Node with one child or no child
            if (root->left == nullptr) {
                GroceryBSTNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                GroceryBSTNode* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: Get the inorder successor
            GroceryBSTNode* temp = minValueNode(root->right);
            root->grocery = temp->grocery;
            root->right = deleteItem(root->right, temp->grocery.barcode);
        }
        return root;
    }

    GroceryBSTNode* minValueNode(GroceryBSTNode* node) {
        GroceryBSTNode* temp = node;
        while (temp && temp->left != nullptr)
            temp = temp->left;
        return temp;
    }

    void display(GroceryBSTNode* node) {
        if (node != nullptr) {
            display(node->left);
            cout << "Barcode: " << node->grocery.barcode << ", Title: " << node->grocery.title
                << ", Price: " << node->grocery.unitPrice << ", Quantity: " << node->grocery.quantityAvailable << endl;
            display(node->right);
        }
    }
};

// Function to load customers from a file
void loadCustomers(CustomerBST& tree, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string cnic, name, mobile, address;

    while (file >> cnic >> name >> mobile >> address) {
        tree.insert(Customer(cnic, name, mobile, address));
    }
    file.close();
}


// Function to load grocery items from a file
void loadGroceryItems(GroceryItemBST& tree, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string barcode, title;
    double price;
    int quantity;

    while (file >> barcode >> title >> price >> quantity) {
        tree.insert(GroceryItem(barcode, title, price, quantity));
    }


    file.close();
}







#endif // !Grocery_store

