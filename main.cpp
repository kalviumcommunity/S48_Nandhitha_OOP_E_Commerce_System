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
    std::vector<Item*> items; // Store pointers to dynamically allocated items

public:
    ~Cart() { // Destructor to free allocated memory
        for (Item* item : items) {
            delete item;
        }
    }

    void addItem(Item* item) {
        this->items.push_back(item);
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : this->items) { 
            total += item->getTotalPrice();
        }
        return total;
    }

    const std::vector<Item*>& getItems() const {
        return this->items;
    }
};

class Bill {
private:
    Cart* cart; // Dynamically allocated Cart

public:
    Bill(Cart* cart) : cart(cart) {}

    void generateBill() const {
        std::cout << "----- Grocery Bill -----\n";
        for (const auto& item : this->cart->getItems()) { 
            std::cout << item->getName() << " - " << item->getQuantity()
                      << " x Rs" << std::fixed << std::setprecision(2)
                      << item->getPrice() << " = Rs" << item->getTotalPrice() << "\n";
        }
        std::cout << "------------------------\n";
        std::cout << "Total Amount: Rs" << std::fixed << std::setprecision(2)
                  << this->cart->getTotalAmount() << "\n";
        std::cout << "------------------------\n";
    }
};

int main() {
    Item* items[] = {
        new Item("Apples", 50.0, 0),
        new Item("Bananas", 30.0, 0),
        new Item("Milk", 150.0, 0),
        // ... (other items)
        new Item("Carrots", 40.0, 0)
    };

    int numItems = sizeof(items) / sizeof(items[0]);
    Cart* cart = new Cart();
    int choice;
    int quantity;

    while (true) {
        std::cout << "Select an item to add to the cart:\n";
        
        for (int i = 0; i < numItems; ++i) {
            std::cout << (i + 1) << ". " << items[i]->getName() << " (Rs" 
                      << std::fixed << std::setprecision(2) 
                      << items[i]->getPrice() << " each)\n";
        }
        std::cout << (numItems + 1) << ". Checkout and Generate Bill\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == numItems + 1) {
            break;
        }

        if (choice < 1 || choice > numItems) {
            std::cout << "Invalid choice! Please try again.\n";
            continue;
        }

        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        cart->addItem(new Item(items[choice - 1]->getName(), items[choice - 1]->getPrice(), quantity));
    }

    Bill bill(cart);
    bill.generateBill();

    // Clean up dynamically allocated memory
    delete cart;
    for (int i = 0; i < numItems; ++i) {
        delete items[i];
    }

    return 0;
}
