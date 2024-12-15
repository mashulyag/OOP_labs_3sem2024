#include "../include/dragon.h"
#include <iostream>
#include <cmath>
#include "../include/bull.h"
#include "../include/frog.h"
#include "../include/NPC.h"

Dragon::Dragon(int x, int y, const std::string& name) : NPC(DragonType, x, y, name) {}

Dragon::Dragon(std::istream& is) : NPC(DragonType, is) {}

void Dragon::print() {
    std::cout << *this;
}

bool Dragon::is_dragon() const {
    return true;
}

bool Dragon::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, false); 
    return false;
}

bool Dragon::fight(std::shared_ptr<Frog> other) {
    fight_notify(other, false);
    return false;
}

bool Dragon::fight(std::shared_ptr<Bull> other) {
    fight_notify(other, true); 
    return true;
}

void Dragon::save(std::ostream& os) {
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Dragon& Dragon) {
    os << "Dragon: " << *static_cast<NPC*>(&Dragon) << std::endl;
    return os;
}

bool Dragon::accept(std::shared_ptr<NPC> attacker) {
    // Используем базовую логику из NPC
    return NPC::accept(attacker);
}
