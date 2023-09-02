#include "StupidPlayer.h"

StupidPlayer::StupidPlayer(std::string name) {
    this->name_ = name;
}

std::string StupidPlayer::name() const {
    return name_;
}

void StupidPlayer::receiveCards(const std::vector<const Card *> &cards) {
    if (currentSet != game()->currentSetNumber()) {
        currentSet = game()->currentSetNumber();
        cards_.clear();
    }
    cards_.insert(cards_.end(), cards.begin(), cards.end());
}

const Card *StupidPlayer::playCard() {
    for (int i = 0; i < cards_.size(); i++) {
        if (game()->topCard()->value == cards_[i]->value || game()->currentColor() == cards_[i]->color)
            if (!cards_[i]->is_wild()){
                auto return_card = cards_[i];
                cards_.erase(cards_.cbegin() + i);
                return return_card;
            }
    }

    for (int i = 0; i < cards_.size(); i++) {
        if (cards_[i]->value == CardValue::Wild) {
            auto return_card = cards_[i];
            cards_.erase(cards_.cbegin()+i);
            return return_card;
        }
    }

    for (int i = 0; i < cards_.size(); i++) {
        if (cards_[i]->value == CardValue::WildDraw4) {
            auto return_card = cards_[i];
            cards_.erase(cards_.cbegin()+i);
            return return_card;
        }
    }
}

bool StupidPlayer::drawAdditionalCard(const Card *additionalCard) {
    if (additionalCard->value == game()->topCard()->value || additionalCard->color == game()->currentColor() ||
        additionalCard->is_wild()) return true;
    cards_.push_back(additionalCard);
    return false;
}

CardColor StupidPlayer::changeColor() {
    return Green;
}

