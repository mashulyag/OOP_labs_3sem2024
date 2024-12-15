#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <set>
#include <math.h>
#include <cstdlib>

struct NPC;
struct Dragon;
struct Bull;
struct Frog;

enum NpcType {
    Unknown = 0,
    DragonType = 1,
    BullType = 2,
    FrogType = 3
};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    std::mutex mtx;
    NpcType type; 
    int x{0};
    int y{0}; 
    std::string name; 
    std::vector<std::shared_ptr<IFightObserver>> observers; 
    bool alive{true}; 

    // Конструктор с параметрами для инициализации типа, координат и имени
    NPC(NpcType t, int _x, int _y, const std::string& name);

    // Конструктор из потока ввода для инициализации типа, координат и имени
    NPC(NpcType t, std::istream& is);

    void subscribe(std::shared_ptr<IFightObserver> observer);

    void fight_notify(std::shared_ptr<NPC> defender, bool win);

    virtual bool is_close(std::shared_ptr<NPC> other, size_t distance) const;

    virtual bool accept(std::shared_ptr<NPC> attacker) = 0;

    virtual bool is_bull() const;
    virtual bool is_dragon() const;
    virtual bool is_frog() const;

    virtual bool fight(std::shared_ptr<Bull> other) = 0;
    virtual bool fight(std::shared_ptr<Dragon> other) = 0;
    virtual bool fight(std::shared_ptr<Frog> other) = 0;

    virtual void print() = 0;

    // Метод для сохранения базовых данных объекта в поток
    virtual void save(std::ostream& os);

    // Перегрузка оператора вывода для вывода информации о NPC
    friend std::ostream& operator<<(std::ostream& os, NPC& npc);

    int roll_dice() const {
        return std::rand() % 6 + 1;
    }

    void move(int dx, int dy, int max_x, int max_y);

    bool is_alive() const {
        return alive;
    }

    void must_die() {
        alive = false;
    }

     NpcType get_type() const {
        return type;
    }

    std::pair<int, int> position() const;

    virtual ~NPC() = default;
};

using set_t = std::set<std::shared_ptr<NPC>>;
