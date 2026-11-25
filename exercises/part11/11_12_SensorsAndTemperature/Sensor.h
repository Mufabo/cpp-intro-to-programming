#pragma once

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual bool isOn() const = 0;   // true if the sensor is on
    virtual void setOn() = 0;        // sets the sensor on
    virtual void setOff() = 0;       // sets the sensor off
    virtual int read() = 0;          // returns the sensor's value if it is on;
                                     // if it is off, throws std::logic_error
};
