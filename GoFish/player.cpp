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
            if(i!=j && myHand[i].getRank()==myHand[j].getRank()){
                c1=myHand[i];
                c2=myHand[j];
                return true;
            }
        }
    }
    return false;
}


int Player::rankInHand(Card c) const{
    
    for(int i=0;i<myHand.size();i++){
        if(myHand[i].getRank()==c.getRank())
           return i;
    }
    return 0;
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
            myHand.erase(myHand.begin()+i);
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
    if(myBook.size()>=2){
    for(int i=0;i<myBook.size()-1;i+=2)
        out.append(myBook[i].toString()+" "+myBook[i+1].toString()+"  ");
    }
    return out;
}

int Player::getHandSize() const{
    
    return (int) myHand.size();
}

int Player::getBookSize() const{
    
    return (int) myBook.size()/2;
}

string Player::goFish(Card a,Card c){
    
    addCard(c);
    addCard(removeCardFromHand(a));
    return c.toString();
}

Card Player::removeCardI(int i){
    Card r = myHand[i];
    this->removeCardFromHand(r);
    return r;
}

//bool Player::checkHandForPair(Card &c1, Card &c2){
//
//    return NULL;
//}


//bool Player::sameRankInHand(Card c) const{
//    
//    return NULL;
//}
