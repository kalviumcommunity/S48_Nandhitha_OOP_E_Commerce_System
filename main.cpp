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
        return this->name;  // Using this pointer
    }

    double getPrice() const {
        return this->price;  // Using this pointer
    }

    int getQuantity() const {
        return this->quantity;  // Using this pointer
    }

    double getTotalPrice() const {
        return this->price * this->quantity;  // Using this pointer
    }
};

class Cart {
private:
    std::vector<Item> items; 

public:
    void addItem(const Item& item) {
        this->items.push_back(item);  // Using this pointer
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : this->items) {  // Using this pointer
            total += item.getTotalPrice();
        }
        return total;
    }

    const std::vector<Item>& getItems() const {
        return this->items;  // Using this pointer
    }
};

class Bill {
private:
    Cart cart;

public:
    Bill(const Cart& cart) : cart(cart) {}

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
    // Array of items with name, price and initial quantity
    Item items[] = {
        Item("Apples", 50.0, 0),
        Item("Bananas", 30.0, 0),
        Item("Milk", 150.0, 0),
        Item("Bread", 40.0, 0),
        Item("Cheese", 200.0, 0),
        Item("Eggs", 10.0, 0),
        Item("Butter", 80.0, 0),
        Item("Rice", 60.0, 0),
        Item("Pasta", 120.0, 0),
        Item("Sugar", 45.0, 0),
        Item("Coffee", 250.0, 0),
        Item("Tea", 150.0, 0),
        Item("Juice", 75.0, 0),
        Item("Chicken", 300.0, 0),
        Item("Beef", 400.0, 0),
        Item("Fish", 350.0, 0),
        Item("Potatoes", 25.0, 0),
        Item("Onions", 35.0, 0),
        Item("Tomatoes", 50.0, 0),
        Item("Carrots", 40.0, 0)
    };

    int numItems = sizeof(items) / sizeof(items[0]);
    Cart cart;
    int choice;
    int quantity;

    while (true) {
        std::cout << "Select an item to add to the cart:\n";
        
        // Display the menu using a for loop
        for (int i = 0; i < numItems; ++i) {
            std::cout << (i + 1) << ". " << items[i].getName() << " (Rs" 
                      << std::fixed << std::setprecision(2) 
                      << items[i].getPrice() << " each)\n";
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

        // Add the selected item with the specified quantity to the cart
        Item selectedItem = items[choice - 1];
        cart.addItem(Item(selectedItem.getName(), selectedItem.getPrice(), quantity));
    }

    Bill bill(cart);
    bill.generateBill();

    return 0;
}
