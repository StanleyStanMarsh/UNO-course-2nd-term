#include "uno_game.h"

class StupidPlayer : public UnoPlayer{
    std::string name_;

    std::vector<const Card*> cards_;

    int currentSet;
public:
    StupidPlayer(std::string name);

    std::string name() const override;

    void receiveCards(const std::vector<const Card*>& cards) override;

    const Card * playCard() override;

    bool drawAdditionalCard(const Card * additionalCard) override;

    CardColor changeColor() override;
};

