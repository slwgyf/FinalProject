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
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <stdio.h>
#include <fstream>
//#include <malloc.h>
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
		void setValue(int num);
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
void Cards :: setValue(int num)
{
	value = num;
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
		void setSum(int num);
		void display ();
		void deal(Cards *deck);	
		int handleAce();
	
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
	//cout << "\tthe sum of the value of the cards is "<< sum << endl;
}
int Hands :: handleAce()
{
	for(int i = 0; i < hand.size(); i++)
	{
		if(hand[i].getValue() == 11)
		{
			setSum(sum - 10);
			hand[i].setValue(1);
			return sum;
		}
	}
	return sum;
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

void Hands :: setSum(int num)
{
	sum = num;
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
		Hands* gethand();
		void hit(Cards *deck);
		string getName();
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
	//cout <<"player constructor"<< endl;
	playHand = hand1;
	bank = num;
	
}
void Player :: displayPlayer()//shows the player stats and their hand
{
	cout <<"\t" <<name << " has $" << bank << " remaining in the bank" << endl
	<<"\t"<< name << "'s hand: " << endl<<"\t";
	
	playHand.display();
}
Hands* Player :: gethand()
{
	return &playHand;
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
	//cout <<"dealer constructor"<< endl;
	
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
	if(playHand.getSum() == 21 && playHand.getHand().size() == 2)
	{
		playHand.setSum(-1);
		return 1;
	}
	if(playHand.getSum() > 21)
	{
		playHand.handleAce();
	}
	if(playHand.getSum() < 17)//the dealer hits if the sum of cards are less than 17
	{
		playHand.deal(deck);
		return 0;//means the dealer is not done playing
	}
	if(playHand.getSum() > 21)
	{
		playHand.handleAce();
	}
	return 1;//means the dealer is done playing
}

double findName (string username);
void printFile ();
void addName (Player player1, int flag);

double findName (string name)
{

	ifstream fp ("saveFile.txt");
	double bank = 0;
	string content, bankStr;
	
	while(! fp.eof())
    {
		getline(fp,content);
		string::size_type pos =content.find(' ');
		if(content.npos != pos) 
		{
			bankStr = content.substr(pos + 1);
			content = content.substr(0, pos);
		}
		bank = atoi(bankStr.c_str());
		//do we want it to be case sensitive?? right now it is.  if no implement tolower()function
		if(name == content)
		{
			fp.close();
			return bank;
		}
    }
	bank = -1;
	cout<< "user not found."<< endl;
	fp.close();
	return bank;
}

int checkDup (string username)
{
	string content, bankStr;
	ifstream fp ("saveFile.txt");
	while(! fp.eof())
    {
		getline(fp,content);
		string::size_type pos =content.find(' ');
		if(content.npos != pos) 
		{
			bankStr = content.substr(pos + 1);
			content = content.substr(0, pos);
		}
		
		//do we want it to be case sensitive?? right now it is.  if no implement tolower()function
		if(username == content)
		{
			fp.close();
			return -1;
		}
    }
	fp.close();
	return 0;
	//make this catch throw error checking as well
}

void printFile ()
{
	ifstream fp ("saveFile.txt");
	string content, bankStr;
	int bank;
	while(! fp.eof())
    {
		getline(fp,content);
		string::size_type pos =content.find(' ');
		if(content.npos != pos) 
		{
			bankStr = content.substr(pos + 1);
			content = content.substr(0, pos);
		}
		bank = atoi(bankStr.c_str());
		cout <<"Username:"<<content<< "| Bank:"<<bank<< endl;
    }
	cout << endl;
	fp.close();
}

void addName (Player player1, int flag)
{
	FILE* fp = fopen("saveFile.txt", "a" );
	string name = player1.getName();
	char nameC[name.size()+1];//as 1 char space for null is also required
	strcpy(nameC, name.c_str());//copies the string and puts it in type char*
	if (flag == 1)
		fprintf(fp, "%s %.0f", nameC, player1.getBank());
	else
		fprintf(fp, "\n%s %.0f", nameC, player1.getBank());
	fclose (fp);
}

void updateFile (string username, double bank)
{
	ifstream fp ("saveFile.txt");
	string content, bankStr;
	vector <string> users;
	vector <double> banks;
	double bank1;
	int i = 0;
	
	while(! fp.eof())//getting the contents of the file into our vectors 
    {
		
		getline(fp,content);
		string::size_type pos =content.find(' ');
		if(content.npos != pos) 
		{
			bankStr = content.substr(pos + 1);
			content = content.substr(0, pos);
		}
		bank1 = atoi(bankStr.c_str());//out the string bank into an integer
			
		users.push_back(content);
		banks.push_back(bank1);	
		//cout << users[i] << endl;
		//cout << banks[i] << endl;		
		i++;
    }
	fp.close();
	//we are going to update the player in the vector, check to make sure there are no players with bank = 0 (they will get deleted), reprint to file
	for ( i = 0; i < users.size(); i++)
	{
		if (username == users[i])
		{
			banks[i] = bank;
			//break;//break because we only save one player at a time so we can stop looking
		}
		
		if (banks[i] == 0)//|| users[i] == "")
		{
			users.erase (users.begin()+i);//this also takes care of any blank lines that might occur on accident 
			banks.erase (banks.begin()+i);
		}
	}
	
	ofstream fileptr;
	fileptr.open("saveFile.txt", std::ofstream::out | std::ofstream::trunc);//opens and deletes everything
	for (i = 0; i < users.size(); i++)
	{
		if (i == users.size()-1)//just the convention for the file we decided-- we don't want a blank line at the end of the file
			fileptr << users[i]<<" " <<banks[i];
		else
			fileptr << users[i]<<" " <<banks[i]<<endl;
	}
	


	fileptr.close();
	
}

void handleBets (Dealer dealer, Player player1, int bet)
{
	Hands hand = *(player1.gethand());
	int sum = hand.getSum();
	double bank = player1.getBank();
	//----------dealer-----------------
	Hands handD = *(dealer.gethand());
	int sumD = handD.getSum();
	
	cout << player1.getName() << "'s sum: " << sum << endl;
	if (sum > 21 && sumD > 21)//Dealer and Player Bust
	{
		cout << player1.getName() << ", you and the dealer both bust. You keep your bet, your bank now has $" << bank << endl;	
	}
	else if (sum == sumD)//Dealer and Player Push
	{
		cout << player1.getName() << ", you pushed. You keep your bet. Your bank now has $" << bank << endl;
	}
	else if (sum == -1)
	{
		bank = bank + (int)((bet * 1.5) + .5);
		cout << player1.getName() << ", you got Blackjack! Blackjack pays out 3 to 2. Your bank now has $" << bank << endl;
	}
	else if(sum > 21)//Player bust
	{
		bank = bank - bet;
		cout << "Sorry " << player1.getName() << ", you busted. Your bank now has $" << bank << endl;
	}
	else if(sumD > 21)//Dealer bust
	{
		bank = bank + bet;
		cout << "Congrats " << player1.getName() << ", you won. Your bank now has $" << bank << endl;
	}
	
	else if(sumD < sum)//Player Wins
	{
		bank = bank + bet;
		cout << "Congrats " << player1.getName() << " you won. Your bank now has $" << bank << endl;
	}
	else//Dealer wins
	{
		bank = bank - bet;
		cout<< "Sorry "<< player1.getName()<< ", you lost. Your bank now has $"<< bank<< endl;
	}
	updateFile (player1.getName(), bank);
}

int errorCheck (string content)//makes sure the input is a string
{
	int num = atoi(content.c_str());
	return num;
}

int main (void)
{
	string username;

	int selection;
	int numPlayers;
	int fileStatus = 0;
	string content;
	double x;
	//string userInfo = "-1";
	ifstream fp ("saveFile.txt");
	//this determines the menu -- if there are saved players then a menu with option to loaad displays and vice versa
	if (fp.fail()) //makes sure the file opens -- if it doesn't then it creates a file
	{
		cout<< "Error Opening File" << endl<<"New file created"<< endl;
		ofstream fp ("saveFile.txt");
		fileStatus = 0;
	}
	else if ( fp.peek() != ifstream::traits_type::eof() )//checks if the file is not empty 
	{
		fileStatus = 1;//has files in it
	}
	else
	{
		fileStatus = 0;//means that there are no users saved
		
	}
	fp.close();
	vector <Player> table;
	Cards deck[52];//set up the deck
	deck->initializeDeck ();
	
	if (fileStatus == 0)//no saved games
	{
		cout<< "Enter number of players: (Maximum:4, Minimum: 1)" << endl;
		cin>> content;
		numPlayers = errorCheck (content);
			while (numPlayers < 1 || numPlayers > 4)
			{
				cout<< "Invalid input.  Please enter either 1, 2, 3, or 4"<< endl;
				cin >> content;
				numPlayers = errorCheck (content);
				//need a way to error check if a non integer is entered how to make sure it the program doesn't blow up
			}
			
		for (int i = 0; i < numPlayers; i ++)
		{
			Hands tempHand (deck);
			cout <<"Enter username for player "<<i+1<<":";
			cin >>username;
			int num = checkDup (username);
			while(num == -1)
			{
				cout<<"Username already exists.  Please enter a new name:"<<endl;
				cin >>username;
				num = checkDup (username);
			}
			Player tempPlayer (tempHand,500, username);
			table.push_back(tempPlayer);
			addName(tempPlayer,1);
		}
	}
	else//there are saved users
	{
		
		cout<< "Enter number of players: (Maximum:4, Minimum: 1)" << endl;
		cin>> content;
		numPlayers = errorCheck (content);
				while (numPlayers < 1 || numPlayers > 4)
				{
					cout<< "Invalid input.  Please enter either 1, 2, 3, or 4"<< endl;
					cin>> content;
					numPlayers = errorCheck (content);
				}
	for (int i = 0; i < numPlayers; i++)
	{
		
		cout<< "1: Create New Player" << endl << "2: Load Saved Player"<< endl;
		cin>> content;
		selection = errorCheck (content);
		while (selection < 1 || selection > 2)
				{
					cout<< "Invalid input.  Please enter either 1 or 2"<< endl;
					cin>> content;
					selection = errorCheck (content);
				}
		if (selection == 1)//same as above--creating a new player
		{
			
			
				Hands tempHand (deck);
				cout <<"Enter username for player "<<i+1<<":";
				cin >>username;
				int num = checkDup (username);
				while(num == -1)
				{
					cout<<"Username already exists.  Please enter a new name:"<<endl;
					cin >>username;
					num = checkDup (username);
				}
				Player tempPlayer (tempHand,500, username);
				table.push_back(tempPlayer);
				addName(tempPlayer, 0);
				
				
			
		}
		else if (selection == 2)//they want to load a new player
		{
			while (selection == 2)
			{
				cout<< "1. Enter a username" << endl << "2. See directory of users" << endl<<"3. Create a new player" << endl;
				cin >> content;
				selection = errorCheck(content);
					while (selection < 1 || selection > 3)
					{
						cout<< "invalid input. Please try again.\n"<< "1. Enter a username" << endl << "2. See directory of users" << endl<<"3. Start new game" << endl;
						cin >> content;
						selection = errorCheck(content);
					}
					if (selection == 1)//entering a username to start the game from
					{
						
						cout << "Enter username for player" <<i+1<<":";
						cin >>username;
						cout<< "Entered username"<< endl;
						double tempBank = findName(username);
						//cout << "made it back->" << tempBank<< endl;
						while(tempBank == -1 )//this happens if the name was not found
						{
							int selection1;
							cout<< "1. Enter new username 2. See directory ";//give the user the option to see all usernames 
							cin >> content;
							selection1 = errorCheck(content);
							while (selection1 < 1 || selection1 > 2)
							{
								cout<< "Invalid input.  Please enter 1 or 2:"<< endl;
								cin >> content;
								selection1 = errorCheck(content);
							}
							if (selection1 == 1)
							{
								cout << "Enter username:";
								cin >> username;
								tempBank = findName(username);//WHY WONT THEY FIND THE NAME THIS TIME WHAT IS DIFFERENT!?!?
								cout << tempBank<<endl;
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
						int num = checkDup (username);
						while(num == -1)
						{
							cout<<"Username already exists.  Please enter a new name:"<<endl;
							cin >>username;
							num = checkDup (username);
						}
						Player tempPlayer (tempHand,500, username);
						table.push_back(tempPlayer);
						addName(tempPlayer,0);
					}
				
			}	
		}
	}	
	}	
	
//PLAY GAME!!
int j;
int sum = 0;
int playSelect;
Hands handD(deck);//set up the dealer
Dealer dealer(handD);
int bets [numPlayers];
int play = 1;
int betTemp;
//while (1)
{	
	for(j = 0; j < numPlayers; j++)
	{
		cout<< table[j].getName()<< " it is your turn.  You have $"<<table[j].getBank()<<". How much would you like to bet?"<< endl<< ">>";
		cin>> content;
		bets[j] = errorCheck (content);
		while (bets[j] == 0 || bets[j] > table[j].getBank())
		{
			if (bets[j] == 0 )
				cout<< "You cannot bet $0.  Enter a new value."<< endl;
			else
			cout<< "You cannot bet more than your bank($"<<table[j].getBank()<<").  Enter a new value."<< endl;
			
			cin>> content;
			bets[j] = errorCheck (content);
		}	
		dealer.displayDealer();
		table[j].displayPlayer();
		
		while (1)
		{
			Hands hand = *(table[j].gethand());
			sum = hand.getSum();
			if (sum > 21)
			{
				sum = (table[j].gethand())->handleAce();
				if(sum > 21)
					break;
			}
			if (sum == 21 && ((table[j].gethand())->getHand().size()) == 2)
			{
				cout<<"BLACKJACK!!"<<endl;
				(table[j].gethand())->setSum(-1);
				break;
			}
			if (sum == 21)
				break;
			cout<< "Do you want to (1) hit or (2) stay?"<<endl<<">>";
			cin >> content;
			playSelect = errorCheck(content);
			while (playSelect != 1 && playSelect!= 2)
			{
				cout<< "Incorrect input: Please select (1) to hit or (2) to stay: ";
				cin >> content;
				playSelect = errorCheck(content);
			}
			if (playSelect == 1)
			{
				table[j].hit(deck);
				table[j].displayPlayer();
			}
			else
			{
				cout<<"----stay-------"<< endl;
				break;
			}
		}
	}

	//dealer plays after everyone else correct??
	int dealerCount = 0;
	
	while (dealerCount == 0)//the dealer keeps playing until the get to 17
	{
			dealerCount= dealer.playGame(deck);		
	}
	Hands hand = *(dealer.gethand());
	cout << "Dealers hand after playing: ";
	hand.display();
	cout << "Dealer's sum: " << dealer.gethand()->getSum() << endl;
	sum = hand.getSum();
	for (j = 0; j < numPlayers; j++)//handle the bets of all of the players
	{
		handleBets(dealer, table[j], bets[j]);
		/*cout <<table[j].getName()<< " would you like to play again? Yes(1) or No(2)"<< endl<< ">>";
		cin >> play;
			if (play ==  2)
			{
				numPlayers--;
				table.erase (table.begin()+j);
				
				if (numPlayers == 0)
				{
					free(bets);
					return 0;
				}
			}*/
	}
	
	/*for (j = 0; j < numPlayers; j++)
	{
		handleBets(dealer, table[j], bets[j]);
	}*/



}
//free(bets);

return 0;
}

//Ace needs to be handled->11 or 1
//if dealer and player busts what happens*DONE*
//I dont want to do play multipe games-- its a pain in the ass
//a shit ton of error checking


