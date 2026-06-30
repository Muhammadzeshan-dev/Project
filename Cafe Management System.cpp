#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
using namespace std;
struct MenuItem {
    int id;
    string name;
    double price;
    string category;
};
struct OrderItem {
    int itemId;
    string name;
    double price;
    int quantity;
};
struct Order {
    int orderId;
    string customerName;
    vector<OrderItem> items;
    double subtotal;
    double tax;
    double total;
};
vector<MenuItem> menu;
vector<Order> orderHistory;
int nextItemId = 1;
int nextOrderId = 1001;
const double TAX_RATE = 0.07; // 7% tax
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int getValidatedInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
        }
    }
}
double getValidatedDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter a positive number.\n";
            clearInputBuffer();
        }
    }
}
string getValidatedString(const string &prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    while (value.empty()) {
        cout << "Input cannot be empty. " << prompt;
        getline(cin, value);
    }
    return value;
}
void seedDefaultMenu() {
    menu.push_back({nextItemId++, "Espresso", 150.0, "Beverage"});
    menu.push_back({nextItemId++, "Cappuccino", 220.0, "Beverage"});
    menu.push_back({nextItemId++, "Latte", 230.0, "Beverage"});
    menu.push_back({nextItemId++, "Iced Tea", 180.0, "Beverage"});
    menu.push_back({nextItemId++, "Club Sandwich", 350.0, "Food"});
    menu.push_back({nextItemId++, "Cheese Burger", 420.0, "Food"});
    menu.push_back({nextItemId++, "Chocolate Cake", 280.0, "Dessert"});
    menu.push_back({nextItemId++, "Cheesecake", 320.0, "Dessert"});
}
void displayMenu() {
    cout << "\n========== CAFE MENU ==========\n";
    cout << left << setw(6) << "ID" << setw(20) << "Item"
         << setw(15) << "Category" << "Price (Rs)\n";
    cout << "--------------------------------------------------\n";
    for (const auto &item : menu) {
        cout << left << setw(6) << item.id << setw(20) << item.name
             << setw(15) << item.category << fixed << setprecision(2)
             << item.price << "\n";
    }
    cout << "====================================================\n";
}
void addMenuItem() {
    string name = getValidatedString("Enter item name: ");
    string category = getValidatedString("Enter category (Beverage/Food/Dessert): ");
    double price = getValidatedDouble("Enter price: ");
    menu.push_back({nextItemId++, name, price, category});
    cout << "Item added successfully!\n";
}
void removeMenuItem() {
    int id = getValidatedInt("Enter item ID to remove: ");
    bool found = false;
    for (size_t i = 0; i < menu.size(); i++) {
        if (menu[i].id == id) {
            menu.erase(menu.begin() + i);
            found = true;
            break;
        }
    }
    if (found)
        cout << "Item removed successfully!\n";
    else
        cout << "Item not found.\n";
}
MenuItem* findMenuItemById(int id) {
    for (auto &item : menu) {
        if (item.id == id) return &item;
    }
    return nullptr;
}
void printReceipt(const Order &order);
void takeOrder() {
    if (menu.empty()) {
        cout << "Menu is empty. Please add items first.\n";
        return;
    }
    string customerName = getValidatedString("Enter customer name: ");
    Order newOrder;
    newOrder.orderId = nextOrderId++;
    newOrder.customerName = customerName;
    char choice;
    do {
        displayMenu();
        int id = getValidatedInt("Enter item ID to order: ");
        MenuItem* selected = findMenuItemById(id);
        if (selected == nullptr) {
            cout << "Invalid item ID. Try again.\n";
        } else {
            int qty = getValidatedInt("Enter quantity: ");
            if (qty <= 0) {
                cout << "Quantity must be positive.\n";
            } else {
                OrderItem oi;
                oi.itemId = selected->id;
                oi.name = selected->name;
                oi.price = selected->price;
                oi.quantity = qty;
                newOrder.items.push_back(oi);
                cout << qty << " x " << selected->name << " added to order.\n";
            }
        }
        cout << "Add another item? (y/n): ";
        cin >> choice;
        clearInputBuffer();
    } while (choice == 'y' || choice == 'Y');
    double subtotal = 0;
    for (const auto &oi : newOrder.items) {
        subtotal += oi.price * oi.quantity;
    }
    newOrder.subtotal = subtotal;
    newOrder.tax = subtotal * TAX_RATE;
    newOrder.total = subtotal + newOrder.tax;
    orderHistory.push_back(newOrder);
    cout << "\nOrder placed successfully! Order ID: " << newOrder.orderId << "\n";
    printReceipt(newOrder);
}
void printReceipt(const Order &order) {
    cout << "\n============ RECEIPT ============\n";
    cout << "Order ID: " << order.orderId << "\n";
    cout << "Customer: " << order.customerName << "\n";
    cout << "----------------------------------\n";
    cout << left << setw(20) << "Item" << setw(5) << "Qty"
         << setw(10) << "Price" << "Total\n";
    for (const auto &oi : order.items) {
        cout << left << setw(20) << oi.name << setw(5) << oi.quantity
             << setw(10) << fixed << setprecision(2) << oi.price
             << (oi.price * oi.quantity) << "\n";
    }
    cout << "----------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Subtotal: Rs " << order.subtotal << "\n";
    cout << "Tax (7%): Rs " << order.tax << "\n";
    cout << "TOTAL:    Rs " << order.total << "\n";
    cout << "==================================\n";
}
void viewOrderHistory() {
    if (orderHistory.empty()) {
        cout << "No orders placed yet.\n";
        return;
    }
    for (const auto &order : orderHistory) {
        printReceipt(order);
    }
}
double calculateTotalRevenue() {
    double revenue = 0;
    for (const auto &order : orderHistory) {
        revenue += order.total;
    }
    return revenue;
}
void showMainMenu() {
    cout << "\n========= CAFE MANAGEMENT SYSTEM =========\n";
    cout << "1. View Menu\n";
    cout << "2. Add Menu Item\n";
    cout << "3. Remove Menu Item\n";
    cout << "4. Take New Order\n";
    cout << "5. View Order History\n";
    cout << "6. View Total Revenue\n";
    cout << "7. Exit\n";
    cout << "===========================================\n";
}
int main() {
    seedDefaultMenu();
    int choice;
    cout << "Welcome to the Cafe Management System!\n";
    do {
        showMainMenu();
        choice = getValidatedInt("Enter your choice: ");
        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                addMenuItem();
                break;
            case 3:
                removeMenuItem();
                break;
            case 4:
                takeOrder();
                break;
            case 5:
                viewOrderHistory();
                break;
            case 6:
                cout << fixed << setprecision(2);
                cout << "Total Revenue: Rs " << calculateTotalRevenue() << "\n";
                break;
            case 7:
                cout << "Thank you for using the Cafe Management System!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
    return 0;
}