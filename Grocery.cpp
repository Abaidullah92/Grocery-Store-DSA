#include "Grocery.h"
#include "Graph.h"
int main() {
    CustomerBST customerTree;
    GroceryItemBST groceryTree;

    // Load customers and grocery items from files
    loadCustomers(customerTree, "d:\\customer.txt");
    loadGroceryItems(groceryTree, "d:\\Grocery.txt");

    // Create a graph with 10 vertices (representing a simple map with 10 locations)
    Graph deliveryGraph(10);

    // Insert edges between various locations (store and customer addresses)
    deliveryGraph.insertEdge(0, 1);  // Store to Customer 1
    deliveryGraph.insertEdge(1, 2);  // Customer 1 to Customer 2
    deliveryGraph.insertEdge(2, 3);  // Customer 2 to Customer 3
    deliveryGraph.insertEdge(3, 4);  // Customer 3 to Customer 4
    deliveryGraph.insertEdge(4, 5);  // Customer 4 to Customer 5
    deliveryGraph.insertEdge(0, 6);  // Store to Customer 6
    deliveryGraph.insertEdge(6, 7);  // Customer 6 to Customer 7
    deliveryGraph.insertEdge(7, 8);  // Customer 7 to Customer 8
    deliveryGraph.insertEdge(8, 9);  // Customer 8 to Customer 9


    int choice;
    do {
        cout << "\n--- Grocery Store Management System ---" << endl;
        cout << "1. Add a Customer" << endl;
        cout << "2. Add a Grocery Item" << endl;
        cout << "3. Search for a Customer" << endl;
        cout << "4. Search for a Grocery Item" << endl;
        cout << "5. Delete a Customer" << endl;
        cout << "6. Delete a Grocery Item" << endl;
        cout << "7. Display All Customers" << endl;
        cout << "8. Display All Grocery Items" << endl;
        cout << "9. Deliver Order (Find shortest path for delivery)" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add a new customer
            string cnic, name, mobile, address;
            cout << "Enter CNIC: ";
            cin >> cnic;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Mobile: ";
            cin >> mobile;
            cout << "Enter Address: ";
            cin >> address;
            customerTree.insert(Customer(cnic, name, mobile, address));
            cout << "Customer added successfully!" << endl;
            break;
        }
        case 2: {
            // Add a new grocery item
            string barcode, title;
            double price;
            int quantity;
            cout << "Enter Barcode: ";
            cin >> barcode;
            cout << "Enter Title: ";
            cin >> title;
            cout << "Enter Unit Price: ";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> quantity;
            groceryTree.insert(GroceryItem(barcode, title, price, quantity));
            cout << "Grocery item added successfully!" << endl;
            break;
        }
        case 3: {
            // Search for a customer
            string cnic;
            cout << "Enter CNIC to search: ";
            cin >> cnic;
            customerTree.searchAndDisplay(cnic);
            break;
        }
        case 4: {
            // Search for a grocery item
            string barcode;
            cout << "Enter Barcode to search: ";
            cin >> barcode;
            groceryTree.searchGroceryItems(barcode);
            break;
        }
        case 5: {
            // Delete a customer
            string cnic;
            cout << "Enter CNIC to delete: ";
            cin >> cnic;
            customerTree.deleteCustomer(customerTree.root, cnic);
            cout << "Customer deleted successfully!" << endl;
            break;
        }
        case 6: {
            // Delete a grocery item
            string barcode;
            cout << "Enter Barcode to delete: ";
            cin >> barcode;
            groceryTree.deleteItem(groceryTree.root, barcode);
            cout << "Grocery item deleted successfully!" << endl;
            break;
        }
        case 7: {
            // Display all customers
            cout << "All Customers:" << endl;
            customerTree.display(customerTree.root);
            break;
        }
        case 8: {
            // Display all grocery items
            cout << "All Grocery Items:" << endl;
            if (groceryTree.root == nullptr) {
                cout << "No grocery items to display." << endl;
            }
            else {
                groceryTree.display(groceryTree.root);
            }

            break;
        }
        case 9:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        case 10:{
            // Deliver an order (find the shortest path from the store to the customer)
            int customerIndex;
            cout << "Enter the customer number (0-9) to deliver to: ";
            cin >> customerIndex;

            // Ensure the index is valid
            if (customerIndex >= 0 && customerIndex < 10) {
                cout << "Delivering order to customer " << customerIndex << "..." << endl;
                deliveryGraph.bfsShortestPath(0, customerIndex);  // Start from store (vertex 0)
            }
            else {
                cout << "Invalid customer number!" << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
