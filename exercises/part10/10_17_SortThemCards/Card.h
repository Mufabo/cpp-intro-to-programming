#pragma once

#include <compare>
#include <format>
#include <stdexcept>
#include <string>

enum class Suit { Club, Diamond, Heart, Spade };

inline std::string toString(Suit suit) {
    switch (suit) {
        case Suit::Club:    return "CLUB";
        case Suit::Diamond: return "DIAMOND";
        case Suit::Heart:   return "HEART";
        case Suit::Spade:   return "SPADE";
    }
    return "?";
}

class Card {
public:
    Card(int value, Suit suit) : value(value), suit(suit) {
        if (value < 2 || value > 14) {
            throw std::invalid_argument("Card value must be in range 2...14.");
        }
    }

    int getValue() const { return value; }
    Suit getSuit() const { return suit; }

    // Part 1: define operator<=> and operator== here

    std::string toString() const {
        std::string cardValue = std::to_string(value);
        if (value == 11) cardValue = "J";
        else if (value == 12) cardValue = "Q";
        else if (value == 13) cardValue = "K";
        else if (value == 14) cardValue = "A";
        return ::toString(suit) + " " + cardValue;
    }

private:
    int value;
    Suit suit;
};

// Lets std::println("{}", card) print a card.
template <>
struct std::formatter<Card> : std::formatter<std::string> {
    auto format(const Card& card, auto& context) const {
        return std::formatter<std::string>::format(card.toString(), context);
    }
};
