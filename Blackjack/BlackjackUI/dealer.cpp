/*!
 * \file dealer.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "s_game.h"
#include "dealer.h"
#include "hand.h"
#include "deck.h"
#include "fonts.h"
#include "localization.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

Dealer::Dealer(S_Game* game)
{
    _game = game;
    _hand = Hand(DEALER_POSITION, true);
}

void Dealer::Draw()
{
    static const char* name = "Dealer";

    al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 10 + 105, 0, name);

    if (IsBusted())
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 242, 0),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 30 + 105, 0, GetStr(STR_BUSTED).c_str());
    else if (IsBlackjack())
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 242, 0),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 30 + 105, 0, "BlackJack'ed");
    else if (_game->GetState() > GAME_STATE_DEALER_TURN)
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 242, 0),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 30 + 105, 0, GetStr(STR_STOOD).c_str());

    _hand.Draw();
}

void Dealer::NewCard( Card* card )
{
    //if (_hand.GetNumberOfCards() == 0)
    //    _hand.AddCard(new Card(CARD_SUIT_SPADES, CARD_RANK_ACE));
    //else _hand.AddCard(new Card(CARD_SUIT_SPADES, CARD_RANK_TEN));

    _hand.AddCard(card);
}

bool Dealer::Hit()
{
    if (Card* card = _game->GetDeck()->WithdrawCard())
    {
        NewCard(card);
        _game->DealerHit(this, card);
    }
    //else
    //    _game->HandleOutOfCards(); // Mathematically impossible to happen
    //    
    return true;
}
