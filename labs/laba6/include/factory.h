#ifndef FACTORY_H
#define FACTORY_H

#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "toad.h"
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <fstream>

class Factory final{
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y) {
        if (type == "Dragon") return std::make_unique<Dragon>(name, x, y);
        if (type == "Bull") return std::make_unique<Bull>(name, x, y);
        if (type == "Toad") return std::make_unique<Toad>(name, x, y);
        throw std::invalid_argument("Unknown NPC type: " + type);
    }

    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename) {
        std::vector<std::unique_ptr<NPC>> npcs;
        std::ifstream file(filename);
        if (!file) throw std::ios_base::failure("Failed to open file: " + filename);

        std::string type, name;
        int x, y;
        while (file >> type >> name >> x >> y) {
            npcs.push_back(createNPC(type, name, x, y));
        }
        return npcs;
    }

    static void saveToFile(const std::string& filename, const std::vector<std::unique_ptr<NPC>>& npcs) {
        std::ofstream file(filename);
        if (!file) throw std::ios_base::failure("Failed to open file: " + filename);

        for (const auto& npc : npcs) {
            file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
        }
    }

    private:
        Factory() {}
};
#endif

