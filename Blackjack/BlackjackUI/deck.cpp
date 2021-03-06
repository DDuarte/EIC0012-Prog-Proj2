/*!
 * \file deck.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "deck.h"
#include "utilities.h"
#include "card.h"
#include "blackjack.h"
#include "sounds.h"

#include <ctime>
#include <stack>
#include <vector>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

Deck::Deck(uint numberOfDecks /*= DEFAULT_NUMBER_OF_DECKS*/)
{
    InitializeDeck(numberOfDecks);
}

void Deck::InitializeDeck(uint numberOfDecks)
{
    _cards = std::vector<Card>();

    _cards.reserve(NUMBER_OF_CARDS*numberOfDecks);

    CardSuit types[] = { CARD_SUIT_CLUBS, CARD_SUIT_SPADES,
                        CARD_SUIT_HEARTS, CARD_SUIT_DIAMONDS };

    for (uint i = 0; i < NUMBER_OF_SUITS*numberOfDecks; ++i)
    {
        int suit = i % NUMBER_OF_SUITS;
        _cards.push_back(Card(types[suit], CARD_RANK_TWO));
        _cards.push_back(Card(types[suit], CARD_RANK_THREE));
        _cards.push_back(Card(types[suit], CARD_RANK_FOUR));
        _cards.push_back(Card(types[suit], CARD_RANK_FIVE));
        _cards.push_back(Card(types[suit], CARD_RANK_SIX));
        _cards.push_back(Card(types[suit], CARD_RANK_SEVEN));
        _cards.push_back(Card(types[suit], CARD_RANK_EIGHT));
        _cards.push_back(Card(types[suit], CARD_RANK_NINE));
        _cards.push_back(Card(types[suit], CARD_RANK_TEN));
        _cards.push_back(Card(types[suit], CARD_RANK_JACK));
        _cards.push_back(Card(types[suit], CARD_RANK_QUEEN));
        _cards.push_back(Card(types[suit], CARD_RANK_KING));
        _cards.push_back(Card(types[suit], CARD_RANK_ACE));
    }

    Shuffle();

    float dx = DECK_POSITION.X;
    float dy = DECK_POSITION.Y;

    for (uint i = 0; i < _cards.size(); i+=2) // Drawing each card makes a very
    {
        dx++;
        dy--;
        _cards[i].SetPosition(Vector2D(dx,dy));
        _cards[i+1].SetPosition(Vector2D(dx,dy));
    }
}

Card* Deck::WithdrawCard()
{
    if (_cards.size() == 0)
        return NULL;

    Card* tempCard = &_cards.back();
    _cards.pop_back();
    return tempCard;
}

void Deck::Shuffle()
{
    PlaySoundOnceS(SAMPLE_SHUFFLE_SOUND, 2.0);

    size_t size = _cards.size();

    for (size_t i = 0; i < _cards.size(); ++i)
    {
        int r1;
        do r1 = rand() % size;
        while (r1 == i);

        std::swap(_cards[r1], _cards[i]);
    }
}

void Deck::Draw(bool cardBack /* = true*/)
{
    for (uint i = 0; i < _cards.size(); i+=2) // Drawing each card makes a very big Deck so we only draw half of them
        _cards[i].Draw(0.0, false, cardBack);
}
