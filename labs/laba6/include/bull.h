#ifndef BULL_H
#define BULL_H

#include "npc.h"

class Dragon;
class Toad;

class Bull : public NPC {
public:
    Bull(const std::string& name, int x, int y) : NPC(name, x, y) {}

    std::string getType() const override { return "Bull"; }

    bool canDefeat(NPC* other) const override {
        return other->getType() == "Toad";
    }

    void accept(NPC* attacker, const int& distance) override;
};

#endif

