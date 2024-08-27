#include <iostream>
#include <vector>
#include <iomanip>

class Item {
private:
    std::string name;
    double price;
    int quantity;

public:
    Item(std::string itemName, double itemPrice, int itemQuantity)
        : name(itemName), price(itemPrice), quantity(itemQuantity) {}

    std::string getName() const {
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
    std::vector<Item> items; 

public:
    void addItem(const Item& item) {
        this->items.push_back(item); 
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : this->items) { 
            total += item.getTotalPrice();
        }
        return total;
    }

    const std::vector<Item>& getItems() const {
        return this->items;
    }
};

class Bill {
private:
    Cart cart; 

public:
    Bill(const Cart& cart) : cart(cart) {}

    void generateBill() const {
        std::cout << "----- Grocery Bill -----\n";
        for (const auto& item : this->cart.getItems()) { 
            std::cout << item.getName() << " - " << item.getQuantity()
                      << " x Rs" << std::fixed << std::setprecision(2)
                      << item.getPrice() << " = Rs" << item.getTotalPrice() << "\n";
        }
        std::cout << "------------------------\n";
        std::cout << "Total Amount: Rs" << std::fixed << std::setprecision(2)
                  << this->cart.getTotalAmount() << "\n";
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
