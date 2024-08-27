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
        return name;
    }

    // Getter for the price
    double getPrice() const {
        return price;
    }

    // Getter for the quantity
    int getQuantity() const {
        return quantity;
    }

    // Method to calculate the total price for this item
    double getTotalPrice() const {
        return price * quantity;
    }
};

class Cart {
private:
    std::vector<Item> items;  // Vector to store items in the cart

public:
    // Method to add an item to the cart
    void addItem(const Item& item) {
        items.push_back(item);
    }

    // Method to calculate the total amount of all items in the cart
    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getTotalPrice();
        }
        return total;
    }

    // Method to return the items in the cart
    const std::vector<Item>& getItems() const {
        return items;
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
        for (const auto& item : cart.getItems()) {
            std::cout << item.getName() << " - " << item.getQuantity()
                      << " x Rs" << std::fixed << std::setprecision(2)
                      << item.getPrice() << " = Rs" << item.getTotalPrice() << "\n";
        }
        std::cout << "------------------------\n";
        std::cout << "Total Amount: Rs" << std::fixed << std::setprecision(2)
                  << cart.getTotalAmount() << "\n";
        std::cout << "------------------------\n";
    }
};

int main() {
    Item apples("Apples", 50.0, 4); 
    Item bananas("Bananas", 30.0, 6);  
    Item milk("Milk", 150.0, 2); 
    Cart cart;
    cart.addItem(apples);
    cart.addItem(bananas);
    cart.addItem(milk);

    Bill bill(cart);
    bill.generateBill();

    return 0;
}
