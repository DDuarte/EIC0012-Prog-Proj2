#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hand.h"
#include "gameExceptions.h"
#include "utilities.h"

#include <string>
#include <vector>
#include <fstream>

class Card;

class Player
{
public:
    Player();
    Player(std::string name, double balance);
    Player(std::ifstream);

    std::string GetName() const { return _name; };
    double GetBalance() const { return _balance; };
    double GetBet() const { return _bet; };
    Hand GetHand() const { return _hand; };
    static std::string GetPlayersFileName() { return _playersFileName; };

    void SetName(std::string name) { if (name.size() > 0) _name = name; };
    void SetBalance(double balance) { _balance = balance; };
    void SetBet(double bet) { (bet > 0 ? _bet = bet : throw InvalidBetException("Invalid bet exception at Player::IncreaseBet(double bet)!")); };
    void IncreaseBet(double bet) { (bet > 0 ? _bet += bet : throw InvalidBetException("Invalid bet exception at Player::IncreaseBet(double bet)!")); };
    static void SetPlayersFileName(std::string playersFileName)
    {
        if (!Utilities::FileExists(playersFileName.c_str()))
        {
            std::fstream out (playersFileName.c_str(), std::ios::out | std::ios::binary);
            if (!out.is_open())
                ;//throw exception
            out.close();
        }

        _playersFileName = playersFileName;
    }

    bool IsBusted() { return GetHand().IsBusted(); }         
    bool IsBlackjack() { return GetHand().IsBlackjack(); } 

    bool ReadBinary(std::ifstream& in);
    void WriteBinary(std::ofstream& out);

    

private:
    std::string _name;
    double _balance;
    double _bet;
    Hand _hand;
    static std::string _playersFileName;
};

#endif // PLAYER_H
