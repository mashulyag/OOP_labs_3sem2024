#include "../include/NPC.h"
#include "../include/bull.h"
#include "../include/frog.h"
#include "../include/dragon.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <set>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>

using namespace std::chrono_literals;

using set_t = std::set<std::shared_ptr<NPC>>;

std::mutex print_mutex;

std::mutex npc_mutex;

class TextObserver : public IFightObserver {
private:
    TextObserver() = default;

public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "\nMurder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

std::shared_ptr<NPC> factory(std::istream& is) {
    int type = 0;
    if (is >> type) {
        switch (static_cast<NpcType>(type)) {
            case BullType: return std::make_shared<Bull>(is);
            case FrogType: return std::make_shared<Frog>(is);
            case DragonType: return std::make_shared<Dragon>(is);
            default: std::cerr << "Unexpected NPC type: " << type << std::endl; break;
        }
    }
    return nullptr;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y, const std::string& name) {
    std::shared_ptr<NPC> npc{};

    switch (type) {
            case BullType: npc = std::make_shared<Bull>(x, y, name);
            break;
            case FrogType: npc = std::make_shared<Frog>(x, y, name);
            break;
            case DragonType: npc = std::make_shared<Dragon>(x, y, name);
            break;
        }

    if (npc) {
        npc->subscribe(TextObserver::get());
    }

    return npc;
}

void save(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Failed to open file for saving: " << filename << std::endl;
        return;
    }
    fs << array.size() << std::endl;
    for (const auto& npc : array)
        npc->save(fs);
}

set_t load(const std::string& filename) {
    set_t result;
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Failed to open file for loading: " << filename << std::endl;
        return result;
    }

    size_t count = 0;
    fs >> count;
    for (size_t i = 0; i < count; ++i) {
        if (auto npc = factory(fs)) {
            npc->subscribe(TextObserver::get());
            result.insert(npc);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (const auto& npc : array)
        npc->print();
    return os;
}

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;

    for (const auto &attacker : array) {
        for (const auto &defender : array) {
            if (attacker != defender && attacker->is_alive() && defender->is_alive() &&
                attacker->is_close(defender, distance) && defender->accept(attacker)) {
                dead_list.insert(defender);
            }
        }
    }

    return dead_list;
}

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
private:
    std::queue<FightEvent> events;
    std::mutex mtx;

public:
    static FightManager& get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent&& event) {
        std::lock_guard<std::mutex> lock(mtx);
        events.push(event);
    }

    void operator()(bool & stop_flag) {
        while (!stop_flag) {
            std::optional<FightEvent> event;
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!events.empty()) {
                    event = events.front();
                    events.pop();
                }
            }

            if (event) {
                if (event->attacker->is_alive() && event->defender->is_alive()) {
                    if (event->defender->accept(event->attacker)) {
                        std::cout << "Oops... someone died..." << std::endl;
                        event->defender->must_die();
                    }
                }
            }

            std::this_thread::sleep_for(100ms);
        }
    }
};

int main() {
    set_t array;
    const int MAX_X = 100;
    const int MAX_Y = 100;
    const int DISTANCE = 50;

    // Генерация начальных NPC
    std::cout << "Generating NPCs..." << std::endl;
    for (size_t i = 0; i < 50; ++i) {
        NpcType type = NpcType(i % 3 + 1);
        int x = std::rand() % MAX_X;
        int y = std::rand() % MAX_Y;
        std::string name = "NPC_" + std::to_string(i);


        std::cout << "type:" << (int)type << std::endl;
        auto npc = factory(type, x, y, name);
        if (npc) array.insert(npc);
    }

    std::cout << "Starting list:" << std::endl
              << array;

    bool stop_flag = false;

    // Поток для передвижения NPC и определения боев
    std::thread move_thread([&array, MAX_X, MAX_Y, DISTANCE, &stop_flag]() {
        while (!stop_flag) {
                  for (auto npc : array) {
                    std::lock_guard<std::mutex> lck(npc->mtx);
                    if (npc)
                    {
                        
                        if (npc->is_alive()) {
                            int dx = std::rand() % 10 - 5;
                            int dy = std::rand() % 10 - 5;
                            npc->move(dx, dy, MAX_X, MAX_Y);

                            for (auto& other : array) {
                                if (npc != other && npc->is_alive() && other->is_alive() && npc->is_close(other, DISTANCE)) {
                                    FightManager::get().add_event({npc, other});
                                }
                            }
                        }
                    }
                }
                std::this_thread::sleep_for(100ms); 
        }
        std::cout << "Move thread stopped" << std::endl;
    });

    // Поток для обработки боев
    std::thread fight_thread(std::ref(FightManager::get()),std::ref(stop_flag));

    const int grid = 20;
    std::array<char, (grid+1) * (grid+1)> fields{0};
    auto start_time = std::chrono::high_resolution_clock::now();
    while (!stop_flag) {
        fields.fill(0);
        {
            for (const auto& npc : array) {
                std::lock_guard<std::mutex> lck(npc->mtx);
                const auto [x, y] = npc->position();
                int i = grid * x / MAX_X;
                int j = grid * y / MAX_Y;
                int k = i+j*grid;
                if (npc->is_alive()) {
                    switch (npc->get_type()) {
                        case DragonType: fields[k] = 'D'; break;
                        case FrogType: fields[k] = 'F'; break;
                        case BullType: fields[k] = 'B'; break;
                        default: fields[k] = '?'; break;
                    }
                } else {
                    fields[k] = '-'; // Мертвый NPC
                }
            }
        }

        for (int j = 0; j < grid; ++j) {
            for (int i = 0; i < grid; ++i) {
                char c = fields[i + j * grid];
                if (c != 0)
                    std::cout << "[" << c << "]";
                else
                    std::cout << "[ ]";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        auto current_time = std::chrono::high_resolution_clock::now();
        std::cout << "Time:" << std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() << std::endl;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() >= 30000) {
            stop_flag = true; // Установка флага остановки
            std::cout << "Stop :)" << std::endl;
        }

        std::this_thread::sleep_for(1s);
    }

    std::cout << "Join move" << std::endl;
    move_thread.join();
    std::cout << "Join fight" << std::endl;
    fight_thread.join();

    std::cout << "\nSurvivors:" << std::endl;
    for (auto& npc : array) {
        if (npc->is_alive()) {
            npc->print();
        }
    }

    return 0;
}
