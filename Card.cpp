//
//  Card.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "Card.h"



Card::Card(){
    Value= "";
    Suit= 1;
    FaceUp = true;
}

Card::Card(std::string CardValue, int CardSuit, bool ShowFace){
    Value= CardValue;
    Suit= CardSuit;
    FaceUp= ShowFace;
}

Card::~Card(){
    
}

void Card::GetCard(){
    if(FaceUp){
        std::cout << Value;
		switch(Suit){
		case 1:
			std::cout << "H" /*(char)3*/;
			break;
		case 2:
			std::cout << "S" /*(char)4*/;
			break;
		case 3:
			std::cout << "C" /*(char)5*/;
			break;
		case 4:
			std::cout << "D" /*(char)6*/;
			break;
		}

    }
    else if(!FaceUp){
        std::cout << "XX";
    }
}

int Card::GetValue(){
    if(Value.compare("J")==0 || Value.compare("Q")==0 || Value.compare("K")==0){
        return 10;
    }
    else if(Value.compare("A")==0){
        return 11;
    }
    else{
        int Number = atoi(Value.c_str());
        return Number;
    }
}

void Card::Flip(){
    if(FaceUp){
        FaceUp = false;
    }
    else if(!FaceUp){
        FaceUp = true;
    }
}
