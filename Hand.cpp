//
//  Hand.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include <iostream>
#include <vector>

#include "Hand.h"


Hand::Hand(){
}

Hand::Hand(Card ACard){
    Cards.push_back(ACard);
}

Hand::~Hand(){
}


void Hand::GetCards(){
    for(int i=0; i<Cards.size(); i++){
        Cards[i].GetCard();
        std::cout << " ";
    }
}

int Hand::GetValue(){
    int Value=0;
    for(int i=0; i<Cards.size(); i++){
        Value += Cards[i].GetValue();
    }
    return Value;
}

int Hand::AceCount(){
    int AceCounter = 0;
    for(int i=0; i<Cards.size(); i++){
        if(Cards[i].Value.compare("A")==0) AceCounter++;
    }
    return AceCounter;
}






//The following function is for handling of multiple aces and their creation of multiple possible values of a hand. It returns a vector which will be filled up with up to 2 values that actually interest the player (there are never more than two, example: Hand of A,A -> only 12 and 2 are interesting, 22 is bust and therefore not considered when making further decisions).
std::vector<int> Hand::PrintedValues(){
    
    std::vector<int> HoldValues;
    
    //First off, if there are no aces, GetValue() is the only value of interest
    if(AceCount()==0){
        HoldValues.push_back(GetValue());
    }
    
    //If there is at least one Ace, it checks for the highest possible non bust value and "adds that to the front of the vector" (as vector was initially empty).
    else if(AceCount()>0){
        int i=0;
        while(i<=AceCount() && GetValue()-(i*10)>21) i++;
        if(i>AceCount()) i=AceCount(); //This is necessary in case the lowest possible value of the hand is still bust, then the while loop will increase i over AceCount and the only stored value would not make sense. This way, you will reset i to be AceCount and just save the lowest possible value, which is bust, but you need to save at least one value to return reasoning for win or loss in the game.
        HoldValues.push_back(GetValue()-(i*10));
        i++;
        
        //Then it searches for a second non bust value, if it is >0 and if there are sufficient aces for this value to exist. This value is then added to the back of the vector.
        if(i<=AceCount() && GetValue()-(i*10)>0)
            HoldValues.push_back(GetValue()-(i*10));
    }
    return HoldValues;
}

bool Hand::isBust(){
    if(PrintedValues().back()>21){ //If the last of all PrintedValues (this will be the lowest positive) is still bust, then the hand is bust, whatever you take your aces to be.
        return true;
    }
    else{
        return false;
    }
}
