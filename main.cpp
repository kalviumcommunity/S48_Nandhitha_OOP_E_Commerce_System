#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
protected:
    string name;
    double price;

public:
    Item() {
        name = "Unknown";
        price = 0.0;
        quantity = 0;
        cout << "" << endl;
    }

    Item(string itemName, double itemPrice, int itemQuantity)
        : name(itemName), price(itemPrice), quantity(itemQuantity) {
    }

    ~Item() {
        cout << "" << endl;
    }

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

    void setName(const string& newName) {
        this->name = newName;
    }

    void setPrice(double newPrice) {
        if (newPrice >= 0) {
            this->price = newPrice;
        }
    }
};

class Item : public Product {
private:
    int quantity;

public:
    Item() : Product(), quantity(0) {}

    Item(string itemName, double itemPrice, int itemQuantity)
        : Product(itemName, itemPrice), quantity(itemQuantity) {}

    ~Item() {}

    int getQuantity() const {
        return this->quantity;
    }

    double getTotalPrice() const {
        return this->price * this->quantity;
    }

    void setQuantity(int newQuantity) {
        if (newQuantity >= 0) {
            this->quantity = newQuantity;
        }
    }
};

class Discount {
public:
    virtual double applyDiscount(double totalAmount) const = 0;
};

class Cart {
private:
    vector<Item*> items;

protected:
    static int totalItemsInCart;
    static int totalItemsSold;

public:
    Cart() {
        totalItemsInCart = 0;
    }

    ~Cart() {
        for (Item* item : items) {
            delete item;
        }
    }

    void addItem(Item* item) {
        this->items.push_back(item);
        totalItemsInCart += item->getQuantity();
        totalItemsSold += item->getQuantity();
    }

    const vector<Item*>& getItems() const {
        return this->items;
    }

    void removeItem(const string& itemName) {
        for (auto it = items.begin(); it != items.end(); ) {
            if ((*it)->getName() == itemName) {
                totalItemsInCart -= (*it)->getQuantity();
                delete *it;
                it = items.erase(it);
            } else {
                ++it;
            }
        }
    }

    static int getTotalItemsInCart() {
        return totalItemsInCart;
    }

    static int getTotalItemsSold() {
        return totalItemsSold;
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : this->items) {
            total += item->getTotalPrice();
        }
        return total;
    }
};

int Cart::totalItemsInCart = 0;
int Cart::totalItemsSold = 0;

class Bill : public Discount {
private:
    Cart* cart;

public:
    Bill(Cart* cart) : cart(cart) {}

    double applyDiscount(double totalAmount) const override {
        return totalAmount * 0.9;
    }

    void generateBill() const {
        cout << "----- Grocery Bill -----\n";
        for (const auto& item : this->cart->getItems()) {
            cout << item->getName() << " - " << item->getQuantity()
                 << " x Rs" << fixed << setprecision(2)
                 << item->getPrice() << " = Rs" << item->getTotalPrice() << "\n";
        }
        cout << "------------------------\n";
        double totalAmount = this->cart->getTotalAmount();
        cout << "Total Amount: Rs" << fixed << setprecision(2) << totalAmount << "\n";
        cout << "Discounted Total: Rs" << fixed << setprecision(2) << applyDiscount(totalAmount) << "\n";
        cout << "Total items in cart: " << Cart::getTotalItemsInCart() << "\n";
        cout << "------------------------\n";
    }
};

int main() {
    Item* defaultItem = new Item();

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

            items[itemChoice - 1]->setQuantity(quantity);  
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

    cout << "Total items sold in all carts: " << Cart::getTotalItemsSold() << "\n";

    delete cart;
    delete defaultItem;
    for (int i = 0; i < numItems; ++i) {
        delete items[i];
    }

    return 0;
}
