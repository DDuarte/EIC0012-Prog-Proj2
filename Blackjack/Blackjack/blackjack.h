#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "game.h"
#include "player.h"
#include "deck.h"

#include <vector>
#include <queue>

const unsigned int NUM_ACTIVE_PLAYERS = 4;

class Deck;
class Player;

class BlackJack : public Game
{
public:
    BlackJack();
    ~BlackJack();

    void RegisterPlayer(std::string name, double balance);
    std::vector<Player*> CheckWinners() const;

    virtual void Initialize();
    virtual void LoadContents();
    virtual void Update();
    virtual void Draw();
    virtual void UnloadContents();

    void ReadPlayersFromFile();

private:
    std::vector<Player> _players;
    std::queue<Player*> _waitingPlayers;

    Player** _activePlayers;

    void SelectPlayers();

    Deck* _deck;
};

#endif // BLACKJACK_H