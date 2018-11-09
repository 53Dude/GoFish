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
    
    ofstream out;
    out.open("gofish_results.txt");
    
    Player p1("Guy");
    Player p2("Roger");
    
    Deck d;  //create a deck of cards
    d.shuffle();
    
    dealHand(d, p1, 7);
    dealHand(d, p2, 7);
    
    Card tempC1;
    Card tempC2;
    int tempInt;
    bool again=true;
    bool win=false;
    Player pWin;
    
    cout << "Initial " << endl;
    cout << p1.getName() <<" hand has : " << p1.showHand() << endl;
    cout << p2.getName() <<" hand has : " << p2.showHand() << endl;
    cout << p1.getName() <<" book has : " << p1.showBooks() << endl;
    cout << p2.getName() <<" book has : " << p2.showBooks() << endl << endl;
    
    while(!win){
        int curTurn=1;
        while(p1.checkHandForBook(tempC1, tempC2))
            p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2));
            
        while(p2.checkHandForBook(tempC1, tempC2))
            p2.bookCards(p2.removeCardFromHand(tempC1),p2.removeCardFromHand(tempC2));
        
        
        cout << "Turn " << curTurn << endl;
        cout << p1.getName() <<" hand has : " << p1.showHand() << endl;
        cout << p2.getName() <<" hand has : " << p2.showHand() << endl;
        cout << p1.getName() <<" book has : " << p1.showBooks() << endl;
        cout << p2.getName() <<" book has : " << p2.showBooks() << endl << endl;
        
        while(again){
            tempC1=p1.chooseCardFromHand();
            cout << p1.getName() <<" asks - do you have a  " << tempC1.rankString(tempC1.getRank()) << endl;
            tempInt=p2.rankInHand(tempC1);
            if(p2.rankInHand(tempC1)!=0){
                cout << p2.getName() <<" says - Yes. I have a  " << tempC1.rankString(tempC1.getRank()) << endl;
                cout<< p1.getName() << " books " <<tempC1.toString() << " & " << p1.goFish(tempC1, p2.removeCardI(tempInt)) << endl;
            }
            else{
                cout << p2.getName() <<" says - Go Fish! " << endl;
                again = false;
            }
        }
        again = true;
        cout << p1.getName() <<" draws " << p1.goFish(tempC1, d.dealCard()) << endl << endl;
        
        if(p1.checkHandForBook(tempC1, tempC2))
            p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2));
        
        
        while(again){
            tempC2=p2.chooseCardFromHand();
            cout << p2.getName() <<" asks - do you have a  " << tempC2.rankString(tempC2.getRank()) << endl;
            tempInt=p1.rankInHand(tempC2);
            if(p1.rankInHand(tempC2)!=0){
                cout << p1.getName() <<" says - Yes. I have a  " << tempC2.rankString(tempC2.getRank()) << endl;
                cout<< p2.getName() << " books " <<tempC2.toString() << " & " << p2.goFish(tempC2, p1.removeCardI(tempInt)) << endl;
            }
            else{
                cout << p1.getName() <<" says - Go Fish! " << endl;
                again = false;
            }
        }
        again = true;
        cout << p2.getName() <<" draws " << p2.goFish(tempC2, d.dealCard()) << endl << endl;
        
        if(p2.checkHandForBook(tempC1, tempC2))
            p2.bookCards(p2.removeCardFromHand(tempC1), p2.removeCardFromHand(tempC2));
        
        if(p1.getBookSize()>=14){
            win=true;
            pWin=p1;
        }
        else if(p2.getBookSize()>=14){
            win=true;
            pWin=p2;
        }
        else if(p1.getHandSize()==0){
            win=true;
            pWin=p1;
        }
        else if(p2.getHandSize()==0){
            win=true;
            pWin=p2;
        }
        
        curTurn++;
    }
    
    cout << "Final " << endl;
    cout << p1.getName() <<" hand has : " << p1.showHand() << endl;
    cout << p2.getName() <<" hand has : " << p2.showHand() << endl;
    cout << p1.getName() <<" book has : " << p1.showBooks() << endl;
    cout << p2.getName() <<" book has : " << p2.showBooks() << endl << endl;
    
    cout << pWin.getName() << " wins!" << endl;
    
    return EXIT_SUCCESS;
}

void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}
