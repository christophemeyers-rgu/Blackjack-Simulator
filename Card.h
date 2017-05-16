//
//  Card.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__Card__
#define __Blackjack_Simulator__Card__

#include <iostream>
#include <string>


class Card{
public:
    Card();
    Card(std::string CardValue, int CardSuit, bool ShowFace);
    ~Card();
    
    void GetCard();
    int GetValue();
    void Flip();
    
    std::string Value;
	int Suit;
    bool FaceUp;
};



#endif /* defined(__Blackjack_Simulator__Card__) */
