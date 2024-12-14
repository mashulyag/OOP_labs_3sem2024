#include "../include/toad.h"
#include "../include/dragon.h"
#include "../include/bull.h"

void Toad::accept(NPC* attacker, const int& distance) {
    if (!isDead() && (dynamic_cast<Dragon*>(attacker) || dynamic_cast<Bull*>(attacker))) {
        bool win = isInRange(attacker, distance);
        if (win) {
            die();
            notify(attacker, win);
        }
    }
}

