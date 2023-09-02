#include "uno_game.h"

struct sortConditionValue {
    inline bool operator()(const Card *card1, const Card *card2) {
        return (card1->value > card2->value);
    }
};

class SimplePlayer: public UnoPlayer {
    std::string name_;

    std::vector<const Card*> cards_;

    int currentSet;
public:
    SimplePlayer(std::string name);

    std::string name() const override;

    void receiveCards(const std::vector<const Card*>& cards) override;

    const Card * playCard() override;

    bool drawAdditionalCard(const Card * additionalCard) override;

    CardColor changeColor() override;
};
