#pragma once
#include "NPC.h"

struct Frog : public NPC {
    Frog(int x, int y, const std::string& name);
    Frog(std::istream& is);

    void print() override;

    bool is_frog() const override;

    bool accept(std::shared_ptr<NPC> attacker) override;

    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Frog> other) override;
    bool fight(std::shared_ptr<Bull> other) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Frog& Frog);

    ~Frog() = default;
};
