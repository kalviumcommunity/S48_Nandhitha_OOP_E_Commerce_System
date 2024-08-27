#include <iostream>
#include <vector>
#include <iomanip>

class Item {
private:
    std::string name;
    double price;
    int quantity;

public:
    // Constructor to initialize the item
    Item(std::string itemName, double itemPrice, int itemQuantity)
        : name(itemName), price(itemPrice), quantity(itemQuantity) {}

    // Getter for the name
    std::string getName() const {
        return this->name;  // Using this pointer
    }

    // Getter for the price
    double getPrice() const {
        return this->price;  // Using this pointer
    }

    // Getter for the quantity
    int getQuantity() const {
        return this->quantity;  // Using this pointer
    }

    // Method to calculate the total price for this item
    double getTotalPrice() const {
        return this->price * this->quantity;  // Using this pointer
    }
};

class Cart {
private:
    std::vector<Item> items;  // Vector to store items in the cart

public:
    // Method to add an item to the cart
    void addItem(const Item& item) {
        this->items.push_back(item);  // Using this pointer
    }

    // Method to calculate the total amount of all items in the cart
    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : this->items) {  // Using this pointer
            total += item.getTotalPrice();
        }
        return total;
    }

    // Method to return the items in the cart
    const std::vector<Item>& getItems() const {
        return this->items;  // Using this pointer
    }
};

class Bill {
private:
    Cart cart;  // Cart object to generate the bill from

public:
    // Constructor to initialize the bill with a cart
    Bill(const Cart& cart) : cart(cart) {}

    // Method to generate and print the bill
    void generateBill() const {
        std::cout << "----- Grocery Bill -----\n";
        for (const auto& item : this->cart.getItems()) {  // Using this pointer
            std::cout << item.getName() << " - " << item.getQuantity()
                      << " x Rs" << std::fixed << std::setprecision(2)
                      << item.getPrice() << " = Rs" << item.getTotalPrice() << "\n";
        }
        std::cout << "------------------------\n";
        std::cout << "Total Amount: Rs" << std::fixed << std::setprecision(2)
                  << this->cart.getTotalAmount() << "\n";  // Using this pointer
        std::cout << "------------------------\n";
    }
};

int main() {
    // Creating item objects
    Item apples("Apples", 50.0, 4);  // 4 Apples at Rs50 each
    Item bananas("Bananas", 30.0, 6);  // 6 Bananas at Rs30 each
    Item milk("Milk", 150.0, 2);  // 2 bottles of Milk at Rs150 each

    // Creating a cart object and adding items to it
    Cart cart;
    cart.addItem(apples);
    cart.addItem(bananas);
    cart.addItem(milk);

    // Creating a bill object and generating the bill
    Bill bill(cart);
    bill.generateBill();

    return 0;
}
