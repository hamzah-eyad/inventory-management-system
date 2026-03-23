#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Node class represents a single node in the linked list
class Node {
private:
  string name;
  int productID;
  int quantity;
  double price;
  Node *next;

public:
  // Constructor to initialize the node with given values
  Node(string name, int productID, int quantity, double price) {
    this->name = name;
    this->productID = productID;
    this->quantity = quantity;
    this->price = price;
    next = nullptr;
  }

  // Getter and setter functions for private member variables
  void setName(string newName) { name = newName; }
  string getName() { return name; }

  void setProductID(int newProductID) { productID = newProductID; }
  int getProductID() { return productID; }

  void setQuantity(int newQuantity) { quantity = newQuantity; }
  int getQuantity() { return quantity; }

  void setPrice(double newPrice) { price = newPrice; }
  double getPrice() { return price; }

  void setNext(Node *newNext) { next = newNext; }
  Node *getNext() { return next; }
};

// Inventory class manages the linked list of products
class Inventory {
private:
  Node *head;

public:
  // Constructor to initialize an empty inventory
  Inventory() { head = nullptr; }

  // Check if the inventory is empty
  bool isEmpty() { return head == nullptr; }

  // Check if a given product ID is new (not already in the inventory)
  bool isNewId(int id) {
    Node *current = head;
    while (current != nullptr) {
      if (current->getProductID() == id) {
        return false;
      }
      current = current->getNext();
    }
    return true;
  }

  // Check if a product with a given ID is found in the inventory
  bool isFound(int productID) {
    Node *current = head;
    while (current != nullptr) {
      if (current->getProductID() == productID) {
        return true;
      }
      current = current->getNext();
    }
    return false;
  }

  // Add a new product to the inventory
  void addProduct(string name, int productID, int quantity, double price) {
    Node *newNode = new Node(name, productID, quantity, price);

    if (isEmpty()) {
      head = newNode;
    } else {
      Node *current = head;
      while (current->getNext() != nullptr) {
        current = current->getNext();
      }
      current->setNext(newNode);
    }
    cout << "Product added to inventory." << endl << endl;
  }

  // Remove a product from the inventory based on its product ID
  void removeProduct(int productID) {
    if (head->getProductID() == productID) {
      Node *temp = head;
      head = head->getNext();
      delete temp;
      cout << "Product has been removed from inventory." << endl << endl;
      return;
    }

    Node *current = head;
    while (current->getNext() != nullptr) {
      if (current->getNext()->getProductID() == productID) {
        Node *temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
        cout << "Product has been removed from inventory." << endl << endl;
        return;
      }
      current = current->getNext();
    }

    cout << "Product was not found in inventory." << endl << endl;
  }

  // Update the quantity and price of a product in the inventory
  void updateProduct(int productID, int newQuantity, double newPrice) {
    Node *current = head;
    while (current != nullptr) {
      if (current->getProductID() == productID) {
        current->setQuantity(newQuantity);
        current->setPrice(newPrice);
        cout << "\nProduct has been updated." << endl << endl;
        return;
      }
      current = current->getNext();
    }
    cout << "Product was not found in inventory." << endl << endl;
  }

  // Display the current state of the inventory
  void displayInventory() {
    if (isEmpty()) {
      cout << "Inventory is empty." << endl << endl;
      return;
    }

    cout << "\t\t\t**Inventory**" << endl << endl;

    Node *current = head;
    cout << "Name\t|\tID\t|\tQuantity\t|\tPrice\n\n\n";
    while (current != nullptr) {
      cout << current->getName() << "\t|\t" << current->getProductID()
           << "\t|\t" << current->getQuantity() << "\t\t|\t"
           << current->getPrice() << endl;
      current = current->getNext();
    }
  }
};

int main() {
  Inventory inventory;
  char choice;

  // Display a welcome message
  system("cls");
  cout << "\n\n\n\n\n\t\t\t\t Welcome To Inventory Management "
          "System\n\n\t\t\t\t\tPress Enter to continue.";
  cin.get();

  do {
    // Display the menu
    system("cls");
    cout << "------------------------" << endl;
    cout << "\n         Menu:" << endl;
    cout << "\n1. Add a product" << endl;
    cout << "2. Remove a product" << endl;
    cout << "3. Update a product" << endl;
    cout << "4. Display inventory" << endl;
    cout << "5. Exit" << endl;
    cout << "\nEnter your choice: ";
    cin >> choice;
    cout << endl;
    system("cls");

    // Perform the chosen operation based on user input
    switch (choice) {
    case '1': {
      // Add a new product
      int num;
      string name;
      int productID, quantity;
      double price;
      cout << "\t--add a product--\n\n";
      cout << "How many products would you like to add? ";
      cin >> num;
      for (int i = 0; i < num; i++) {
        cout << "\nEnter product '" << i + 1 << "' name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter product ID: ";
        cin >> productID;
        while (!inventory.isNewId(productID)) {
          cout << "Product ID already exists. Please enter a new ID: ";
          cin >> productID;
        }
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: ";
        cin >> price;
        inventory.addProduct(name, productID, quantity, price);
      }
      cout << "\t\t\t\t \nPress Enter to continue  \n";
      cin.ignore();
      cin.get();
      system("cls");

      break;
    }
    case '2': {
      // Remove a product
      int productID;
      cout << "\t--remove a product--\n\n";
      if (inventory.isEmpty()) {
        cout << "Inventory is empty." << endl << endl;
        cout << "\t\t\t\t \nPress Enter to continue  \n";
        cin.ignore();
        cin.get();
        system("cls");
        break;
      }
      cout << "Enter product ID to remove: ";
      cin >> productID;
      inventory.removeProduct(productID);
      cout << "\t\t\t\t \nPress Enter to continue  \n";
      cin.ignore();
      cin.get();
      system("cls");
      break;
    }
    case '3': {
      // Update a product
      int productID, newQuantity;
      double newPrice;
      cout << "\t--update a product--\n\n";
      cout << "Enter product ID to update: ";
      cin >> productID;
      if (inventory.isFound(productID)) {
        cout << "\nEnter new quantity: ";
        cin >> newQuantity;
        cout << "Enter new price: ";
        cin >> newPrice;
        inventory.updateProduct(productID, newQuantity, newPrice);
        cout << "\t\t\t\t \nPress Enter to continue  \n";
        cin.ignore();
        cin.get();
        system("cls");
      } else {
        cout << "\nProduct not found!" << endl;
        cout << "\t\t\t\t \nPress Enter to continue  \n";
        cin.ignore();
        cin.get();
        system("cls");
      }
      break;
    }
    case '4': {
      // Display the inventory
      inventory.displayInventory();
      cout << "\t\t\t\t \nPress Enter to continue  \n";
      cin.ignore();
      cin.get();
      system("cls");
      break;
    }
    case '5': {
      // Exit the program
      cout << "Exiting program." << endl;
      cout << "\t\t\t\t \nPress Enter to continue  \n";
      cin.ignore();
      cin.get();
      system("cls");
      break;
    }
    default: {
      // Invalid choice
      cin.ignore();
      cout << "Invalid choice. Please try again." << endl;
      cout << "\t\t\t\t \nPress Enter to continue  \n";
      cin.ignore();
      cin.get();
      system("cls");
      break;
    }
    }

  } while (choice != 5);

  return 0;
}