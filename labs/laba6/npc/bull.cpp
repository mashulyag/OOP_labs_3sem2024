#include "bull.h"
#include "dragon.h"
#include "toad.h"

void Bull::accept(NPC* attacker, const int& distance) {
    if (!isDead() && (dynamic_cast<Dragon*>(attacker) || dynamic_cast<Toad*>(attacker))) {
        bool win = isInRange(attacker, distance);
        if (win) {
            die();
            notify(attacker, win);
        }
    }
}

