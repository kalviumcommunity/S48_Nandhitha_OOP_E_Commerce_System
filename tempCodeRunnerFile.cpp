#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Item {
private:
    string name;
    double price;
    int quantity;

public:
    Item(string itemName, double itemPrice, int itemQuantity)
        : name(itemName), price(itemPrice), quantity(itemQuantity) {}

    string getName() const {
        return this->name;
    }

    double getPrice() const {
        return this->price;
    }

    int getQuantity() const {
        return this->quantity;
    }

    double getTotalPrice() const {
        return this->price * this->quantity;
    }
};

class Cart {
private:
    vector<Item*> items; 

public:
    ~Cart() {
        for (Item* item : items) {
            delete item;
        }
    }

    void addItem(Item* item) {
        this->items.push_back(item);
    }

    void removeItem(const string& itemName) {
        for (auto it = items.begin(); it != items.end(); ) {
            if ((*it)->getName() == itemName) {
                delete *it;  
                it = items.erase(it);  
            } else {
                ++it;
            }
        }
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : this->items) { 
            total += item->getTotalPrice();
        }
        return total;
    }

    const vector<Item*>& getItems() const {
        return this->items;
    }
};

class Bill {
private:
    Cart* cart;

public:
    Bill(Cart* cart) : cart(cart) {}

    void generateBill() const {
        cout << "----- Grocery Bill -----\n";
        for (const auto& item : this->cart->getItems()) { 
            cout << item->getName() << " - " << item->getQuantity()
                 << " x Rs" << fixed << setprecision(2)
                 << item->getPrice() << " = Rs" << item->getTotalPrice() << "\n";
        }
        cout << "------------------------\n";
        cout << "Total Amount: Rs" << fixed << setprecision(2)
             << this->cart->getTotalAmount() << "\n";
        cout << "------------------------\n";
    }
};

int main() {
    Item* items[] = {
        new Item("Apples", 50.0, 0),
        new Item("Bananas", 30.0, 0),
        new Item("Milk", 150.0, 0),
        new Item("Bread", 40.0, 0),
        new Item("Cheese", 200.0, 0),
        new Item("Eggs", 10.0, 0),
        new Item("Butter", 80.0, 0),
        new Item("Rice", 60.0, 0),
        new Item("Pasta", 120.0, 0),
        new Item("Carrots", 40.0, 0)
    };

    int numItems = sizeof(items) / sizeof(items[0]);
    Cart* cart = new Cart();
    int choice;
    int quantity;

    while (true) {
        cout << "Select an action:\n";
        cout << "1. Add an item to the cart\n";
        cout << "2. Remove an item from the cart\n";
        cout << (numItems + 1) << ". Checkout and Generate Bill\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == numItems + 1) {
            break;
        }

        if (choice == 1) {
            cout << "Select an item to add to the cart:\n";
            for (int i = 0; i < numItems; ++i) {
                cout << (i + 1) << ". " << items[i]->getName() << " (Rs" 
                     << fixed << setprecision(2) 
                     << items[i]->getPrice() << " each)\n";
            }
            cout << "Enter item number: ";
            int itemChoice;
            cin >> itemChoice;

            if (itemChoice < 1 || itemChoice > numItems) {
                cout << "Invalid choice! Please try again.\n";
                continue;
            }

            cout << "Enter quantity: ";
            cin >> quantity;

            cart->addItem(new Item(items[itemChoice - 1]->getName(), items[itemChoice - 1]->getPrice(), quantity));
        } else if (choice == 2) {
            cout << "Enter the name of the item to remove from the cart: ";
            string itemName;
            cin.ignore();  
            getline(cin, itemName);
            cart->removeItem(itemName);
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    Bill bill(cart);
    bill.generateBill();

    delete cart;
    for (int i = 0; i < numItems; ++i) {
        delete items[i];
    }

    return 0;
}
