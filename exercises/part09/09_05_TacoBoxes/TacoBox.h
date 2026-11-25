#pragma once

class TacoBox {
public:
    virtual ~TacoBox() = default;
    virtual int tacosRemaining() const = 0;
    virtual void eat() = 0;
};
