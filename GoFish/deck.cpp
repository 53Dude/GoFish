//
//  deck.cpp
//  go_fish
//
//  Created by Guy on 11/1/18.
//  Copyright © 2018 Guy Co. All rights reserved.
//

#include "deck.h"

//Card::Suit suitItr[] = {Card::spades,Card::hearts,Card::diamonds,Card::clubs};

Deck::Deck(){
    for(int i=0;i<13;i++){
        myCards[i]=Card(i+1,Card::spades);
    }
    for(int i=13;i<26;i++){
        myCards[i]=Card(i-12,Card::hearts);
    }
    for(int i=26;i<39;i++){
        myCards[i]=Card(i-25,Card::diamonds);
    }
    for(int i=39;i<52;i++){
        myCards[i]=Card(i-38,Card::clubs);
    }
    myIndex=0;
}

void Deck::shuffle(){
    
    if(myIndex==52)
        return;
    
    vector<Card> working;
    Card tempCard;
    
    for(int i=0;i<size();i++)
        working.push_back(myCards[i]);
    
    if(working.size()==1)
        return;
    
    //flips list a random amount of times, moving elements depending on random value
    int temp=rand()%9;
    for(int i=0;i<working.size()*temp;i++){
        
        int iOne=rand()%working.size();
        int iTwo=rand()%working.size();
        while(iOne!=iTwo){
            iOne=rand()%working.size();
            iTwo=rand()%working.size();
        }
        
        tempCard=working[0];
        working[0]=working[iOne];
        working[iOne]=tempCard;
        
        tempCard=working[iOne];
        working[iOne]=working[iTwo];
        working[iTwo]=tempCard;
    }
    
    for(int i=0;i<size();i++)
        myCards[i]=working[i];
    
}

Card Deck::dealCard(){
    if(myIndex==52)
        return Card(0,Card::spades);
    myIndex++;
    return myCards[myIndex-1];
}

int  Deck::size() const{
    
    return 52-myIndex;
}
