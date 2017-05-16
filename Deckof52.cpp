//
//  Deckof52.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "Deckof52.h"
#include <stdlib.h> //includes rand()

 

Deckof52::Deckof52(){
	Values.push_back("2");
	Values.push_back("3");
	Values.push_back("4");
	Values.push_back("5");
	Values.push_back("6");
	Values.push_back("7");
	Values.push_back("8");
	Values.push_back("9");
	Values.push_back("10");
	Values.push_back("J");
	Values.push_back("Q");
	Values.push_back("K");
	Values.push_back("A");
}

Deckof52::~Deckof52(){}


void Deckof52::FillDeck(){
    Card Dummy("A",1,true);
    for(int i=0; i<13; i++){
        for(int j=1; j<=4; j++){
            Dummy.Value = Values[i];
            Dummy.Suit = j;
            Cards.push_back(Dummy);
        }
    }
}



void Deckof52::ShowDeck(){
    int k=0;
    for(int i=0; i<13; i++){
        for(int j=0; j<4; j++){
            Cards[k].GetCard();
            std::cout << " ";
            k++;
        }
        std::cout << std::endl;
    }
}



void Deckof52::Shuffle(){
    Card Dummy;
    int k=0;
    for(int i=0; i<Cards.size(); i++){
        k = rand() % 52;        //assigns a random number between 0 and 51 (indeces of 52 cards)
        
        Dummy = Cards[i];       //Then swap cards at i and k by ordinary swap mechanism
        Cards[i] = Cards[k];
        Cards[k] = Dummy;
    }
}



Card Deckof52::Hit(){
    Card Dummy;                         //Creates Placeholder card
    
    Dummy = Cards.back();               //Take card from back
    Cards.pop_back();                   //Delete that card from deck
    if(!Dummy.FaceUp) Dummy.Flip();     //If for any reason it was FaceDown, flip
    return Dummy;                       //Return Card
}


