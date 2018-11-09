//
//  card.cpp
//  go_fish
//
//  Created by Guy on 11/1/18.
//  Copyright © 2018 Guy Co. All rights reserved.
//


#include "card.h"

Card::Card(int rank, Suit s){
    
    myRank=rank;
    mySuit=s;
    
}

Card::Card(){
    
    myRank=1;
    mySuit=spades;
    
}

string Card::toString() const{
        
    return (rankString(myRank)+suitString(mySuit));
}

bool Card::sameSuitAs(const Card& c) const{
    if(mySuit==c.mySuit)
        return true;
    return false;
}

int  Card::getRank() const{
    return myRank;
}

string Card::suitString(Suit s) const{
    if(mySuit==hearts)
        return "h";
    else if(mySuit==diamonds)
        return "d";
    else if(mySuit==clubs)
        return "c";
    else
        return "s";
}

string Card::rankString(int r) const{
    if(r==11)
        return "J";
    else if(r==12)
        return "Q";
    else if(r==13)
        return "K";
    else if(r!=1){
        string out_string;
        stringstream ss;
        ss << r;
        out_string = ss.str();
        return out_string;
    }
    return "A";
}


bool Card::operator ==(Card const &rhs){
    if(myRank==rhs.myRank&&mySuit==rhs.mySuit)
        return true;
    return false;
}

bool Card::operator !=(Card const &rhs){
    if(myRank!=rhs.myRank&&mySuit!=rhs.mySuit)
        return true;
    return false;
}

ostream& operator << (ostream& out, const Card& c){
    out << c.toString();
    return out;
}
