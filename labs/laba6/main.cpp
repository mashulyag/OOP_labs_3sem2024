#include <iostream>
#include "include/factory.h"
#include "include/visitor.h"
#include "include/consoleobserv.h"
#include "include/logobserv.h"

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Dragon", "Dragon1", 300, 300));
    npcs.push_back(Factory::createNPC("Bull", "Bull1", 320, 320));
    npcs.push_back(Factory::createNPC("Toad", "Toad1", 290, 290));

    ConsoleObserver consoleObserver;
    LogObserver logObserver("log.txt");

    for (const auto& npc : npcs) {
        npc->attach(&consoleObserver);
        npc->attach(&logObserver);
    }

    BattleVisitor battleVisitor(100);
    battleVisitor.addObserver(&consoleObserver);
    battleVisitor.addObserver(&logObserver);

    battleVisitor.execute(npcs);

    for (const auto& npc : npcs) {
        npc->print();
    }

    return 0;
}
