//
//  go_fish.cpp
//  GoFish
//
//  Created by Guy on 11/1/18.
//  Copyright © 2018 Guy Co. All rights reserved.
//

#include <stdio.h>
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

void dealHand(Deck &d, Player &p, int numCards);

int main(int argc, const char * argv[]) {
    // insert code here...
    srand(time(NULL));
    
    cout << "So the game begins" << endl;
    //opens file
    ofstream out;
    out.open("gofish_results.txt");
    
    //players
    Player p1("Guy");
    Player p2("Roger");
    
    //creates and shuffles deck
    Deck d;  //create a deck of cards
    d.shuffle();
    
    //deals
    dealHand(d, p1, 7);
    dealHand(d, p2, 7);
    
    //temporary variables used as mailboxes essentially
    Card tempC1;
    Card tempC2;
    int tempInt;
    
    //loop terminators
    bool again=true;
    bool win=false;
    
    //winning player after game
    Player pWin;
    
    //initial game state
    out << "Initial " << endl;
    out << p1.getName() <<" hand has : " << p1.showHand() << endl;
    out << p2.getName() <<" hand has : " << p2.showHand() << endl;
    out << p1.getName() <<" book has : " << p1.showBooks() << endl;
    out << p2.getName() <<" book has : " << p2.showBooks() << endl << endl;
    
    //turn iterator
    int curTurn=1;
    

    while(!win){
        
        //bookLook
        while(p1.checkHandForBook(tempC1, tempC2))
            p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2));
            
        while(p2.checkHandForBook(tempC1, tempC2))
            p2.bookCards(p2.removeCardFromHand(tempC1),p2.removeCardFromHand(tempC2));
        
        
        //curTurn turn game state
        out << "Turn " << curTurn << endl;
        out << p1.getName() <<" hand has : " << p1.showHand() << endl;
        out << p2.getName() <<" hand has : " << p2.showHand() << endl;
        out << p1.getName() <<" book has : " << p1.showBooks() << endl;
        out << p2.getName() <<" book has : " << p2.showBooks() << endl << endl;
        
        //p1 turn
        while(again and p1.getHandSize()>0){
            tempC1=p1.chooseCardFromHand();
            if(tempC1.getRank()==0)
                break;
            out << p1.getName() <<" asks - do you have a  " << tempC1.rankString(tempC1.getRank()) << endl;
            tempInt=p2.rankInHand(tempC1);
            if(tempInt!=-1){
                out << p2.getName() <<" says - Yes. I have a  " << tempC1.rankString(tempC1.getRank()) << endl;
                out<< p1.getName() << " books " <<tempC1.toString() << " & " << p1.goFish(tempC1, p2.removeCardI(tempInt)) << endl;
            }
            else{
                out << p2.getName() <<" says - Go Fish! " << endl;
                again = false;
            }
        }
        if(p1.getHandSize()<=0 and d.size()<=0)
            pWin=p1;
        else if(p1.getHandSize()<=0)
            p1.addCard(d.dealCard());
        again = true;
        if(d.size()>=1)
            out << p1.getName() <<" draws " << p1.goFish(tempC1, d.dealCard()) << endl << endl;
        else
            out << "Deck empty" << endl << endl;
        
        //p1 lookBook
        if(p1.checkHandForBook(tempC1, tempC2))
            p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2));
        
        //p2 turn
        while(again and p2.getHandSize()>0){
            tempC2=p2.chooseCardFromHand();
            out << p2.getName() <<" asks - do you have a  " << tempC2.rankString(tempC2.getRank()) << endl;
            tempInt=p1.rankInHand(tempC2);
            if(tempInt!=-1){
                out << p1.getName() <<" says - Yes. I have a  " << tempC2.rankString(tempC2.getRank()) << endl;
                out<< p2.getName() << " books " <<tempC2.toString() << " & " << p2.goFish(tempC2, p1.removeCardI(tempInt)) << endl;
            }
            else{
                out << p1.getName() <<" says - Go Fish! " << endl;
                again = false;
            }
        }
        if(p2.getHandSize()<=0 and d.size()<=0)
            pWin=p2;
        else if(p2.getHandSize()<=0)
            p2.addCard(d.dealCard());
        again = true;
        if(d.size()>=1)
            out << p2.getName() <<" draws " << p2.goFish(tempC2, d.dealCard()) << endl << endl;
        else
            out << "Deck empty" << endl << endl;
        
        //ps lookBook
        if(p2.checkHandForBook(tempC1, tempC2))
            p2.bookCards(p2.removeCardFromHand(tempC1), p2.removeCardFromHand(tempC2));
        
        //check for win
        if(p1.getBookSize()>=14){
            win=true;
            pWin=p1;
        }
        else if(p2.getBookSize()>=14){
            win=true;
            pWin=p2;
        }
        else if(p1.getHandSize()<=0 and d.size()<=0)
            win=true;
        else if(p2.getHandSize()==0 and d.size()<=0)
            win=true;
        
        curTurn++;
    }
        
    
    //final game state
    out << "Final " << endl;
    out << p1.getName() <<" hand has : " << p1.showHand() << endl;
    out << p2.getName() <<" hand has : " << p2.showHand() << endl;
    out << p1.getName() <<" book has : " << p1.showBooks() << endl;
    out << p2.getName() <<" book has : " << p2.showBooks() << endl << endl;
    
    out << pWin.getName() << " wins!" << endl;
    
    cout << "And ends" << endl;
    
    return EXIT_SUCCESS;
}

void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}
