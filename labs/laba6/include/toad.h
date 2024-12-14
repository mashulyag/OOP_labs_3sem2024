#ifndef TOAD_H
#define TOAD_H

#include "npc.h"

class Dragon;
class Bull;

class Toad : public NPC {
public:
    Toad(const std::string& name, int x, int y) : NPC(name, x, y) {}

    std::string getType() const override { return "Toad"; }

    bool canDefeat(NPC* other) const override {
        return false; // Жабы не могут победить никого
    }

    void accept(NPC* attacker, const int& distance) override;
};

#endif

