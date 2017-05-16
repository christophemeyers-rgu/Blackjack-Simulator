//
//  Blackjack.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 02/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "Functions.h"
#include <limits.h>



bool Yes(std::string Y){
    if(Y.compare("Y")==0 || Y.compare("y")==0 || Y.compare("Yes")==0 || Y.compare("yes")==0 || Y.compare("YES")==0)
        return true;
    else return false;
}



void Pause(std::vector<HumanPlayer> HP){		//Will not pause if only computer players playing
	if(HP.size()!=0){
		std::cout << std::endl;
		system("read -p \"Press a key to continue...\" -n 1 -s");       //"Pause" in Windows
        std::cout << std::endl;
	}
}


void DealHands(Deckof52 &Deck, House &Dealer, std::vector<HumanPlayer> &HP, std::vector<ComputerPlayer> &CP){
    Card Dummy;
    
    Dummy = Deck.Hit();
    Dummy.Flip();                       //Dealer's first card needs to be FaceDown
    Dealer.Hands[0].Cards.push_back(Dummy);
    Dealer.Hands[0].Cards.push_back(Deck.Hit());
    
    for(int i=0; i<HP.size(); i++)      //Deal humans
        for(int j=0; j<2; j++)
            HP[i].Hands[0].Cards.push_back(Deck.Hit());
    
    
    for(int i=0; i<CP.size(); i++)      //Deal computers
        for(int j=0; j<2; j++)
            CP[i].Hands[0].Cards.push_back(Deck.Hit());
    
}


void ComputerDecision(std::vector<ComputerPlayer> &CP, Deckof52 &Deck, std::vector<HumanPlayer> HP){
    for(int i=0; i<CP.size(); i++)
        switch(i){
            case 0:
                std::cout << "--SIDNEY----------------------------------------" << std::endl;
                
                CP[i].Surrendered = false;          //Sidney doesn't Surrender
                CP[i].SidneyDecision(Deck);
				Pause(HP);
                break;
            case 1:
                std::cout << "--ALEX------------------------------------------" << std::endl;

                CP[i].Surrendered = false;          //Alex doesn't Surrender
                CP[i].AlexDecision(Deck);
				Pause(HP);
                break;
            case 2:
                std::cout << "--DARYL-----------------------------------------" << std::endl;

                CP[i].DarylDecision(Deck);
				Pause(HP);
                break;
            case 3:
                std::cout << "--SAM-------------------------------------------" << std::endl;

                CP[i].SamDecision(Deck);
				Pause(HP);
                break;
        }
}

void HumanEvaluation(std::vector<HumanPlayer> &HP, House &Dealer, bool SixFive){
    
    for(int i=0; i<HP.size(); i++){                     //For each player
        
        if(!HP[i].Surrendered){                         //Only if not surrendered
            
            for(int j=0; j<HP[i].Hands.size(); j++){    //For each hand
                
                std::cout << HP[i].Name << "'s hand";
                if(HP[i].Hands.size()>1)
                    std::cout << " No. " << j+1;
                if(HP[i].Hands[0].isBust())
                    std::cout << " is BUST!" << std::endl;
                else
                    std::cout << " is worth " << HP[i].Hands[j].PrintedValues().front() << ":" << std::endl;
                
                if(HP[i].BJ || (!HP[i].Hands[j].isBust() && (HP[i].Hands[j].PrintedValues().front()>Dealer.Hands[0].PrintedValues().front() || Dealer.Hands[0].isBust()))){
                    std::cout << "You win ";
                    HP[i].EvaluateWinnings(true, SixFive);
                }
                
                else if(!HP[i].Hands[j].isBust() && HP[i].Hands[j].PrintedValues().front()==Dealer.Hands[0].PrintedValues().front()){
                    std::cout << "You push and get back your £" << HP[i].Bet << " Bet." << std::endl;
                }
                
                else{
                    std::cout << "You lose ";
                    HP[i].EvaluateWinnings(false, SixFive);
                }
            }
        }
        
        std::cout << std::endl;
    }
}


void ComputerEvaluation(std::vector<ComputerPlayer> &CP, House &Dealer, bool SixFive){
    for(int i=0; i<CP.size(); i++){
        if(!CP[i].Surrendered){    //Only do something if not surrendered
            
            std::cout << CP[i].Name << "'s hand";
            if(CP[i].Hands[0].isBust())
                std::cout << " is BUST!" << std::endl;
            else
                std::cout << "is worth " << CP[i].Hands[0].PrintedValues().front() << ":" << std::endl;

            
            if(CP[i].BJ || (!CP[i].Hands[0].isBust() && (CP[i].Hands[0].PrintedValues().front()>Dealer.Hands[0].PrintedValues().front() || Dealer.Hands[0].isBust()))){
                std::cout << "You win ";
                CP[i].EvaluateWinnings(true, SixFive);
            }
            
            else if(!CP[i].Hands[0].isBust() && CP[i].Hands[0].PrintedValues().front()==Dealer.Hands[0].PrintedValues().front()){
                std::cout << "You push and get back your £" << CP[i].Bet << " Bet." << std::endl;
            }
            
            else{
                std::cout << "You lose ";
                CP[i].EvaluateWinnings(false, SixFive);
            }
        }
        
        std::cout << std::endl;
    }
}







