#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

class Hand
{
public:
    Hand();
    Hand(std::vector<Card> cards);
    unsigned int GetScore();
    
    bool IsBusted() const { return GetScore() > 21; }
    bool IsBlackjack() const { return GetScore() == 21; }

    void AddCard(Card card);
private:
    std::vector<Card> _cards;
    
};
#endif // HAND_H