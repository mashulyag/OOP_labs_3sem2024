#include "../include/NPC.h"
#include <iostream>
#include <cmath>
#include <memory>

// Конструктор с параметрами для инициализации типа, координат и имени
NPC::NPC(NpcType t, int _x, int _y, const std::string& _name) : type(t), x(_x), y(_y), name(_name) {}

// Конструктор из потока ввода для инициализации типа, координат и имени
NPC::NPC(NpcType t, std::istream& is) : type(t) {
    is >> x >> y >> name;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(std::shared_ptr<NPC> defender, bool win) {
    for (auto& observer : observers) {
        observer->on_fight(shared_from_this(), defender, win);
    }
}

bool NPC::is_close(std::shared_ptr<NPC> other, size_t distance) const {
    return std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2);
}

bool NPC::is_bull() const { return false; }
bool NPC::is_dragon() const { return false; }
bool NPC::is_frog() const { return false; }

void NPC::save(std::ostream& os) {
    os << x << " " << y << " " << name << std::endl;
}

std::ostream& operator<<(std::ostream& os, NPC& npc) {
    os << "{ type: " << npc.type 
       << ", x: " << npc.x 
       << ", y: " << npc.y 
       << ", name: " << npc.name 
       << " }";
    return os;
}

void NPC::move(int dx, int dy, int max_x, int max_y) {
    x = std::max(0, std::min(x + dx, max_x));
    y = std::max(0, std::min(y + dy, max_y));
}

std::pair<int, int> NPC::position() const {
    return {x, y};
}

bool NPC::accept(std::shared_ptr<NPC> attacker) {
    int attack_power = attacker->roll_dice(); 
    int defense_power = this->roll_dice();   
    return attack_power > defense_power;  
}
