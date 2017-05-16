//
//  HumanPlayer.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 12/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "HumanPlayer.h"
#include "Functions.h"


HumanPlayer::HumanPlayer(std::string PlayerName, double InitialMoney):Player(PlayerName){
    BankRoll = InitialMoney;
}


void HumanPlayer::InsuranceDecision(){
    std::string DoYou;
    double Money;
    
    
    std::cout << Name << ", do you want to place an insurance bet on your hand? (y/n)";
    std::cin >> DoYou;
    if(Yes(DoYou)){
        Insured = true;
        
        std::cout << "How much do you want to bet as insurance? (up to £" << 0.5*Bet << ") £";
        std::cin >> Money;
        while(Money<=0 || Money>(0.5*Bet) || std::cin.fail()){		//In case of bad input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(),'\n');
            std::cout << "Please enter a bet higher than £0 up to £" << 0.5*Bet << ": £";
            std::cin >> Money;
        }
        InsuranceBet = Money;
    }
    else Insured = false;
    
    std::cout << std::endl;
}



void HumanPlayer::Decision(Deckof52 &Deck){
    std::string HitMe, Surrender, DoubleDown, Split;
    
    //IF NO BLACKJACK//
    if(Hands[0].GetValue()!=21){        //Only 1 Hand at beginning of this function
        GetAllInfo();
        
		//Only ask for surrendering if not insured.
        if(!Insured){
            std::cout << "Surrender? (y/n)";	
            std::cin >> Surrender;
        }
        
        //SURRENDERING//
        if(Yes(Surrender)){
            Surrendered=true;
            std::cout << "You get back half of your £" << Bet << "." << std::endl;
            std::cout << std::endl;
            BankRoll -= 0.5*Bet;
        }//END OF SURRENDERING//

		//NOT SURRENDERING//
        else{
            Surrendered=false;
            
            for(int i=0; i<Hands.size(); i++){
                
                if(Hands.size()>1){
                    GetHand(i);     //Print hand in question if there are multiple hands
                }
                
                
				//SPLIT PAIRS//
                if(Hands[i].Cards[0].Value.compare(Hands[i].Cards[1].Value)==0){
                    std::cout << "Split Pairs? (y/n)";
                    std::cin >> Split;
                    if(Yes(Split)){
                        SplitPairs(i, Deck);
                        std::cout << "You put down the same bet of £" << Bet << " on your new hand." << std::endl;
                        std::cout << std::endl;
                        GetHand(i);
                    }
                }
                //END OF SPLITTING//
				
				
				std::cout << "Double down? (y/n)";
                std::cin >> DoubleDown;
                
				//DOUBLE DOWN//
                if(Yes(DoubleDown)){
                    Bet += Bet;
                    std::cout << "Your bet has increased to £" << Bet << " and you will receive one more card." << std::endl;
                    Hands[i].Cards.push_back(Deck.Hit());
                    std::cout << std::endl;
                    GetAllInfo();
                    HitMe = "N";
                }//END OF DOUBLE DOWN//

				//NO DOUBLING DOWN//
                else{
                    std::cout << "Hit? (y/n)";
                    std::cin >> HitMe;
                }//END OF NOT DOUBLING DOWN//
                
                
                
				//HIT LOOP//
                while(Yes(HitMe)){
                    std::cout << std::endl;
                    std::cout << Name << " hits." << std::endl;
                    Hands[i].Cards.push_back(Deck.Hit());
                    GetAllInfo();
                    
					//IF NOT BUST//
                    if(Hands[i].PrintedValues().front()<21){
                        std::cout << "Hit? (y/n)";
                        std::cin >> HitMe;
                    }
					//IF BUST, NO MORE HITTING//
                    else
                        HitMe="N";

                }//END OF HIT LOOP//

            }
            
            std::cout << std::endl;
            for(int i=0; i<Hands.size(); i++){
                std::cout << Name << "'s hand";
                if(Hands.size()>1)
                    std::cout << " No. " << i+1;
                if(!Hands[i].isBust())
                    std::cout << " is worth " << Hands[i].PrintedValues().front() << "." << std::endl;
                else
                    std::cout << " is BUST." << std::endl;
                
            }
        }//END OF NOT SURRENDERED
    }//END OF NO BLACKJACK DECISIONS//

	//else print blackjack statement
    else
        BlackJack();
}




void HumanPlayer::EvaluateWinnings(bool Won, bool SixFive){
    if(Won){
        if(Hands[0].Cards.size()==2 && Hands[0].GetValue()==21){  //Blackjack Payout
            if(SixFive){
                BankRoll += (6./5.)*Bet;
                std::cout <<  "£" << (6./5.)*Bet << "." << std::endl;
            }
            else{
                BankRoll += (3./2.)*Bet;
                std::cout << "£" << (3./2.)*Bet << "." << std::endl;
            }
        }
        else{                                   //Normal Win Payout
            BankRoll += Bet;
            std::cout << "£" << Bet << "." << std::endl;
        }
    }
    else{                                       //Loss
        BankRoll -= Bet;
        std::cout << "£" << Bet << "." << std::endl;
    }
}
