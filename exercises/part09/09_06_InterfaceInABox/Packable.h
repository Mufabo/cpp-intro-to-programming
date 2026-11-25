#pragma once

class Packable {
public:
    virtual ~Packable() = default;
    virtual double weight() const = 0;
};
