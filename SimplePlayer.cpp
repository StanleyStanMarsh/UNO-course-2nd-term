#include "SimplePlayer.h"

SimplePlayer::SimplePlayer(std::string name) : cards_() {
    this->name_ = name;
}

std::string SimplePlayer::name() const {
    return name_;
}

void SimplePlayer::receiveCards(const std::vector<const Card *> &cards) {
    if (currentSet != game()->currentSetNumber()) {
        currentSet = game()->currentSetNumber();
        cards_.clear();
    }
    cards_.insert(cards_.end(), cards.begin(), cards.end());
}

const Card *SimplePlayer::playCard() {

    for (int i = 0; i < cards_.size(); i++) {
        if (game()->topCard()->value == cards_[i]->value)
            if (!cards_[i]->is_wild()) {
                auto return_card = cards_[i];
                cards_.erase(cards_.cbegin() + i);
                return return_card;
            }
    }

    std::sort(cards_.begin(), cards_.end(), sortConditionValue());
    int wild_ind = -1;
    for (int i = 0; i < cards_.size(); i++) {
        if (game()->currentColor() == cards_[i]->color) {
            if (!cards_[i]->is_wild()) {
                auto return_card = cards_[i];
                cards_.erase(cards_.cbegin() + i);
                return return_card;
            }
        }
        if (cards_[i]->value == CardValue::Wild) {
            wild_ind = i;
        }
    }

    if (wild_ind != -1) {
        auto return_card = cards_[wild_ind];
        cards_.erase(cards_.cbegin() + wild_ind);
        return return_card;
    }

    for (int i = 0; i < cards_.size(); i++) {
        if (cards_[i]->value == CardValue::WildDraw4) {
            auto return_card = cards_[i];
            cards_.erase(cards_.cbegin()+i);
            return return_card;
        }
    }
}

bool SimplePlayer::drawAdditionalCard(const Card *additionalCard) {
    if (additionalCard->value == game()->topCard()->value || additionalCard->color == game()->currentColor() ||
    additionalCard->is_wild()) return true;
    cards_.push_back(additionalCard);
    return false;
}

CardColor SimplePlayer::changeColor() {
    int num_of_colors[4]{};
    for (auto card : cards_) {
        num_of_colors[card->color]++;
    }
    int max_color = 0, max_num = num_of_colors[0];
    for (int i = 0; i < 4; i++) {
        if (max_num < num_of_colors[i]) {
            max_color = i;
            max_num = num_of_colors[i];
        }
    }
    return static_cast<CardColor>(max_color);
}


