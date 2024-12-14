#ifndef NPC_H
#define NPC_H

#include <string>
#include <list>
#include <iostream>
#include <cmath>
#include "observer.h"

class Observer;

class NPC {
protected:
    std::string name;
    int x, y;
    bool dead = false;
    std::list<Observer*> observers;

public:
    NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    const std::string& getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isDead() const { return dead; }
    virtual void die() { dead = true; }
    virtual bool canDefeat(NPC* other) const = 0;

    void print() const {
        std::cout << getType() << " [" << name << "] (" << x << ", " << y << ")"
                  << (isDead() ? " - DEAD" : "") << std::endl;
    }

    virtual void accept(NPC* attacker, const int& distance) = 0;
    virtual void attach(Observer* observer) { observers.push_back(observer); }
    virtual void detach(Observer* observer) { observers.remove(observer); }
    virtual void notify(NPC* attacker, bool win) {
        if (win) {
            for (auto& observer : observers) {
                observer->update(getName() + " was killed by " + attacker->getName());
            }
        }
    }

    bool isInRange(NPC* other, const int& distance) const {
        return (x - other->getX()) * (x - other->getX()) + (y - other->getY()) * (y - other->getY()) <= distance * distance;
    }
};

#endif

