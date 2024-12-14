#include <gtest/gtest.h>
#include "../include/factory.h"
#include "../include/dragon.h"
#include "../include/bull.h"
#include "../include/toad.h"
#include "../include/visitor.h"
#include "../include/consoleobserv.h"
#include "../include/logobserv.h"
#include <fstream>

// Тест для проверки создания NPC
TEST(FactoryTest, CreateNPC) {
    auto dragon = Factory::createNPC("Dragon", "Dragon1", 100, 100);
    auto bull = Factory::createNPC("Bull", "Bull1", 150, 150);
    auto toad = Factory::createNPC("Toad", "Toad1", 200, 200);

    ASSERT_EQ(dragon->getType(), "Dragon");
    ASSERT_EQ(bull->getType(), "Bull");
    ASSERT_EQ(toad->getType(), "Toad");
}

// Тест для проверки загрузки NPC из файла
TEST(FactoryTest, LoadFromFile) {
    std::vector<std::unique_ptr<NPC>> npcs = Factory::loadFromFile("tests/test_npcs.txt");
    ASSERT_EQ(npcs.size(), 3);
    ASSERT_EQ(npcs[0]->getType(), "Dragon");
    ASSERT_EQ(npcs[1]->getType(), "Bull");
    ASSERT_EQ(npcs[2]->getType(), "Toad");
}

// Тест для проверки взаимодействия между NPC
TEST(InteractionTest, Battle) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Dragon", "Dragon1", 100, 100));
    npcs.push_back(Factory::createNPC("Bull", "Bull1", 150, 150));
    npcs.push_back(Factory::createNPC("Toad", "Toad1", 200, 200));

    ConsoleObserver consoleObserver;
    LogObserver logObserver("build/log.txt");

    for (const auto& npc : npcs) {
        npc->attach(&consoleObserver);
        npc->attach(&logObserver);
    }

    BattleVisitor battleVisitor(100);
    battleVisitor.addObserver(&consoleObserver);
    battleVisitor.addObserver(&logObserver);

    battleVisitor.execute(npcs);

    ASSERT_EQ(npcs.size(), 2); // Dragon should defeat Bull
    ASSERT_EQ(npcs[0]->getType(), "Dragon");
    ASSERT_EQ(npcs[1]->getType(), "Toad");
}

// Тест для проверки записи событий в файл
TEST(LoggingTest, LogEvents) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Dragon", "Dragon1", 100, 100));
    npcs.push_back(Factory::createNPC("Bull", "Bull1", 150, 150));
    npcs.push_back(Factory::createNPC("Toad", "Toad1", 200, 200));

    ConsoleObserver consoleObserver;
    LogObserver logObserver("tests/test_log.txt");

    for (const auto& npc : npcs) {
        npc->attach(&consoleObserver);
        npc->attach(&logObserver);
    }

    BattleVisitor battleVisitor(100);
    battleVisitor.addObserver(&consoleObserver);
    battleVisitor.addObserver(&logObserver);

    battleVisitor.execute(npcs);

    std::ifstream logFile("build/log.txt");
    std::string line;
    std::getline(logFile, line);
    ASSERT_EQ(line, "Bull1 was killed by Dragon1");
}

