#include "NPC.h"

struct Dragon : public NPC {
    Dragon(int x, int y, const std::string& name);

    Dragon(std::istream& is);

    void print() override;

    bool is_dragon() const override;

    bool accept(std::shared_ptr<NPC> attacker) override;

    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Frog> other) override;
    bool fight(std::shared_ptr<Bull> other) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Dragon& Dragon);

    ~Dragon() = default;
};
