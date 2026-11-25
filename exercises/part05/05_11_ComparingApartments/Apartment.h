#pragma once

class Apartment {
public:
    Apartment(int rooms, int squares, int pricePerSquare)
        : rooms(rooms), squares(squares), pricePerSquare(pricePerSquare) {
    }

    // Add largerThan, priceDifference and moreExpensiveThan here

private:
    int rooms;
    int squares;
    int pricePerSquare;
};
