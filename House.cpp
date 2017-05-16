//
//  House.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "House.h"
#include "Functions.h"



House::House(){
    Name = "Dealer";
}

House::House(std::string Dealer){
    Name = Dealer;
}

House::~House(){
}



void House::GetInfo(){                 //Will only be used for first display of Dealers Cards
    std::cout << Name << ":" << std::endl;
    Hands[0].GetCards();
    std::cout << std::endl;
}

//House will only ever have 1 hand

void House::Decision(Deckof52 &Deck, bool Soft17){
    GetAllInfo();
    if(Hands[0].GetValue()==17 || Soft17){      //Check for Soft-17 when there's only 2 cards in the hand.
        std::cout << Name << " hits due to Soft-17." << std::endl;
        Hands[0].Cards.push_back(Deck.Hit());
        GetAllInfo();
    }
    while(Hands[0].PrintedValues().front()<17){
        std::cout << Name << " hits." << std::endl;
        Hands[0].Cards.push_back(Deck.Hit());
        GetAllInfo();
    }
    if(Hands[0].isBust()){
        std::cout << Name << " is BUST." << std::endl;
    }
    else if(!Hands[0].isBust()){
        std::cout << Name << " sticks." << std::endl;
        std::cout << Name << "'s hand is worth " << Hands[0].PrintedValues().front() << "." << std::endl;
    }
        
}





