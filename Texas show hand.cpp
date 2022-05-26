#include <string.h>
#include <iostream>

using namespace std ;

enum Suit{ SPADES = 832, HEARTS = 574, DIAMONDS = 456, CLUBS = 192 };
enum Face{ ACE = 3947, DEUCE = 4537, THREE = 6696, FOUR = 7729, FIVE = 8374, SIX = 9295, SEVEN = 11491, EIGHT = 13638, NINE = 14454, TEN = 15332, JACK = 18987, QUEEN = 20215, KING = 213643};

struct Card{
	Suit suit ;
	Face face ;
};

typedef Card Hand[5] ;

void Play(Hand hand1, Hand hand2) ;

bool Input(Hand hand) ;

bool BiggerThan(Card card1, Card card2) ;

void FindLargest(Hand hand, Card & largest) ;

bool IsStraight(Hand hand, Card & largest) ;

bool IsFlush(Hand hand, Card & largest) ;

bool IsStraightFlush(Hand hand, Card & largest) ;

bool IsFourOfAKind(Hand hand, Card & largest) ;

bool HasThreeOfAKind(Hand hand, Card & largest) ;

bool HasOnePair(Hand hand, bool excludeACard, Card excludedCard, Card & largest) ;

bool IsTwoPairs(Hand hand, Card & largest1, Card & largest2) ;

bool IsFullHouse(Hand hand, Card & largest) ;

void PrintCard(int type1, Card compare1, Card compare2, int type2, Card compare3, Card compare4) ;

void Whattype(int type1, char ch1[20], int type2, char ch2[20]) ;

void WhatCard(Card card, char ch2[20]) ;

void Play(Hand hand1, Hand hand2) ;

bool BiggerThan(Card card1, Card card2) {
	if (card1.face == card2.face) {
		if (card1.suit > card2.suit)
		  return true ;
		else
		  return false ;
	}
	else if (card1.face == ACE)
	  return true ;
	else if (card2.face == ACE)
	  return false ;
	else if (card1.face > card2.face)
	  return true ;
	else
	  return false ;
}

bool InputHand(Hand hand) {
	int i = 0 ;
	char ch[3] = {'\0'} ;
	char num[3] = {'\0'} ;
	cin >> ch ;
	while (strcmp(ch,"-1") != 0 && i < 5) {
		if (strcmp(ch,"S") == 0)
		  hand[i].suit = SPADES ;
		else if (strcmp(ch,"H") == 0)
		  hand[i].suit = HEARTS ;
		else if (strcmp(ch, "D") == 0)
		  hand[i].suit = DIAMONDS ;
		else if (strcmp(ch,"C") == 0)
		  hand[i].suit = CLUBS ;
		else
		  return false ;
		  
		cin >> num ;
		if (strcmp(num,"A") == 0)
		  hand[i].face = ACE ;
		else if (strcmp(num, "2") == 0)
		  hand[i].face = DEUCE ;
		else if (strcmp(num, "3") == 0)
		  hand[i].face = THREE ;
		else if (strcmp(num, "4") == 0)
		  hand[i].face = FOUR ;
		else if (strcmp(num, "5") == 0)
		  hand[i].face = FIVE ;
		else if (strcmp(num,"6") == 0)
		  hand[i].face = SIX ;
		else if (strcmp(num, "7") == 0)
		  hand[i].face = SEVEN ;
		else if (strcmp(num,"8") == 0)
		  hand[i].face = EIGHT ;
		else if (strcmp(num,"9") == 0)
		  hand[i].face = NINE ;
		else if (strcmp(num,"10") == 0)
		  hand[i].face =TEN ;
		else if (strcmp(num, "J") == 0)
		  hand[i].face= JACK ;
		else if (strcmp(num,"Q") == 0)
		  hand[i].face= QUEEN ;
		else if (strcmp(num, "K") == 0)
		  hand[i].face = KING ;
		else 
		  return false ;
		i++ ;
		cin >> ch ;
		if (i == 5 && strcmp(ch,"-1") != 0)
		  return false ;
	}
	if (i == 5)
	  return true ;
	else 
	  return false ;
}

void FindLargest(Hand hand, Card & largest) {
	int i, k;
	Card temp ;
	for (i = 0 ; i < 4 ; i++) {
		for(k=i+1 ; k < 5 ; k++) {
			if (BiggerThan(hand[k],hand[i])) {
				temp.face = hand[i].face ;
				hand[i].face = hand[k].face ;
				hand[k].face = temp.face ;
				temp.suit = hand[i].suit ;
				hand[i].suit = hand[k].suit ;
				hand[k].suit = temp.suit ;			
				}
		}
	}
	
	bool check = true ;
	for ( i = 0 ; i < 5 ; i++) {
		if (hand[0].face != ACE)
		  check = false ;
		if (hand[1].face != FIVE)
		  check = false ;
		if (hand[2].face != FOUR)
		  check = false ;
		if (hand[3].face != THREE)
		  check = false ;
		if (hand[4].face != DEUCE)
		  check = false ;
		  
	}
	
	if (check) {
		largest.face = hand[1].face ;
		largest.suit = hand[1].suit ;
	}
	else {
		largest.face=  hand[0].face ;
		largest.suit = hand[0].suit ;
	}
}

bool IsStraight(Hand hand, Card & largest) {
	int list[20], i ;
	bool check = false ;
	list[0] = ACE + DEUCE + THREE + FOUR + FIVE ;
	list[1] = DEUCE + THREE + FOUR + FIVE + SIX ;
	list[2] = THREE + FOUR + FIVE + SIX + SEVEN ;
	list[3] = FOUR + FIVE + SIX + SEVEN + EIGHT ;
	list[4] = FIVE + SIX + SEVEN + EIGHT + NINE ;
	list[5] = SIX + SEVEN + EIGHT + NINE + TEN ;
	list[6] = SEVEN + EIGHT + NINE + TEN + JACK ;
	list[7] = EIGHT + NINE + TEN + JACK + QUEEN ;
	list[8] = NINE + TEN  + JACK + QUEEN + KING ;
	list[9] = TEN + JACK + QUEEN + KING + ACE ;
	int total = hand[0].face + hand[1].face + hand[2].face + hand[3].face + hand[4].face ;
	for ( i = 0 ; i < 10 ; i++) {
		if (total = list[i])
		  check = true ;
	}
	
	FindLargest(hand, largest) ;
	return check ;
}

bool IsFlush(Hand hand, Card & largest) {
	int i, k ;
	int check2 = 0 ;
	bool check = true ;
	for ( i = 0 ; i < 4 ; i++) {
		if (hand[i].suit != hand[i+1].suit) {
			check = false ;
		}
	}
	
	if (check) {
		FindLargest(hand, largest) ;
	}
}
bool IsStraightFlush(Hand hand, Card & largest) {
	Card temp ;
	bool check = false ;
	if (IsFlush(hand, temp)) {
		if (IsStraight(hand, temp)) {
			check = true ;
			FindLargest(hand, largest) ;
		}
	}
}

bool IsFourOfAKind(Hand hand, Card & largest) {
	Card temp ;
	for (int i = 0 ; i < 4 ; i++) {
		for(int k=i+1 ; k < 5 ; k++) {
			if (BiggerThan(hand[k],hand[i])) {
				temp.face = hand[i].face ;
				hand[i].face = hand[k].face ;
				hand[k].face = temp.face ;
				temp.suit = hand[i].suit ;
				hand[i].suit = hand[k].suit ;
				hand[k].suit = temp.suit ;			
			}
		}
	}
	int equal = 1 ;
	bool check = false ;
	temp.face = hand[0].face ;
	temp.suit = hand[0].suit ;
	if (hand[0].face != hand[1].face) {
		temp.face = hand[1].face ;
		temp.suit = hand[1].suit ;
	}
	
	for (int i = 0 ; i < 5 ; i++ ) {
		if (temp.face == hand[i].face)
		  equal++ ;
	}
	
	if (equal == 4) {
		check = true ;
		largest.face = temp.face ;
		largest.suit = temp.suit ;
	}
	return check ;
}

bool HasThreeOfAKind(Hand hand, Card & largest) {
	Card temp ;
	bool check = false ;
	if (!IsFourOfAKind(hand, temp)) {
		for (int i = 0 ; i < 4 ; i++) {
			for(int k=i+1 ; k < 5 ; k++) {
				if (BiggerThan(hand[k],hand[i])) {
					temp.face = hand[i].face ;
					hand[i].face = hand[k].face ;
					hand[k].face = temp.face ;
					temp.suit = hand[i].suit ;
					hand[i].suit = hand[k].suit ;
					hand[k].suit = temp.suit ;			
				}
			}
		}
		int equal = 0 ;
		temp.face = hand[0].face ;
		temp.suit = hand[0].suit ;
		if (hand[0].face != hand[1].face) {
			if (hand[1].face != hand[2].face) {
				temp.face = hand[2].face ;
				temp.suit = hand[2].suit ;
			}
			else if (hand[1].face == hand[2].face) {
				temp.face = hand[1].face ;
				temp.suit = hand[1].suit ;
			}
		}
	
		for (int i = 0 ; i < 5 ; i++ ) {
			if (temp.face == hand[i].face)
		  		equal++ ;
		}
	
		if (equal == 3) {
			check = true ;
			largest.face = temp.face ;
			largest.suit = temp.suit ;
		}
	}
	return check ;
}

bool HasOnePair(Hand hand, bool excludeACard, Card excludedCard, Card & largest) {
	bool check = false ;
	bool bRun = true ;
	int a = 0 ;
	Card temp ;
	if (!HasThreeOfAKind(hand, temp)) {
		for (int i = 0 ; i < 4 ; i++) {
			for(int k=i+1 ; k < 5 ; k++) {
				if (BiggerThan(hand[k],hand[i])) {
					temp.face = hand[i].face ;
					hand[i].face = hand[k].face ;
					hand[k].face = temp.face ;
					temp.suit = hand[i].suit ;
					hand[i].suit = hand[k].suit ;
					hand[k].suit = temp.suit ;			
				}
			}
		}
	
		if (hand[0].face != hand[1].face)
		  a = 1 ;
		int equal = 0 ;
		if (excludeACard == false) {
			temp.face = hand[0].face ;
			temp.suit = hand[0].suit ;
			if (hand[0].face != hand[1].face) {
				temp.face = hand[1].face ;
				temp.suit = hand[1].suit ;
			}
			
			for (int i = 0 ; i < 5 ; i++) {
				if (temp.face == hand[i].face)
				  equal++ ;
			}
			
			if (equal == 2) {
				check = true ;
				largest.face = temp.face ;
				largest.suit = temp.suit ;
				
			}
		}
		
		else if (excludeACard == true) {
			while (bRun) {
				if (hand[a].face != excludedCard.face) {
					temp.face = hand[a].face ;
					temp.suit = hand[a].suit ;
					bRun = false ;
				}
				else 
				  a++ ;
			}
			
			if (temp.face != hand[a+1].face) {
				temp.face = hand[a+1].face ;
				temp.suit = hand[a+1].suit ;
			}
			
			for (int i = 0 ; i < 5 ; i++) {
				if (temp.face == hand[i].face)
				  equal++ ;
			}
			
			if (equal == 2) {
				check = true ;
				largest.face = temp.face ;
				largest.suit = temp.suit ;
			}
		}
	}
	return check ;
}

bool IsTwoPairs(Hand hand, Card & largest1, Card & largest2) {
	bool check = false ;
	Card temp ;
	if (HasOnePair(hand,false,temp,temp)) {
		largest1.face = temp.face ;
		largest1.suit = temp.suit ;
		if (HasOnePair(hand, true, temp, largest2))
		  check = true ;
	}
	return check ;
}

bool IsFullHouse (Hand hand, Card & largest) {
	bool check = false ;
	Card temp ;
	for (int i = 0 ; i < 4 ; i++) {
		for(int k=i+1 ; k < 5 ; k++) {
			if (BiggerThan(hand[k],hand[i])) {
				temp.face = hand[i].face ;
				hand[i].face = hand[k].face ;
				hand[k].face = temp.face ;
				temp.suit = hand[i].suit ;
				hand[i].suit = hand[k].suit ;
				hand[k].suit = temp.suit ;			
			}
		}
	}
	
	if (hand[1].face == hand[2].face) {
		if (hand[1].face == hand[0].face && hand[3].face == hand[4].face) {
			check = true ;
			largest.face = hand[0].face ;
			largest.suit = hand[0].suit ;
		}
	}
	else if (hand[1].face != hand[2].face) {
		if (hand[0].face == hand[1].face && hand[2].face == hand[3].face && hand[3].face == hand[4].face) {
			check = true ;
			largest.face = hand[2].face ;
			largest.suit = hand[2].suit ;
		}
	}
	return check ;
}

void PrintCard(int type1, Card compare1, Card compare2, int type2, Card compare3, Card compare4) {
	char ch1[20] ;
	char ch2[20] ;
	char ch3[50], ch4[50] ;
	char ch5[50], ch6[50] ;
	Whattype(type1, ch1, type2, ch2) ;
	WhatCard(compare1, ch3) ;
	WhatCard(compare2, ch4) ;
	WhatCard(compare3, ch5) ;
	WhatCard(compare4, ch6) ;
	if (type1 == 3) {
		strcat(ch3," and ") ;
		strcat(ch3, ch4) ;
	}
	
	if (type2 == 3) {
		strcat(ch5, " and ") ;
		strcat(ch5,ch6) ;
	}
	
	if (type1 > type2)
	  cout << ch1 << " (" << ch3 << ')' << " wins over " << ch2 << " (" << ch5 << ")." ;
	else if (type1 < type2) 
	  cout << ch1 << " (" << ch3 << ')' << " loses to " << ch2 << " (" << ch5 << ")." ;	
	else if (type1 == type2) {
		if (type1 == 3) {
			if (compare1.face > compare3.face)
			  cout << ch1 << " (" << ch3 << ')' << " wins over " << ch2 << " (" << ch5 << ")." ;
			else if (compare1.face < compare4.face)
			  cout << ch1 << " (" << ch3 << ')' << " loses to " << ch2 << " (" << ch5 << ")." ;
			else {
				if (compare2.face > compare4.face)
				  cout << ch1 << " (" << ch3 << ')' << " wins over " << ch2 << " (" << ch5 << ")." ;
				else if (compare2.face < compare4.face)
				  cout << ch1 << " (" << ch3 << ')' << " loses to " << ch2 << " (" << ch5 << ")." ;
				else if (compare2.face == compare4.face) {
					if (compare1.suit > compare3.suit)
					  cout << ch1 << " (" << ch3 << ')' << " wins over " << ch2 << " (" << ch5 << ")." ;
					else if (compare1.suit < compare3.suit)
					  cout << ch1 << " (" << ch3 << ')' << " loses to " << ch2 << " (" << ch5 << ")." ;
				}
			}  
		}
		
		else {
			if (BiggerThan(compare1,compare3))
			  cout << ch1 << " (" << ch3 << ')' << " wins over " << ch2 << " (" << ch5 << ")." ;
			else if (!BiggerThan(compare1,compare3))
			  cout << ch1 << " (" << ch3 << ')' << " loses to " << ch2 << " (" << ch5 << ")." ;
		}
	}	
}

void Whattype(int type1, char ch1[20], int type2, char ch2[20]) {
	if (type1 == 9) 
	  strcpy(ch1, "Straight flush") ;
	if (type1 == 8)
	  strcpy(ch1, "Four of a kind") ;
	if (type1 == 7)
	  strcpy(ch1, "Full house") ;
	if (type1 == 6)
	  strcpy(ch1, "Flush") ;
	if (type1 == 5)
	  strcpy(ch1, "Straight") ;
	if (type1 == 4)
	  strcpy(ch1, "Three of a kind") ;
	if (type1 == 3)
	  strcpy(ch1, "Two pairs") ;
	if (type1 == 2)
	  strcpy(ch1, "One pair") ;
	if (type1 == 1)
	  strcpy(ch1, "Zilch") ;
	if (type2 == 9) 
	  strcpy(ch1, "straight flush") ;
	if (type2 == 8)
	  strcpy(ch1, "four of a kind") ;
	if (type2 == 7)
	  strcpy(ch1, "full house") ;
	if (type2 == 6)
	  strcpy(ch1, "flush") ;
	if (type2 == 5)
	  strcpy(ch1, "straight") ;
	if (type2 == 4)
	  strcpy(ch1, "three of a kind") ;
	if (type2 == 3)
	  strcpy(ch1, "two pairs") ;
	if (type2 == 2)
	  strcpy(ch1, "one pair") ;
	if (type2 == 1)
	  strcpy(ch1, "zilch") ;
}

void WhatCard(Card card, char ch2[50]) {
	char ch1[50] ;
	if (card.suit == SPADES)
	  strcpy(ch1,"Spades") ;
	else if (card.suit == HEARTS)
	  strcpy(ch1, "Hearts") ;
	else if (card.suit == DIAMONDS)
	  strcpy(ch1, "Diamonds") ;
	else if (card.suit == CLUBS) 
	  strcpy(ch1, "Clubs") ;
	if (card.face == ACE)
	  strcpy(ch2, "Ace") ;
	else if (card.face == DEUCE)
	  strcpy(ch2, "Deuce") ;
	else if (card.face == THREE)
	  strcpy(ch2, "Three") ;
	else if (card.face == FOUR)
	  strcpy(ch2, "Four") ;
	else if (card.face == FIVE)
	  strcpy(ch2, "Five") ;
	else if (card.face == SIX)
	  strcpy(ch2, "Six") ;
	else if (card.face == SEVEN)
	  strcpy(ch2, "Seven") ;
	else if (card.face == EIGHT)
	  strcpy(ch2, "Eight") ;
	else if (card.face == NINE)
	  strcpy(ch2, "Nine") ;
	else if (card.face == TEN)
	  strcpy(ch2, "Ten") ;
	else if (card.face == JACK)
	  strcpy(ch2, "Jack") ;
	else if(card.face == QUEEN)
	  strcpy(ch2, "Queen") ;
	else if (card.face == KING)
	  strcpy(ch2, "King") ;
	
	strcat(ch2, " of ") ;
	strcat(ch2, ch1) ;
}

void Play(Hand hand1, Hand hand2) {
	Card compare1, compare2 ;
	Card compare3, compare4 ;
	int type1, type2 ;
	if (IsStraightFlush(hand1, compare1))
	  type1 = 9 ;
	else if (IsFourOfAKind(hand1,compare1))
	  type1 = 8 ;
	else if (IsFullHouse(hand1, compare1))
	  type1 = 7 ;
	else if (IsFlush(hand1, compare1))
	  type1 = 6 ;
	else if (IsStraight(hand1, compare1))
	  type1 = 5 ;
	else if (HasThreeOfAKind(hand1, compare1))
	  type1 = 4 ;
	else if (IsTwoPairs(hand1, compare1, compare2))
	  type1 = 3 ;
	else if (HasOnePair(hand1, false , compare1, compare1))
	  type1 = 2 ;
	else {
		type1 = 1 ; 
		FindLargest(hand1, compare1) ;
	}
	
	if (IsStraightFlush(hand2, compare3))
	  type2 = 9 ;
	else if (IsFourOfAKind(hand2,compare3))
	  type2 = 8 ;
	else if (IsFullHouse(hand2, compare3))
	  type2 = 7 ;
	else if (IsFlush(hand2, compare3))
	  type2 = 6 ;
	else if (IsStraight(hand2, compare3))
	  type2 = 5 ;
	else if (HasThreeOfAKind(hand2, compare3))
	  type2 = 4 ;
	else if (IsTwoPairs(hand2, compare3, compare4))
	  type2 = 3 ;
	else if (HasOnePair(hand2, false , compare3, compare3))
	  type2 = 2 ;
	else {
		type2 = 1 ; 
		FindLargest(hand2, compare3) ;
	}
	
	PrintCard(type1, compare1, compare2, type2, compare3, compare4) ;
	
}

int main() {
	Hand firstHand, secondHand ;
	if (InputHand(firstHand))
	  if (InputHand(secondHand))
	    Play(firstHand, secondHand) ;
	  else
	    cout << "Input Error in second hand of cards!\n" ;
	else 
	  cout << "Input Error in first hand of cards!\n" ;	
}
