#pragma once

// Store combines a Warehouse, a ShoppingCart and a text interface.
// It only compiles once you have written Warehouse.h and ShoppingCart.h.

#include <iostream>
#include <print>
#include <string>
#include "ShoppingCart.h"
#include "Warehouse.h"

class Store {
public:
    Store(Warehouse& warehouse, std::istream& input) : warehouse(warehouse), input(input) {
    }

    // the function that handles the customer's visit to the store
    void shop(const std::string& customer) {
        ShoppingCart cart;
        std::println("Welcome to the store {}", customer);
        std::println("our selection:");
        for (const std::string& product : warehouse.products()) {
            std::println("{}", product);
        }

        std::string product;
        while (true) {
            std::print("what to put in the cart (press enter to go to the register): ");
            std::getline(input, product);
            if (product.empty()) {
                break;
            }
            if (warehouse.take(product)) {
                cart.add(product, warehouse.price(product));
            } else {
                std::println("Sorry, {} is not available.", product);
            }
        }

        std::println("your shoppingcart contents:");
        cart.print();
        std::println("total: {}", cart.price());
    }

private:
    Warehouse& warehouse;
    std::istream& input;
};
