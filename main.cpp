//
//  main.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 02/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <time.h>   //includes time(), a function which returns the number of seconds since a set date on the computers interior clock.

#include "Functions.h"
#include "Deckof52.h"
#include "House.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Game.h"


//NEED TO FIX:
//CHARACTERS FOR CARD SUITS     ok!
//POUND SIGNS
//SYSTEM("PAUSE") DOESN'T WORK


int main(){

	std::cout << "Let's play a game of Blackjack!" << std::endl;
	std::cout << std::endl;

	//Setup

	//Game MyGame;
	Hand AHand;
	Deckof52 Deck;
	House Dealer("Dealer");
	HumanPlayer APlayer("YourName", 1000);
	ComputerPlayer BPlayer("HisName", 1000);

	std::vector<HumanPlayer> HP;
	std::vector<ComputerPlayer> CP;

	int NumberofHumans, NumberofComputers, ComputerRounds=0;
	double Input;				//This will take all numeric inputs and then be converted into integers if needed


	std::string Play="Yes";               //Used to determine whether a new round should be started or not
	std::string Soft17, SixFive;          //Decide on which rules to play.


	srand(time(NULL));
	//sets seed value for rand() in shuffle to be different each time the program gets executed, as the time passed since the set date for the time() function has since changed. This allows for good pseudo random values to be generated and a different set of shuffles each time the program is executed.


	std::cout << "Our deck of cards: " << std::endl;
	Deck.FillDeck();
	Deck.ShowDeck();
	Deck.Shuffle();
	std::cout << std::endl;




	//Number of human players?
	std::cout << "How many human players are there? (up to 5) ";
	std::cin >> Input;
	while(Input>5 || Input<0 || std::cin.fail()){		//Looks for wrong input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(),'\n');
		std::cout << "Please enter a number between 0 and 5: ";
		std::cin >> Input;
	}
	NumberofHumans = Input;


	//Number of computer players?
	std::cout << "How many computer players are there? (up to 2) ";
	std::cin >> Input;
	while(Input>2 || Input<0 || std::cin.fail()){		//Looks for wrong input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(),'\n');
		std::cout << "Please enter a number between 0 and 2: ";
		std::cin >> Input;
	}
	NumberofComputers = Input;


	//If no humans, ask for number of rounds to play
	if(NumberofHumans<1 && NumberofComputers>0){
		do{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(),'\n');
			std::cout << "Please enter a number of rounds for the computer players to play: ";
			std::cin >> Input;
		}while(std::cin.fail());			//Looks for wrong input
		ComputerRounds = Input;
	}



	std::cout << std::endl;


	//Name all human players
	for(int i=0; i<NumberofHumans; i++){
		HP.push_back(APlayer);              //Creates a player
		HP[i].Hands.push_back(AHand);       //Creates a first hand
		do{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(),'\n');
			std::cout << "What's your name, Player " << i+1 << "?";
			std::cin >> HP[i].Name;
		}while(std::cin.fail());			//Looks for wrong input
	}


	//Name all computer players
	for(int i=0; i<NumberofComputers; i++){
		CP.push_back(BPlayer);              //Creates a player
		CP[i].Hands.push_back(AHand);       //Creates a first hand
		switch(i){
		case 0:
			CP[i].Name = "Sidney";
			break;
		case 1:
			CP[i].Name = "Alex";
			break;
		case 2:
			CP[i].Name = "Daryl";
			break;
		case 3:
			CP[i].Name = "Sam";
			break;
		}
	}


	//If game will be started, ask for rules
	if(NumberofHumans>0 || (NumberofComputers>0 && ComputerRounds>0)){
		std::cout << std::endl;
		std::cout << "Play Soft-17 Rule? (y/n)";
		std::cin >> Soft17;
		std::cout << "Play 6:5 Blackjack? (y/n)";
		std::cin >> SixFive;
	}



	//Keep playing, while humans are playing or while computers have rounds to play
	while(NumberofHumans>0 || (NumberofComputers>0 && ComputerRounds>0)){

		SimpleRound(Deck, Dealer, HP, CP, Yes(Soft17), Yes(SixFive));


		for(int i=0; i<HP.size(); i++){

			if(HP[i].BankRoll>0){   //If you still have Money

				std::cout << HP[i].Name << ", play again? (y/n) ";
				std::cin >> Play;
				std::cout << std::endl;

				if(!Yes(Play)){
					HP.erase(HP.begin()+i);
					NumberofHumans--;
					if(HP.size()>0) i--; //Set index back by 1, as all players' indeces will move one down
				}

			}
			else{                   //You're broke

				std::cout << HP[i].Name << ", you have run out of money! Thanks for playing!" << std::endl;
				std::cout << std::endl;

				HP.erase(HP.begin()+i);
				NumberofHumans--;
				if(HP.size()>0) i--;
			}
		}



		if(NumberofHumans==0 && NumberofComputers!=0 && ComputerRounds!=0){
			ComputerRounds--;
		}
		if(NumberofHumans==0 && NumberofComputers!=0 && ComputerRounds==0){
			do{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(),'\n');
				std::cout << "Please enter a number of rounds for the computer players to play: ";
				std::cin >> ComputerRounds;
			}while(std::cin.fail());			//Looks for wrong input
		}

		std::cout << std::endl;
		

	}

	


	return 0;

}

