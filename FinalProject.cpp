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
#include <stdio.h>

using namespace std;


class Cards{
	protected:
		string suit; //what type should this begin
		string face;
		int value;
		
	public:
		int dealt;// acts as a flag 1: been dealt 0: has not been dealt
		Cards ();
		string getSuit();
		string getFace();
		int getValue();
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
			
			(this +i)->suit = "H";//♥"; heart \u26665
			(this +i)->face = faceVals[i];
			(this +i)->value = vals[i];
			(this + i)->dealt = 0;
	}
	for ( i = 13; i < 26; i++)
	{
			
			(this +i)->suit = "D";//"♦";diamond \u2666
			(this +i)->face = faceVals[i - 13];
			(this +i)->value = vals[i-13];
			(this + i)->dealt = 0;
	}
	for ( i = 26; i < 39; i++)
	{
			(this +i)->suit =  "C";//"♣";//clubs \u2663
			(this +i)->face = faceVals[i-26];
			(this +i)->value = vals[i-26];
			(this + i)->dealt = 0;
	}
	for ( i = 39; i < 52; i++)
		{
			(this +i)->suit = "S";//"♠";spade \u2660
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
//allows other classes to access the members
string Cards :: getSuit()
{
	return suit;
}

string Cards :: getFace()
{
	return face;
}

int Cards :: getValue()
{
	return value;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
class Hands : public Cards
{
	protected:
		vector <Cards> hand;
		int sum;
		
	public:
		Hands ();
		Hands(Cards *deck);
		vector <Cards> getHand();
		int getSum();
		void display ();
		void deal(Cards *deck);	
	
};
Hands :: Hands()//default contructor
{
	sum = 0;
}
Hands :: Hands(Cards *deck)
{
	sum = 0;
	srand (time(NULL));//makes everytime random
	for (int i= 0; i < 2; i++)//when constructed a hand should get two cards
	{
		
		int index = rand()%52;//picks a random card
		int count = 1;
		while (deck[index].dealt == 1)//checks to make sure it hasnt been dealt
		{
			index = rand()%52;//selects another random card
			count ++;
			if (count == 52)//checks to make sure there are still cards left in the deck
			{
				cout<<"Deck is out of cards"<< endl;
				return;
			}
		}
		deck[index].dealt = 1;//sets dealt to one in order to make sure it doesn't get dealt again
		hand.push_back(deck[index]);//adds on the card to the hand vector
		sum += deck[index].getValue();//adds together in order to get a sum
	}
	
	
}
void Hands :: deal (Cards *deck)
{
	
	srand (time(NULL));//ensures it is random every time
	int index = rand()%52;//picks a random card
	int count = 1;
	while (deck[index].dealt == 1)//checks to make sure the card hasnt been dealt
	//breaks out of the loop when it finds a card that hasnt been dealt
	{
		index = rand()%52;
		count ++;
		if (count == 52)
		{
			cout<<"Deck is out of cards"<< endl;
			return;
		}
	}
	
	deck[index].dealt = 1;//marks the chosen card as dealt
	
	hand.push_back(deck[index]);//adds the card to the hand
	sum += deck[index].getValue();//updates the value of the cards
	
	
	
	
	
}

void Hands :: display()
{
	for (int i = 0; i < hand.size(); i++)
	{
		hand[i].display();//calls the hand display function
		cout << " ";
		
	}
	cout << endl;
	cout << "the sum of the value of the cards is "<< sum << endl;
}
//allows other classes to access this information
vector <Cards> Hands :: getHand()
{
	return hand;
}

int Hands :: getSum()
{
	return sum;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
class Player{
	protected:
		double bank;
		Hands playHand;
		string name;
		
	public:
		//virtual void playGame ();
		Player();
		Player(Hands hand1, double num, string n);
		void displayPlayer();
		Hands getHand();
		void hit(Cards *deck);
		string getName ();
		double getBank();
			
};

Player :: Player ()
{
	bank = 0;
	cout<<" you did not mean to create this player"<< endl;
}
Player :: Player (Hands hand1, double num, string n)
{
	
	name = n;
	cout <<"player constructor"<< endl;
	playHand = hand1;
	bank = num;
	
}
void Player :: displayPlayer()//shows the player stats and their hand
{
	cout << name << " has $" << bank << " remaining in the bank" << endl
	<< name << "'s hand: " << endl;
	
	playHand.display();
}
Hands Player :: getHand()
{
	return playHand;
}
string Player :: getName()
{
	return name;
}
double Player :: getBank()
{
	return bank;
}

void Player :: hit(Cards *deck)
{

	playHand.deal(deck);
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
class Dealer : public Player//dealer is a player initialized with 0
{
	public:
		int playGame(Cards *deck);
		void displayDealer();
		Dealer(Hands hand1);
		Dealer ();
		
};
Dealer :: Dealer ()
{
	cout << "opps you messed up the dealer"<< endl;
}
Dealer::Dealer(Hands hand1) : Player(hand1, 0, "")//calls the player constructor to create the dealer as a player with no bank
{
	cout <<"dealer constructor"<< endl;
	
}
void Dealer :: displayDealer()
{
	vector <Cards> tempH = playHand.getHand();//displays the dealers hand- the first card is face down, the second is face up
	cout << "Dealers Hand" << endl;
	int i;
	cout << "[X X] ";
	for (i = 1; i < tempH.size(); i++)
	{
		tempH[i].display();//uses the cards display function
	}
	
	cout << endl;
}

int Dealer :: playGame (Cards *deck)
{

	if (playHand.getSum() < 17)//the dealer hits if the sum of cards are less than 17
	{
		playHand.deal(deck);
		return 0;//means the dealer is not done playing
	}
	return 1;//means the dealer is done playing
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//int main (void)
//{
	//Set up table
	//------------------------------------------------------------------------------------
	/*Cards deck[52];
	deck->initializeDeck ();
	
	Hands handD(deck);
	Dealer dealer(handD);
	srand(time(NULL));
	int num = rand()%4 +1;//ensures that the amount of mony that each player gets will be random
		
	Hands handE(deck);
	Player Eric(handE, num, "Eric");
	num = rand()%4 +1;//ensures that the amount of mony that each player gets will be random
	Hands handN(deck);
	Player Sammy(handN, num, "Sammy");
	//------------------------------------------------------------------------------------
	
	//Display hands
	//------------------------------------------------------------------------------------
	dealer.displayDealer();
	cout <<endl<< "----------ERIC----------" << endl;
	Eric.displayPlayer();
	cout << "HIT" <<endl;
	Eric.hit(deck);//deals the player another card
	Eric.displayPlayer();
	cout << endl;
	
	cout <<endl<< "----------SAMMY---------" << endl;
	Sammy.displayPlayer();
	cout << "HIT" << endl;
	Sammy.hit(deck);
	Sammy.displayPlayer();
	cout << endl;
	
	//------------------------------------------------------------------------------------
	int i = 0;
	while (i == 0)//the dealer keeps playing until the get to 17
	{
		i = dealer.playGame(deck);
		
	}
	cout << "Dealer after playing:" << endl;
	dealer.displayDealer();
	return 0;
}


This program can...
1) initialize the deck
2)initialize a hand for multiple players and the dealer
3)deals random cards to hands
4)display cards of the players and dealers
5)randomly assign players amount of money for them to bet during the bank
6)makes use of vectors and strings

Next steps...
1)add in a define operator
2)set up user input
3)add catch and throw error checking
4)ask and handle player bets
5)allow players to log in/ save game


*/

double findName (string username);
void printFile ();
void addName (Player player1);

double findName (string name)
{
	cout<< "in find Name"<< endl;
	char nameC[name.size()+1];//as 1 char space for null is also required
	strcpy(nameC, name.c_str());//copies the string and puts it in type char* 
	cout<< "past string conversion"<< endl;
	char* garbage;
	double bank = 0;
	int num;
	FILE* fp = fopen ("saveFile.txt", "r");
	fscanf(fp, "%f", num);
	
	cout<< "Opened file"<< endl;
	
	while (fscanf (fp, "%s %f", garbage, &bank) == 2)
	{
		cout<< "in while loop"<< endl;
		cout <<"hi" << endl;
		cout <<garbage << endl;
		if (strcmp (garbage, nameC) == 0)
		{
			cout << "in if "<< endl;
			fclose(fp);
			return bank;
		}		
		cout<< "after if " << endl;
	}
	cout << "Username not found." << endl;
	bank = -1;//IN FUTURE THROW AN ERROR HERE
	fclose(fp);
	return bank;
}

void printFile ()
{
	double tempN, tempB;
	int num;
	FILE* fp = fopen ("saveFile.txt", "r");
	fscanf(fp, "%f", num);
	cout << "Current Users:" << endl;
	while (fscanf(fp, "%s|f", &tempN, &tempB) == 2)
	{
		cout<< "Username:"<<tempN<<"  Bank: "<<tempB<< endl;
	}
	
}

void addName (Player player1)
{
	FILE* fp = fopen("saveFile.txt", "a" );
	string name = player1.getName();
	char nameC[name.size()+1];//as 1 char space for null is also required
	strcpy(nameC, name.c_str());//copies the string and puts it in type char*
	fprintf(fp, "%s|%.0f\n", nameC, player1.getBank());
	fclose (fp);
	
}

int main (void)
{
	FILE* fp;
	string username;

	int selection;
	int numPlayers;
	int fileStatus =1;
	double x;
	string userInfo = "-1";
	fp = fopen ("saveFile.txt", "r");
	
	cout<< fileStatus<< endl;
	fclose(fp);
	vector <Player> table;
	Cards deck[52];//set up the deck
	deck->initializeDeck ();
	
	if (fileStatus == 0)//no saved games
	{
		cout<< "Enter number of players: (Maximum:4, Minimum: 1)" << endl;
		cin>> numPlayers;
			while (numPlayers < 1 || numPlayers > 4)
			{
				cout<< "Invalid input.  Please enter either 1, 2, 3, or 4"<< endl;
				cin >> numPlayers;
				//need a way to error check if a non integer is entered how to make sure it the program doesn't blow up
			}
			
		for (int i = 0; i < numPlayers; i ++)
		{
			Hands tempHand (deck);
			cout <<"Enter username for player "<<i+1<<":";
			cin >>username;
			Player tempPlayer (tempHand,500, username);
			table.push_back(tempPlayer);
			addName(tempPlayer);
		}
		
	
		
		
			
	}
	else//there are saved users
	{
		
		cout<< "Enter number of players: (Maximum:4, Minimum: 1)" << endl;
		cin>> numPlayers;
				while (numPlayers < 1 || numPlayers > 4)
				{
					cout<< "Invalid input.  Please enter either 1, 2, 3, or 4"<< endl;
					cin >> numPlayers;
				}
	for (int i = 0; i < numPlayers; i++)
	{
		
		cout<< "1: Create New Player" << endl << "2: Load Saved Player"<< endl;
		cin >> selection;
		//catch throw error checking
		if (selection == 1)//same as above--creating a new player
		{
			
			
				Hands tempHand (deck);
				cout <<"Enter username for player "<<i+1<<":";
				cin >>username;
				Player tempPlayer (tempHand,500, username);
				table.push_back(tempPlayer);
				
			
		}
		else if (selection == 2)//they want to load a new player
		{
			while (selection == 2)
			{
				cout<< "1. Enter a username" << endl << "2. See directory of users" << endl<<"3. Create a new player" << endl;
				cin >> selection;
					while (selection < 1 || selection > 3)
					{
						cout<< "invalid input. Please try again.\n"<< "1. Enter a username" << endl << "2. See directory of users" << endl<<"3. Start new game" << endl;
						cin >> selection;
					}
					if (selection == 1)//entering a username to start the game from
					{
						
						cout << "Enter username for player" <<i+1<<":";
						cin >>username;
						cout<< "Entered username"<< endl;
						double tempBank = findName(username);
						cout << "made it back" << endl;
						while(tempBank == -1 )//this happens if the name was not found
						{
							int selection1;
							cout<< "1. Enter new username 2. See directory ";//give the user the option to see all usernames 
							cin >> selection1;
							if (selection == 1)
							{
								cout << "Enter username:";
								cin >> username;
								tempBank = findName(username);
							}
							else 
								printFile();							
						}
						Hands tempHand(deck);
						Player tempPlayer (tempHand,tempBank, username);
						table.push_back(tempPlayer);
						
					}
					else if (selection == 2)//want to see a list of the users that have saved games
					{
						printFile();
					}
					else if (selection == 3)//starting a brand new game--same as above
					{
						Hands tempHand (deck);
						cout <<"Enter username for player "<<i+1<<":";
						cin >>username;
						Player tempPlayer (tempHand,500, username);
						table.push_back(tempPlayer);
					}
				
			}	
		}
	}	
	}	

	
	
	
	return 0;
}


