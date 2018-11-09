//
//  player.cpp
//  go_fish
//
//  Created by Guy on 11/1/18.
//  Copyright © 2018 Guy Co. All rights reserved.
//

#include "player.h"

Player::Player(){
    myName="";
}

void Player::addCard(Card c){
    
    myHand.push_back(c);
}

void Player::bookCards(Card c1, Card c2){
    
    myBook.push_back(c1);
    myBook.push_back(c2);
}


bool Player::checkHandForBook(Card &c1, Card &c2){
    for(int i=0;i<myHand.size();i++){
        for(int j=0;j<myHand.size();j++){
            if(myHand[i].getRank()==myHand[j].getRank()){
                c1=myHand[i];
                c2=myHand[j];
                return true;
            }
        }
    }
    return false;
}


bool Player::rankInHand(Card c) const{
    
    for(int i=0;i<myHand.size();i++){
        if(myHand[i].getRank()==c.getRank())
           return true;
    }
    return false;
}


Card Player::chooseCardFromHand() const{
    
    return myHand[0];
}


bool Player::cardInHand(Card c) const{

    for(int i=0;i<myHand.size();i++){
        if(myHand[i].getRank()==c.getRank()&&myHand[i].sameSuitAs(c))
            return true;
    }
    return false;
}


Card Player::removeCardFromHand(Card c){
    
    for(int i=0;i<myHand.size();i++){
        if(myHand[i].getRank()==c.getRank()&&myHand[i].sameSuitAs(c)){
            myHand.erase(myHand.begin()+(i-1));
            return c;
        }
    }
    return c;
}

string Player::showHand() const{
    
    string out="";
    for(int i=0;i<myHand.size();i++)
        out.append(myHand[i].toString()+" ");
    return out;
}

string Player::showBooks() const{
    
    string out="";
    for(int i=0;i<myHand.size()-1;i+=2)
        out.append(myHand[i].toString()+" "+myHand[i+1].toString()+"  ");
    return out;
}

int Player::getHandSize() const{
    
    return (int) myHand.size();
}

int Player::getBookSize() const{
    
    return (int) myBook.size();
}


//bool Player::checkHandForPair(Card &c1, Card &c2){
//
//    return NULL;
//}


//bool Player::sameRankInHand(Card c) const{
//    
//    return NULL;
//}
