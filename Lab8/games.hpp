#ifndef CS3_LAB_8_Part_2_
#define CS3_LAB_8_Part_2_

// Nicholas A Moore
// CSIII
// Lab 8
// Part II
// 03/12/2023

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
    Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_ = 0;

        initializeGame();

        for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
            makeMove(i);
            if (i == playersCount_ - 1)
                ++movesCount_;
        }
        printWinner();
    }

    virtual ~Game() {}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
                    // returns true if winner is decided
    static const int noWinner = -1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
    // implementing concrete methods
    void initializeGame() {
        playersCount_ = rand() % numPlayers_ + 1; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Monopoly, player " << playerWon_ << " won in "
            << movesCount_ << " moves." << endl;
    }

private:
    static const int numPlayers_ = 8; // max number of players
    static const int minMoves_ = 20; // nobody wins before minMoves_
    static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayers_; // initalize players
        for (int i = 0; i < numPlayers_; ++i)
            experience_[i] = rand() % maxExperience_ + 1;
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = (rand() % maxMoves_) / experience_[player];
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Chess, player " << playerWon_
            << " with experience " << experience_[playerWon_]
            << " won in " << movesCount_ << " moves over"
            << " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
            << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 2; // nobody wins before minMoves_
    static const int maxMoves_ = 100; // somebody wins before maxMoves_
    static const int maxExperience_ = 5; // player's experience
                               // the higher, the greater probability of winning
    int experience_[numPlayers_];
};

class Dice : public Game {
public:

    void initializeGame() {
        playersCount_ = numPlayers_; // Always two players, one actual, one computer
    }

    int diceRoll() {
        int retVal;
        retVal = rand() % diceVal_ + 1; // random num 1-6
        return retVal;
    }

    void makeMove(int player) {

        if (player == 0) { // computer
            std::cout << "Round: " << movesCount_ + 1 << ' ' << "Computer Rolled: ";
            if (movesCount_ == 0 || computerScore_ < playerScore_) { // first round, move must be made otherwise, only when losing
                computerScore_ = 0; // reset
                computerPassed_ = false; // reset
                for (int i = 0; i < numOfRolls_; ++i) { // computers turn
                    currentRoll_ = diceRoll(); // roll a dice
                    std::cout <<  currentRoll_ << ' '; // print
                    computerScore_ += currentRoll_; // add to total score
                }
                std::cout << "Computer's Score: " << computerScore_ << std::endl;
            }
            else {
                computerPassed_ = true; // flag to compare against player
                std::cout << "Computer Passed Turn " << "Computer's Score is: " << computerScore_ << std::endl;
            }

        }

        if (player == 1) { // player
            std::cout << "You rolled: ";
                if (rollAgain_ != 'n') {
                    playerScore_ = 0; // reset
                    playerPassed_ = false;
                    for (int i = 0; i < numOfRolls_; ++i) {
                        currentRoll_ = diceRoll(); // get roll
                        std::cout << currentRoll_ << ' '; // print roll
                        playerScore_ += currentRoll_; // assign to score
                    }
                    std::cout << "Your score: " << playerScore_ << std::endl;
                    if (movesCount_ != 2) { // not last turn
                        std::cout << "Roll again? [y/n]" << std::endl;
                        std::cin >> rollAgain_;
                        if (rollAgain_ != 'n') {
                            playerPassed_ = false;
                        }
                        else { // set flag
                            playerPassed_ = true;
                        }
                    }
                }
                else {
                    std::cout << "Turn Passed your score is: " << playerScore_ << std::endl;
                    if (computerPassed_ == true && playerPassed_ == true) {
                        computerScore_ >= playerScore_ ? playerWon_ = 0 : playerWon_ = 1; // computer gets win in tie
                    }
                    else if (movesCount_ != 2) { // not last turn
                        std::cout << "Roll again? [y/n]" << std::endl;
                        std::cin >> rollAgain_;
                    }
                }

                if (movesCount_ == 2 || computerPassed_ == true && playerPassed_ == true) {
                    computerScore_ >= playerScore_ ? playerWon_ = 0 : playerWon_ = 1; // computer gets win in tie
                }
        }


    }

    void printWinner() {
        if (playerWon_ == 0) { // 0 == computer
            std::cout << "Computer won with a score of: " << computerScore_;
        }
        else { // 1 == player
            std::cout << "You won with a score of: " << playerScore_;
        }
    }


private:
    static const int numPlayers_ = 2;
    static const int maxRounds_ = 3;
    static const int diceVal_ = 6;
    static const int numOfRolls_ = 5;

    int computerScore_ = 0;
    int playerScore_ = 0;
    int currentRoll_ = 0;

    bool computerPassed_ = false; // flags for ending game
    bool playerPassed_ = false;

    char rollAgain_ = 'y'; // for player to roll again or not
};


#endif
