#ifndef HAND_H
#define HAND_H

#include "utilities.h"
#include "card.h"

#include <vector>
#include <algorithm>

int const ACE_MAX_VAL = 11;
int const ACE_MIN_VAL = 1;
int const BLACKJACK_HAND = 21;

class Hand
{
public:
    Hand();
    Hand(Vector2D position, bool dealerHand = false);
    ~Hand();

    uint GetScore() const { return _score; }

    bool IsBusted() const { return GetScore() > BLACKJACK_HAND; }
    bool IsBlackjack() const { return GetScore() == BLACKJACK_HAND && _cards.size() == 2; }

    Hand& AddCard(Card* card);
    void RemoveCard(const Card* card);
    void Clear();

    void Draw();

    void ShowSecondCard() { _drawSecondCardBack = false; }

private:
    std::vector<Card*> _cards;
    uint _score;

    bool _dealerHand;
    bool _drawSecondCardBack;
    int _cardJustAdded;

    Vector2D _position;

    void UpdateScore();
};

#endif // HAND_H
