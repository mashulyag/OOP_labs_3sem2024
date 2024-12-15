#include "../include/bull.h"
#include <iostream>
#include <cmath>
#include "../include/dragon.h"
#include "../include/frog.h"
#include "../include/NPC.h"

Bull::Bull(int x, int y, const std::string& name) : NPC(BullType, x, y, name) {}

Bull::Bull(std::istream& is) : NPC(BullType, is) {}

void Bull::print() {
    std::cout << *this;
}

bool Bull::is_bull() const {
    return true;
}

bool Bull::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, false); 
    return false;
}

bool Bull::fight(std::shared_ptr<Frog> other) {
    fight_notify(other, true);
    return true;
}

bool Bull::fight(std::shared_ptr<Bull> other) {
    fight_notify(other, false); 
    return false;
}

void Bull::save(std::ostream& os) {
    os << BullType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Bull& Bull) {
    os << "Bull: " << *static_cast<NPC*>(&Bull) << std::endl;
    return os;
}

bool Bull::accept(std::shared_ptr<NPC> attacker) {
    return NPC::accept(attacker);
}
