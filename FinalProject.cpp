//============================================================================
// Name        : lab7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>


using namespace std;


class Cards{
	public:
		string suit; //what type should this begin
		string face;
		int value;
		int dealt;// acts as a flag 1: been dealt 0: has not been dealt
	
		Cards ();
		void initializeDeck();
		virtual void display ();
		
};
Cards :: Cards ()
{
	suit = "default";
	face = "default";
	value = 0;
	dealt = 0;
}

void Cards::initializeDeck()//intializes all 52 cards
{
	int i;
	string faceVals [13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	int vals[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};//intially give ace 11 and we will handle it later
	for ( i = 0; i < 13; i++)
	{
			
			(this +i)->suit = "H";
			(this +i)->face = faceVals[i];
			(this +i)->value = vals[i];
			(this + i)->dealt = 0;
	}
	for ( i = 13; i < 26; i++)
	{
			
			(this +i)->suit = "D";
			(this +i)->face = faceVals[i - 13];
			(this +i)->value = vals[i-13];
			(this + i)->dealt = 0;
	}
	for ( i = 26; i < 39; i++)
	{
			(this +i)->suit = "C";//clubs
			(this +i)->face = faceVals[i-26];
			(this +i)->value = vals[i-26];
			(this + i)->dealt = 0;
	}
	for ( i = 39; i < 52; i++)
		{
			(this +i)->suit = "S";
			(this +i)->face = faceVals[i-39];
			(this +i)->value = vals[i-39];
			(this + i)->dealt = 0;
		}
	
	
}

void Cards:: display ()
{
		//cout << "___" << endl;
		cout << "[" << face << " " ;
		cout << suit << "]" ;
}


class Hands : public Cards
{
	public:
		vector <Cards> hand;
		int sum;
		
	public:
		Hands ();
		Hands(Cards *deck);
		void display ();
		void deal(Cards *deck);	
	
};
Hands :: Hands()
{
	sum = 0;
}
Hands :: Hands(Cards *deck)
{
	
	srand (time(NULL));
	for (int i= 0; i < 2; i++)
	{
		
		int index = rand()%52;
		int count = 1;
		while (deck[index].dealt == 1)
		{
			index = rand()%52;
			count ++;
			if (count == 52)
			{
				cout<<"Deck is out of cards"<< endl;
				return;
			}
		}
		deck[index].dealt = 1;
		hand.push_back(deck[index]);
		sum += deck[index].value;
	}
	
}
void Hands :: deal (Cards *deck)
{
	srand (time(NULL));
	int index = rand()%52;
	int count = 1;
	while (deck[index].dealt == 1)
	{
		index = rand()%52;
		count ++;
		if (count == 52)
		{
			cout<<"Deck is out of cards"<< endl;
			return;
		}
	}
	
	deck[index].dealt = 1;
	
	hand.push_back(deck[index]);
	sum += deck[index].value;

}

void Hands :: display()
{
	for (int i = 0; i < hand.size(); i++)
	{
		hand[i].display();
		cout << " ";
		
	}
	
	cout << endl;
}


class Player{
	protected:
		double bank;
		Hands playHand;
		
	public:
		//virtual void playGame ();
		Player();
		Player(Hands hand1, int num);
			
};
Player :: Player ()
{
	bank = 0;
	cout<<" you did not mean to create this player"<< endl;
}
Player :: Player (Hands hand1, int num)
{
		cout <<"player constructor"<< endl;
	playHand = hand1;
	if (num == 0)
	{
		bank = 0;
		
	}
	else if(num == 1)
	{
		bank = 10000;	
	}
	else if (num == 2)
		bank = 1000;
	else 
		bank = 250;
	
}
class Dealer : public Player
{
	public:
		void playGame(Cards *deck);
		void display();
		Dealer(Hands hand1);
		Dealer ();
		
};
Dealer :: Dealer ()
{
	cout << "opps you messed up the dealer"<< endl;
}
Dealer::Dealer(Hands hand1) : Player(hand1, 0)
{
	cout <<"dealer constructor"<< endl;
	
}
void Dealer :: display ()
{
	int i;
	cout << "[X X]";
	for (i = 1; i < playHand.hand.size(); i++)
	{
		playHand.hand[i].display();
	}
	
	cout << endl;
}

void Dealer :: playGame (Cards *deck)
{
	if (playHand.sum < 17)
	{
		playHand.deal(deck);
	}
	display();

}


int main (void)
{
	
	Cards deck[52];
	deck->initializeDeck ();
	Hands hand1 (deck);
	hand1.deal(deck);
	deck[17].display();
	hand1.display();
	Player (hand1, 1);
	Hands hand2 (deck);
	Dealer dealer(hand2);
	dealer.display ();
	dealer.playGame (deck);
	

	
	return 0;
}
