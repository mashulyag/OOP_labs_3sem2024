#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/bull.h"
#include "../include/dragon.h"
#include "../include/frog.h"
#include "../include/factory.h"
#include <fstream>
#include <thread>
#include <chrono>

// Тест для проверки создания NPC
TEST(FactoryTest, CreateNPC) {
    auto dragon = factory(DragonType, 100, 100, "Dragon1");
    auto bull = factory(BullType, 150, 150, "Bull1");
    auto frog = factory(FrogType, 200, 200, "Frog1");

    ASSERT_EQ(dragon->get_type(), DragonType);
    ASSERT_EQ(bull->get_type(), BullType);
    ASSERT_EQ(frog->get_type(), FrogType);
}

// Тест для проверки перемещения NPC
TEST(NPCTest, MoveTest) {
    NPC npc(BullType, 100, 100, "Bull1");
    npc.move(5, -5, 500, 500);
    ASSERT_EQ(npc.position().first, 105);
    ASSERT_EQ(npc.position().second, 95);
}

// Тест для проверки метода is_close
TEST(NPCTest, IsCloseTest) {
    NPC npc1(DragonType, 0, 0, "Dragon1");
    NPC npc2(DragonType, 3, 4, "Dragon2");
    ASSERT_TRUE(npc1.is_close(std::make_shared<NPC>(npc2), 5));
    ASSERT_FALSE(npc1.is_close(std::make_shared<NPC>(npc2), 4));
}

// Тест для проверки метода accept (боя)
TEST(NPCTest, AcceptTest) {
    NPC dragon(DragonType, 0, 0, "Dragon1");
    NPC bull(BullType, 10, 10, "Bull1");

    // Имитация боя
    bool result = bull.accept(std::make_shared<NPC>(dragon));
    ASSERT_TRUE(result); // Дракон должен победить быка
}

// Тест для проверки метода fight для Дракона
TEST(DragonTest, FightTest) {
    Dragon dragon(0, 0, "Dragon1");
    Bull bull(10, 10, "Bull1");

    bool result = dragon.fight(std::make_shared<Bull>(bull));
    ASSERT_TRUE(result); // Дракон должен победить быка
}

// Тест для проверки метода fight для Быка
TEST(BullTest, FightTest) {
    Bull bull(0, 0, "Bull1");
    Frog frog(10, 10, "Frog1");

    bool result = bull.fight(std::make_shared<Frog>(frog));
    ASSERT_TRUE(result); // Бык должен победить лягушку
}

// Тест для проверки метода fight для Лягушки
TEST(FrogTest, FightTest) {
    Frog frog(0, 0, "Frog1");
    Dragon dragon(10, 10, "Dragon1");

    bool result = frog.fight(std::make_shared<Dragon>(dragon));
    ASSERT_FALSE(result); // Лягушка не должна победить дракона
}

// Тест для проверки сохранения и загрузки NPC из файла
TEST(FileTest, SaveAndLoadNPC) {
    set_t npcs;
    npcs.insert(factory(DragonType, 100, 100, "Dragon1"));
    npcs.insert(factory(BullType, 150, 150, "Bull1"));
    npcs.insert(factory(FrogType, 200, 200, "Frog1"));

    // Сохранение в файл
    save(npcs, "test_npcs.txt");

    // Загрузка из файла
    set_t loaded_npcs = load("test_npcs.txt");

    ASSERT_EQ(loaded_npcs.size(), 3);
    ASSERT_EQ(loaded_npcs.begin()->get_type(), DragonType);
    ASSERT_EQ((++loaded_npcs.begin())->get_type(), BullType);
    ASSERT_EQ((++(++loaded_npcs.begin()))->get_type(), FrogType);
}

// Тест для проверки работы потоков
TEST(ThreadTest, MoveAndFight) {
    set_t npcs;
    npcs.insert(factory(DragonType, 100, 100, "Dragon1"));
    npcs.insert(factory(BullType, 150, 150, "Bull1"));
    npcs.insert(factory(FrogType, 200, 200, "Frog1"));

    bool stop_flag = false;

    // Поток для перемещения NPC
    std::thread move_thread([&npcs, &stop_flag]() {
        while (!stop_flag) {
            for (auto& npc : npcs) {
                std::lock_guard<std::mutex> lock(npc->mtx);
                if (npc->is_alive()) {
                    npc->move(5, 5, 500, 500);
                }
            }
            std::this_thread::sleep_for(100ms);
        }
    });

    // Поток для обработки боев
    std::thread fight_thread([&npcs, &stop_flag]() {
        while (!stop_flag) {
            for (auto& npc1 : npcs) {
                for (auto& npc2 : npcs) {
                    if (npc1 != npc2 && npc1->is_alive() && npc2->is_alive() && npc1->is_close(npc2, 100)) {
                        npc2->must_die(); // Имитация боя
                    }
                }
            }
            std::this_thread::sleep_for(100ms);
        }
    });

    // Запуск потоков на короткое время
    std::this_thread::sleep_for(500ms);
    stop_flag = true;

    move_thread.join();
    fight_thread.join();

    // Проверка результатов
    int alive_count = 0;
    for (const auto& npc : npcs) {
        if (npc->is_alive()) {
            alive_count++;
        }
    }
    ASSERT_LT(alive_count, 3); // По крайней мере один NPC должен быть мертв
}

// Основная функция для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
