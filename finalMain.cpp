#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <fstream>
using namespace std; 

double findName (string username);
void printFile ();
double findName (string username)
{
	char* garbage;
	double bank = 0;
	int num;
	FILE* fp = fopen ("saveFile.txt", "r");
	fscanf(fp, "%f", num);
	
	while (fscanf (fp, "%s|%f", &garbage, &bank) == 2)
	{
		if (strcmp (garbage, username)== 0)
		{
			fclose(fp);
			return bank;
		}		
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


int main (void)
{
	fstream fp;
	string username ;
	int selection;
	int numPlayers;
	int fileStatus;
	string userInfo = "-1";
	fp.open ("saveFile.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	fp>>fileStatus;
	cout<< fileStatus<< endl;
	fp.close();
	vector <Players> table;
	//Player tempPlayer;
	//Hands	tempHand;
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
			Hand tempHand (deck);
			cout <<"Enter username for player "<<i+1<<":";
			cin >>username;
			Player tempPlayer (tempHand,500, username);
			table.push_back(tempPlayer);
			
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
			
			
				Hand tempHand (deck);
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
						
						cout << "Enter username for player" <<i<<":";
						cin >>username;
						double tempBank;
						tempBank = findName(username);
						while(tempBank == -1 )//this happens if the name was not found
						{
							int selection1;
							cout<< "1. Enter new username 2. See directory ";//give the user the option to see all usernames 
							cin >> selection1;
							if (selection == 1)
							{
								cout << "Enter username:"
								cin >> username;
								tempBank = findName(username);
							}
							else 
								printFile();							
						}
						Hand tempHand (deck);
						Player tempPlayer (tempHand,tempBank, username);
						table.push_back(tempPlayer);
						
					}
					else if (selection == 2)//want to see a list of the users that have saved games
					{
						printFile();
					}
					else if (selection == 3)//starting a brand new game--same as above
					{
						Hand tempHand (deck);
						cout <<"Enter username for player "<<i+1<<":";
						cin >>username;
						Player tempPlayer (tempHand,500, username);
						table.push_back(tempPlayer);
					}
				
			}	
		}
	}	
	}	
//consider have a vector of players to keep track of them
	/*if (username != "-1")//meaning they input something for user name
	{
		//create pointers to objects with the specs in the file
		
	}
	else
	{
		//enter username for each player
		//create pointers to objects with default
	}*/
	
	//Theoretically all player objects are set up 
		
	//Set up table
	//------------------------------------------------------------------------------------
	/*Cards deck[52];
	deck->initializeDeck ();
	
	Hands handD(deck);
	Dealer dealer(handD);
	//display all players cards and dealers one card
	//give each player option to hit or stay.  they keep going until they decide to stay or they bust 
	//dealer plays 
	//bets handled
	
	
	
	srand(time(NULL));
			
	Hands handE(deck);
	Player Eric(handE, rand()%4 +1, "Eric");
	
	Hands handN(deck);
	Player Sammy(handN, rand()%4 +1, "Sammy");
	//------------------------------------------------------------------------------------
	
	//Display hands
	//------------------------------------------------------------------------------------
	dealer.displayDealer();
	cout <<endl<< "----------ERIC----------" << endl;
	Eric.displayPlayer();
	cout << "HIT" <<endl;
	Eric.hit(deck);
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
	while (i == 0)
	{
		i = dealer.playGame(deck);
		
	}
	cout << "Dealer after playing:" << endl;
	dealer.displayDealer();
	*/
	
	
	
	return 0;
}

