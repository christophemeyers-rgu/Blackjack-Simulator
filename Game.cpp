//
//  Game.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "Game.h"
#include "Functions.h"




void SimpleRound(Deckof52 &Deck, House &Dealer, std::vector<HumanPlayer> &HP, std::vector<ComputerPlayer> &CP, bool Soft17, bool SixFive){
    
    
    
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "--NEW ROUND-------------------------------------" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    
    std::cout << std::endl;
    
    
    
    
    std::cout << "--BETS------------------------------------------" << std::endl;
    
	//HUMAN BETS//
    for(int i=0; i<HP.size(); i++){
        std::cout << HP[i].Name << " has £" << HP[i].BankRoll << ". How much do you want to bet? (£1-10) £";
        std::cin >> HP[i].Bet;

        while(HP[i].Bet<1 || HP[i].Bet>10 || std::cin.fail()){		//In case of bad input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(),'\n');
            std::cout << "Please make a bet between £1-10: £";
            std::cin >> HP[i].Bet;
        }
    }//END OF HUMAN BETS



	//COMPUTER BETS//
    for(int i=0; i<CP.size(); i++){    
        CP[i].Bet = 1;             //For now we'll have them all bet the minimum of £1
        
        std::cout << CP[i].Name << " has £" << CP[i].BankRoll << ". He bets £" << CP[i].Bet << std::endl;
    }//END OF COMPUTER BETS//
    
    
    
    
    
    std::cout << "--CARDS-----------------------------------------" << std::endl;

    
    std::cout << std::endl;
    std::cout << "Dealing cards." << std::endl;
    std::cout << std::endl;
    
    //DEALING
    DealHands(Deck, Dealer, HP, CP);
    
    
    
    //PRINT DEALER
    Dealer.GetInfo();
    
    std::cout << std::endl;
    
    
    
    //PRINT HUMANS//
    for(int i=0; i<HP.size(); i++){
        if(HP[i].Hands[0].GetValue()==21){	//CHECK FOR BLACKJACK
            HP[i].BJ = true;
            HP[i].BlackJack();
        }
        else{
            HP[i].BJ = false;
            HP[i].GetAllInfo();
        }
    }//END OF PRINTING HUMANS//
    

    std::cout << std::endl;

    
    //PRINTING COMPUTERS//
    for(int i=0; i<CP.size(); i++){
        if(CP[i].Hands[0].GetValue()==21){	//CHECK FOR BLACKJACK
            CP[i].BJ = true;
            CP[i].BlackJack();
        }
        else{
            CP[i].BJ = false;
            CP[i].GetAllInfo();
        }
    }//END OF PRINTING COMPUTERS//
    
    
    Pause(HP);


    //INSURANCE BREAK//
    if(Dealer.Hands[0].Cards[1].Value.compare("A")==0){
        
        std::cout << "--INSURANCE?-----------------------------------" << std::endl;
        
        for(int i=0; i<HP.size(); i++)
            HP[i].InsuranceDecision();
    }
    else
        for(int i=0; i<HP.size(); i++)
            HP[i].Insured = false;
    //END OF INSURANCE BREAK//
	
    
    
    //START OF SPLIT UP FOR NO DEALER BLACKJACK//
    if(Dealer.Hands[0].GetValue()!=21){
        
        
        
        //INSURANCE CASH IN//
        if(Dealer.Hands[0].Cards[1].Value.compare("A")==0){
            std::cout << Dealer.Name << " has no blackjack, all insurance bets lose." << std::endl;
            std::cout << std::endl;
            
            for(int i=0; i<HP.size(); i++)
                if(HP[i].Insured)
                    HP[i].BankRoll -= HP[i].InsuranceBet;

			Pause(HP);
        }//END OF INSURANCE CASH IN//
        
        
		
        
        //HUMAN PLAYERS' TURNS//
        for(int i=0; i<HP.size(); i++)
            if(HP[i].Hands[0].GetValue()!=21){
                std::cout << "--PLAYER " << i+1 << "--------------------------------------" << std::endl;
                HP[i].Decision(Deck);

				Pause(HP);
            }
            else
                HP[i].Surrendered = false;
		//END OF HUMAN PLAYERS' TURNS//
        

        
        //COMPUTER PLAYERS' TURN//
        ComputerDecision(CP, Deck, HP);
        
        

        
        //CHECK HOW MANY DID NOT SURRENDER//
        long int PlayersNotSurrendered = HP.size() + CP.size();
        
        for(int i=0; i<HP.size(); i++){
            if(HP[i].Surrendered)
                PlayersNotSurrendered--;
        }
        for(int i=0; i<CP.size(); i++){
            if(CP[i].Surrendered)
                PlayersNotSurrendered--;
        }//END OF SURRENDER CHECK//
        
        
        
        //If there is at least one player left that did not surrender,
        //the dealer will have his turn and scores will be evaluated.
        
		//AT LEAST 1 PLAYER LEFT//
        if(PlayersNotSurrendered>0){

			//DEALER DECISION
            std::cout << "--DEALER----------------------------------------" << std::endl;
            Dealer.Decision(Deck, Soft17);
            //END OF DEALER DECISION


            Pause(HP);


            //EVALUATION OF SCORES//
            std::cout << "------------------------------------------------" << std::endl;
            std::cout << "--SCORES----------------------------------------" << std::endl;
            

            //PRINT DEALER'S SCORE//
            if(Dealer.Hands[0].isBust())
                std::cout << Dealer.Name << " is BUST!" << std::endl;
            else
                std::cout << Dealer.Name << ": " << Dealer.Hands[0].PrintedValues().front() << std::endl;
            //END OF PRINT//

            std::cout << std::endl;
            
			//HUMAN EVALUATION//
            HumanEvaluation(HP, Dealer, SixFive);
            
			//COMPUTER EVALUATION//
            ComputerEvaluation(CP, Dealer, SixFive);
            
			
			//END OF EVALUATIONS//

        }//END OF AT LEAST 1 PLAYER LEFT//

        else//IF ALL SURRENDERED//
            std::cout << "All Players have surrendered, the round ends." << std::endl;
        //END OF IF ALL SURRENDERED//

    }//END OF DEALER HAS NO BLACKJACK//
    
    //DEALER HAS BLACKJACK//
    else if (Dealer.Hands[0].GetValue()==21){
        
		//Skip all decisions


		//DEALER BLACKJACK PRINT//
        std::cout << "--DEALER----------------------------------------" << std::endl;
        Dealer.Hands[0].Cards[0].Flip();
        Dealer.BlackJack();
        //END OF DEALER BLACKJACK PRINT//


		//INSURANCE BETS WIN//
        if(Dealer.Hands[0].Cards[1].Value.compare("A")==0){
            for(int i=0; i<HP.size(); i++){
                std::cout << HP[i].Name << " you win £" << HP[i].InsuranceBet << " on insurance!" << std::endl;
                HP[i].BankRoll += HP[i].InsuranceBet;
            }
            std::cout << std::endl;
        }//END OF INSURANCE EVALUATION//


		Pause(HP);


        //EVALUATION OF SCORES//
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "--SCORES----------------------------------------" << std::endl;
        
        
		//DEALER SCORE PRINT//
        std::cout << Dealer.Name << ": BLACKJACK!" << std::endl;
        
		
		std::cout << std::endl;
        
        
		//HUMAN EVALUATION//
		for(int i=0; i<HP.size(); i++){
            std::cout << HP[i].Name;
            if(HP[i].BJ){
                std::cout << ", you push and get back your £" << HP[i].Bet << " Bet." << std::endl;
            }
            else{
                std::cout << ", you lose ";
                HP[i].EvaluateWinnings(false, SixFive);
            }
        }//END OF HUMAN EVALUATION//

        
		//COMPUTER EVALUATION//
        for(int i=0; i<CP.size(); i++){
            std::cout << CP[i].Name;
            if(CP[i].BJ){
                std::cout << ", you push and get back your £" << CP[i].Bet << " Bet." << std::endl;
            }
            else{
                std::cout << ", you lose ";
                CP[i].EvaluateWinnings(false, SixFive);
            }
        }//END OF COMPUTER EVALUATION//
        
    }//END OF DEALER HAS BLACKJACK//

    
    
	Pause(HP);
	


    std::cout << "--BANKROLL UPDATES------------------------------" << std::endl;

    
    Hand AHand;     //Need to create a first hand after clearing, because functions rely on it existing.

	//CLEAR AND GIVE BANKROLL OF HUMANS//
    for(int i=0; i<HP.size(); i++){
        for(int j=0; j<HP[i].Hands.size(); j++){
            HP[i].Hands[j].Cards.clear();
            HP[i].Hands.clear();
            HP[i].Hands.push_back(AHand);
        }
        std::cout << HP[i].Name << ", you now have £" << HP[i].BankRoll << "." << std::endl;
    }//END OF CLEARING AND BANKROLLS OF HUMANS//
    
	
	//CLEAR AND GIVE BANKROLL OF COMPUTERS//
    for(int i=0; i<CP.size(); i++){
        for(int j=0; j<CP[i].Hands.size(); j++){
            CP[i].Hands[j].Cards.clear();
            CP[i].Hands.clear();
            CP[i].Hands.push_back(AHand);
        }
        std::cout << CP[i].Name << ", you now have £" << CP[i].BankRoll << "." << std::endl;
    }//END OF CLEARING AND BANKROLLS OF COMPUTERS//

    
	//CLEAR DEALER//
	Dealer.Hands[0].Cards.clear();

	//CLEAR, REFILL AND SHUFFLE DECK//
	Deck.Cards.clear();
    Deck.FillDeck();
    Deck.Shuffle();
    
    
    
    Pause(HP);
    
    
   
}
