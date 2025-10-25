#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <utility>
using namespace std;

enum class stockStatus { IN_STOCK, OUT_OF_STOCK };

int productIdCounter = 0;

struct Product {
    int id;
    string product_name;
    double price;
    stockStatus status;
    int quantity;

    Product() : id(0), price(0.0), status(stockStatus::OUT_OF_STOCK), quantity(0) {}

    Product(const string& name, double price_, int quantity_)
        : id(++productIdCounter),
          product_name(name),
          price(price_),
          status(quantity_ > 0 ? stockStatus::IN_STOCK : stockStatus::OUT_OF_STOCK),
          quantity(quantity_) {}
};

class VendingMachine {
    int capacity;
    int total_stock;
    map<int, Product> products;

public:
    VendingMachine(int capacity_) : capacity(capacity_), total_stock(0) {}

    void addProduct(const string& product_name, double price, int quantity) {
        if (total_stock >= capacity) throw runtime_error("Vending machine is full");
        if (quantity <= 0) throw runtime_error("Quantity must be greater than zero");
        if (total_stock + quantity > capacity) throw runtime_error("Not enough space in vending machine");

        pair<bool,int> res = product_exists(product_name);
        bool exists = res.first;
        int existing_id = res.second;

        if (exists) {
            Product& p = products[existing_id];
            p.quantity += quantity;
            p.status = (p.quantity > 0) ? stockStatus::IN_STOCK : stockStatus::OUT_OF_STOCK;
            total_stock += quantity;
        } else {
            Product p(product_name, price, quantity);
            products.emplace(p.id, p);
            total_stock += quantity;
        }
    }

    void getProducts() const {
        if (products.empty()) {
            cout << "No products available\n";
            return;
        }
        for (map<int, Product>::const_iterator it = products.begin(); it != products.end(); ++it) {
            int id = it->first;
            const Product& product = it->second;
            cout << "ID: " << id
                 << ", Name: " << product.product_name
                 << ", Price: " << product.price
                 << ", Status: " << (product.status == stockStatus::IN_STOCK ? "In Stock" : "Out of Stock")
                 << ", Quantity: " << product.quantity << "\n";
        }
    }

    double getBillingAmount(const vector<pair<string,int> >& items) const {
        double total_amount = 0.0;
        if (items.empty()) return total_amount;

        for (size_t i = 0; i < items.size(); ++i) {
            const string& product_name = items[i].first;
            int qty = items[i].second;

            if (qty <= 0) throw runtime_error("Quantity must be greater than zero");

            int product_id = getProductId(product_name);
            const Product& product = products.find(product_id)->second;

            if (product.status == stockStatus::OUT_OF_STOCK)
                throw runtime_error(string("Product is out of stock: ") + product_name);

            if (product.quantity < qty)
                throw runtime_error(string("Not enough stock for product: ") + product_name);

            total_amount += product.price * qty;
        }
        return total_amount;
    }

    void purchase(const vector<pair<string,int> >& items) {
        if (items.empty()) throw runtime_error("No items to purchase");

        // Validate and compute total first (atomic intent)
        double total_amount = getBillingAmount(items);

        // Commit: decrement quantities
        for (size_t i = 0; i < items.size(); ++i) {
            const string& product_name = items[i].first;
            int qty = items[i].second;

            int product_id = getProductId(product_name);
            Product& product = products.find(product_id)->second;

            product.quantity -= qty;
            product.status = (product.quantity > 0) ? stockStatus::IN_STOCK : stockStatus::OUT_OF_STOCK;
            total_stock -= qty;
        }

        cout << "Purchase successful. Total amount: " << total_amount << "\n";
    }

private:
    pair<bool,int> product_exists(const string& product_name) const {
        for (map<int, Product>::const_iterator it = products.begin(); it != products.end(); ++it) {
            if (it->second.product_name == product_name) {
                return pair<bool,int>(true, it->first);
            }
        }
        return pair<bool,int>(false, -1);
    }

    int getProductId(const string& product_name) const {
        for (map<int, Product>::const_iterator it = products.begin(); it != products.end(); ++it) {
            if (it->second.product_name == product_name) {
                return it->first;
            }
        }
        throw runtime_error("Product not found: " + product_name);
    }
};

int main() {
    VendingMachine vm(10);
    vm.addProduct("Coke", 1.5, 5);
    vm.addProduct("Pepsi", 1.2, 3);
    vm.addProduct("Water", 0.5, 2);
    vm.getProducts();

    vector<pair<string,int> > items;
    items.push_back(make_pair(string("Coke"), 2));
    items.push_back(make_pair(string("Pepsi"), 1));

    double total_amount = vm.getBillingAmount(items);
    cout << "Total amount: " << total_amount << "\n";

    vm.purchase(items);
    vm.getProducts();
    
    return 0;
}
