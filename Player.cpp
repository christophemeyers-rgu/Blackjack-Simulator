//
//  Player.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "Player.h"
#include "Functions.h"

Player::Player(){
    Name = "";
    Hand Dummy;
    Hands.push_back(Dummy);
}

Player::Player(std::string PlayerName){
    Name = PlayerName;
}


void Player::GetAllInfo(){              //Print this while you have only 1 hand
    
    for(int i=0; i<Hands[0].Cards.size(); i++)      //Turn all facedown cards faceup
        if(!Hands[0].Cards[i].FaceUp)
            Hands[0].Cards[i].Flip();
    
    std::cout << Name << ":" << std::endl;
    Hands[0].GetCards();
    std::cout << '\t' << "(" << Hands[0].PrintedValues().front();
    if(Hands[0].PrintedValues().size()>1)
        std::cout << " or " << Hands[0].PrintedValues().back();
    std::cout << ")" << std::endl;
    std::cout << std::endl;
}



void Player::BlackJack(){       //Will only be used to display Blackjack, so there will only be 1 Hand
    std::cout << Name << ":" << std::endl;
    Hands[0].GetCards();
    std::cout << '\t' << "(21) => BLACKJACK!" << std::endl;
}


void Player::GetHand(int i){        //Basically GetAllInfo, only used for more than one Hand during decision
    std::cout << "Hand " << i+1 << ":" << std::endl;
    Hands[i].GetCards();
    std::cout << '\t' << "(" << Hands[i].PrintedValues().front();
    if(Hands[i].PrintedValues().size()>1)
        std::cout << " or " << Hands[i].PrintedValues().back();
    std::cout << ")" << std::endl;
    std::cout << std::endl;
}


void Player::SplitPairs(int i, Deckof52 &Deck){
    Card Dummy = Hands[i].Cards.back();
    Hands[i].Cards.pop_back();
    
    Hand NewHand(Dummy);
    Hands.push_back(NewHand);
    
    Hands[i].Cards.push_back(Deck.Hit());
    Hands[i+1].Cards.push_back(Deck.Hit());
}




