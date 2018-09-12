#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "owner.h"
#include "gameConsole.h"
#include "window.h"

using namespace std;

GameConsole::GameConsole(){
  player1.addOpponent(&player2);
  player2.addOpponent(&player1);
}

GameConsole::~GameConsole(){}

void GameConsole::initializeDeck1(istream &deckStream){
  player1.initializeDeck(deckStream);
}

void GameConsole::initializeDeck2(istream &deckStream){
  player2.initializeDeck(deckStream);
}

void GameConsole::game(bool deck1, bool deck2, bool n1, bool n2, string name1, string name2, bool testing, bool bonus, string input){
  player1.setTesting(testing);
  player2.setTesting(testing);

  Xwindow* w;
  if(bonus) {
    w = new Xwindow();
    player1.attach_window(w);
    player2.attach_window(w);
  }

  if(!deck1){
    ifstream deck("default.deck");

    istream &inputStream = deck;
    player1.initializeDeck(inputStream);
  }
  if(!deck2){
    ifstream deck("default.deck");

    istream &inputStream = deck;
    player2.initializeDeck(inputStream);
  }

  if(!n1){
    if(!(cin >> name1)) return;
    player1.rename(name1);
  }else{
    player1.rename(name1);
  }
  if(!n2){
    if(!(cin >> name2)) return;
    player2.rename(name2);
  }else{
    player2.rename(name2);
  }

  srand(time(nullptr)); //use for random generate

  if(!testing){
    player1.shuffle();
    player2.shuffle();
  }

  player1.draw(4);
  player2.draw(4);

  int whosTurn = 1;
  istringstream ss(input);
  int turn = 1;

  while(true){

    if(player1.lose() && player2.lose()){
      cout << "Tie" << endl;
      return;
    }else if(player1.lose()){
      cout << "Player 2 win" << endl;
      return;
    }else if(player2.lose()){
      cout << "Player 1 win" << endl;
      return;
    }

    if(ss.eof()){
      getline(cin, input);
    }else{
      getline(ss, input);
    }

    string i;
    istringstream ss2(input);

    if(!(ss2 >> i) && turn > 2){
      cerr << "Invalid Command. Try again" << endl;
      cin.clear();
      cin.ignore();
    }

    if(i == "help"){
      cout << endl;
      cout << "Commands: help -- Display this message." << endl;
      cout << "          end -- End the current player's turn" << endl;
      cout << "          quit -- End the game." << endl;
      cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
      cout << "          attack minion -- Orders minion to attack the opponent." << endl;
      cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
      cout << "          use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
      cout << "          inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
      cout << "          hand -- Describe all cards in your hand." << endl;
      cout << "          board -- Describe all cards on the board." << endl;
      cout << endl;
    }else if(i == "end"){

      if(whosTurn == 1){
        whosTurn = 2;
        player1.endTurn();
        player2.draw(1);
      }else{
        whosTurn = 1;
        player2.endTurn();
        player1.draw(1);
      }

    }else if(i == "quit"){
      cout << "Thanks for playing" << endl;
      return;
    }else if(i == "draw"){

      if(testing){
        if(whosTurn == 1){
          player1.draw(1);
        }else{
          player2.draw(1);
        }
      }else{
        cout << "Not in testing mode, cannot use this command." << endl;
      }

    }else if(i == "discard"){

      if(testing){
        int card;
        if(!(ss2 >> card)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        if(whosTurn == 1){
          player1.discard(card-1);
        }else{
          player2.discard(card-1);
        }
      }else{
        cout << "Not in testing mode, cannot use this command." << endl;
      }

    }else if(i == "attack"){
      int minion;
      int target;
      int numOfCommands = 0;

      while(ss2 >> i){
        numOfCommands++;
      }

      ss2.str(input);
      ss2.clear();
      ss2.seekg(0);
      ss2 >> i; //get rite of first word "attack"

      if(numOfCommands == 1){
        if(!(ss2 >> minion)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        if(whosTurn == 1){
          player1.attack(minion-1);
        }else{
          player2.attack(minion-1);
        }
      }else if(numOfCommands == 2){
        if(!(ss2 >> minion >> target)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        if(whosTurn == 1){
          player1.attack(minion-1, target-1);
        }else{
          player2.attack(minion-1, target-1);
        }
      }else{
        cerr << "Invalid Index. Try again." << endl;
        continue;
      }

    }else if(i == "play"){
      int minion;
      int player;
      int target;
      int numOfCommands = 0;

      while(ss2 >> i){
        numOfCommands++;
      }

      ss2.str(input);
      ss2.clear();
      ss2.seekg(0);
      ss2 >> i;

      if(numOfCommands == 1){
        if(!(ss2 >> minion)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        if(whosTurn == 1){
          player1.play(minion-1);
        }else{
          player2.play(minion-1);
        }
      }else if(numOfCommands == 3){
        string t;
        if(!(ss2 >> minion >> player)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        ss2 >> t;
        if(t == "r"){
          target = 6;
        }else{
          ss2.str(t);
          ss2.clear();
          ss2.seekg(0);
          if(!(ss2 >> target)){
            cerr << "Invalid Index. Try again." << endl;
            continue;
          }
        }

        if(whosTurn == 1){
          player1.play(minion-1, player, target-1);
        }else{
          player2.play(minion-1, player, target-1);
        }
      }else{
        cerr << "Invalid Index. Try again." << endl;
        continue;
      }

    }else if(i == "use"){
      int minion;
      int player;
      int target;
      int numOfCommands = 0;

      while(ss2 >> i){
        numOfCommands++;
      }

      ss2.str(input);
      ss2.clear();
      ss2.seekg(0);
      ss2 >> i;

      if(numOfCommands == 1){
        if(!(ss2 >> minion)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        if(whosTurn == 1){
          player1.use(minion-1);
        }else{
          player2.use(minion-1);
        }
      }else if(numOfCommands == 3){
        string t;
        if(!(ss2 >> minion >> player)){
          cerr << "Invalid Index. Try again." << endl;
          continue;
        }

        ss2 >> t;
        if(t == "r"){
          target = 6;
        }else{
          ss2.str(t);
          ss2.clear();
          ss2.seekg(0);
          if(!(ss2 >> target)){
            cerr << "Invalid Index. Try again." << endl;
            continue;
          }
        }


        if(whosTurn == 1){
          player1.use(minion-1, player, target-1);
        }else{
          player2.use(minion-1, player, target-1);
        }
      }else{
        cerr << "Invalid Index. Try again." << endl;
        continue;
      }

    }else if(i == "inspect"){
      int num;
      if(!(ss2 >> num)){
        cerr << "Invalid Index. Try again." << endl;
        continue;
      }

      if(whosTurn == 1){
        player1.inspect(num-1);
      }else{
        player2.inspect(num-1);
      }

    }else if(i == "hand"){

      if(whosTurn == 1){
        player1.seeHand();
      }else{
        player2.seeHand();
      }

    }else if(i == "board"){

      if(whosTurn == 1){
        cout << player1;
      }else{
        cout << player2;
      }
    }else{
      if(turn > 2){
        cerr << "Invalid Command. Try again." << endl;
      }
    }
    turn ++;
  }
  delete w;
}

