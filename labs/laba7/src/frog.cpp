#include "../include/frog.h"
#include <iostream>
#include <cmath>
#include "../include/dragon.h"
#include "../include/bull.h"
#include "../include/NPC.h"

Frog::Frog(int x, int y, const std::string& name) : NPC(FrogType, x, y, name) {}

Frog::Frog(std::istream& is) : NPC(FrogType, is) {}

void Frog::print() {
    std::cout << *this;
}

bool Frog::is_frog() const {
    return true;
}

bool Frog::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, false); 
    return false;
}

bool Frog::fight(std::shared_ptr<Frog> other) {
    fight_notify(other, false);
    return false;
}

bool Frog::fight(std::shared_ptr<Bull> other) {
    fight_notify(other, false); 
    return false;
}

void Frog::save(std::ostream& os) {
    os << FrogType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Frog& Frog) {
    os << "Frog: " << *static_cast<NPC*>(&Frog) << std::endl;
    return os;
}

bool Frog::accept(std::shared_ptr<NPC> attacker) {
    return NPC::accept(attacker);
}
