#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "owner.h"
#include "gameConsole.h"

using namespace std;

bool ifExists(const char *filename){
  ifstream file(filename);
  return (bool)file;
}

int main(int argc, char *argv[]){
  GameConsole start;

  bool deck1 = false;
  bool deck2 = false;
  bool n1 = false;
  bool n2 = false;
  string name1 = "";
  string name2 = "";
  bool testing = false;
  bool bonus = false;
  string input = "";

  for(int i = 0; i < argc; i++){
    if(string(argv[i])  == "-deck1" || string(argv[i])  == "-deck2"){
     i++;

     if(!ifExists(argv[i])){
       if(string(argv[i-1])  == "-deck1") cout << "deck1 ";
       if(string(argv[i-1])  == "-deck2") cout << "deck2 ";
       cout << "file doesn't exist or cannot be read. Terminating program" << endl;
       return 1;
     }

     ifstream deck(string(argv[i]));
     istream &deckStream = deck;

     if(string(argv[i-1]) == "-deck1"){
       start.initializeDeck1(deckStream);
       deck1 = true;
     }else{
       start.initializeDeck2(deckStream);
       deck2 = true;
     }
   }else if(string(argv[i]) == "-init"){
     i++;

     if(!ifExists(argv[i])){
       cout << "Init file doesn't exist or cannot be read. Terminating program" << endl;
       return 1;
     }
     ifstream commands(string(argv[i]));

     int numOfCommands = 0;

     while(!commands.eof()){
       string s;
       getline(commands, s);

       if(numOfCommands == 0){
         n1 = true;
         name1 = s;
       }else if(numOfCommands == 1){
         n2 = true;
         name2 = s;
       }else{
         input += s;
         input += "\n";
       }
       numOfCommands++;
     }

   }else if(string(argv[i])  == "-testing"){
     testing = true;
   } else if (string(argv[i])  == "-bonus") {
     bonus = true;
   }
  }

  start.game(deck1, deck2, n1, n2, name1, name2, testing, bonus, input);
}

