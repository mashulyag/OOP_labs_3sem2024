#include "dragon.h"
#include "bull.h"
#include "toad.h"

void Dragon::accept(NPC* attacker, const int& distance) {
    if (!isDead() && (dynamic_cast<Bull*>(attacker) || dynamic_cast<Toad*>(attacker))) {
        bool win = isInRange(attacker, distance);
        if (win) {
            die();
            notify(attacker, win);
        }
    }
}

