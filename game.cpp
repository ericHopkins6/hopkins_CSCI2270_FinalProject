#include <iostream>
#include <fstream>
#include <time.h>
#include "game.h"
using namespace std;

game::game()
{
	masterListSize = 10;
	userListSize = 0;
	compListSize = 0;
	masterList = new figure[masterListSize];
}
game::~game()
{
	for(int i = 0; i < masterListSize; i++)
	{
		masterList[i].name = "";
		masterList[i].attack = 0;
		masterList[i].speed = 0;
		masterList[i].defense = 0;
		masterList[i].special = 0;
	}
	resetCompPicks();
	resetUserPicks();
}
void game::readIn(string str)
{
	ifstream in;
	in.open(str);
	string line;
	int start = 0;
	int i = 0;
	int j = 0;
	while(getline(in, line))
	{
		i = 0;
		start = i;
		figure f;
		//name
		while(line[i] != ',')
			i++;
		string name = line.substr(start, i-start);
		f.name = name;
		//attack
		i++;
		start = i;
		while(line[i] != ',')
			i++;
		int attack = stoi(line.substr(start, i-start));
		f.attack = attack;
		//speed
		i++;
		start = i;
		while(line[i] != ',')
			i++;
		int speed = stoi(line.substr(start, i-start));
		f.speed = speed;
		//defense
		i++;
		start = i;
		while(line[i] != ',')
			i++;
		int defense = stoi(line.substr(start, i-start));
		f.defense = defense;
		//special
		i++;
		start = i;
		while(line[i] != ',')
			i++;
		int special = stoi(line.substr(start, i-start));
		f.special = special;
		//add f
		masterList[j] = f;
		j++;
	}
}
void game::userPick(int num)
{
	userListSize = num;
	compListSize = num;
	string name = "";
	bool found = false;
	userList = new figure[userListSize];
	int j = 0;
	for(int i = 0; i < userListSize; i++)
	{
		found =false;
		while(!found)
		{
			cout << "Pick your next character.\n" << endl;
			printMasterList();
			printUserList();
			getline(cin, name);
			cout << endl;
			for(j = 0; j < masterListSize; j++)
			{
				if(masterList[j].name==name)
				{
					found = true;
					break;
				}
				else if(j == masterListSize-1)
					cout << "Character not found\n" << endl;
			}
			for(int j = 0; j < userListSize; j++)
			{
				if(name == userList[j].name)
				{
					cout << "You've already chosen that character!\n" << endl;
					found = false;
					break;
				}
			}
		}
		userList[i] = masterList[j];
	}
	cout << "You're now ready to fight!\n" << endl;
}
void game::compPick()
{
	figure* tempList = new figure[masterListSize];
	int k = 0;
	bool found = false;
	for(int i = 0; i < masterListSize; i++)
	{
		found = false;
		for(int j = 0; j < userListSize; j++)
		{
			if(masterList[i].name == userList[j].name)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			tempList[k]=masterList[i];
			k++;
		}
	}
	compList = new figure[compListSize];
	for(int i = 0; i < compListSize; i++)
	{
		srand(time(NULL));
		compList[i] = tempList[(rand()+i*4)%(masterListSize-userListSize)];
	}
}
void game::resetUserPicks()
{
	for(int i = 0; i < userListSize; i++)
	{
		userList[i].name = "";
		userList[i].attack = 0;
		userList[i].speed = 0;
		userList[i].defense = 0;
		userList[i].special = 0;
	}
	userListSize = 0;
}
void game::resetCompPicks()
{
	for(int i = 0; i < compListSize; i++)
	{
		compList[i].name = "";
		compList[i].attack = 0;
		compList[i].speed = 0;
		compList[i].defense = 0;
		compList[i].special = 0;
	}
	compListSize = userListSize;
}
void game::printMasterList()
{
	cout << "All fighters:" << endl;
	for(int i = 0; i < masterListSize; i++)
		cout << masterList[i].name << endl;
	cout << endl;
}
void game::printCompList()
{
	cout << "The computer's inventory:" << endl;
	for(int i = 0; i < compListSize; i++)
		cout << compList[i].name << endl;
	cout << endl;
}
void game::printUserList()
{
	cout << "Your inventory:" << endl;
	for(int i = 0; i < userListSize; i++)
		cout << userList[i].name << endl;
	cout << endl;
}
void game::displayStats(string name)
{
	int i = 0;
	for(i = 0; i < masterListSize; i++)
	{
		if(masterList[i].name==name)
			break;
		else if(i == masterListSize-1)
		{
			cout << "Character not found" << endl;
			cout << endl;
			return;
		}
	}
	cout << "Name: " << masterList[i].name << endl;
	cout << "Attack: " << masterList[i].attack << endl;
	cout << "Speed: " << masterList[i].speed << endl;
	cout << "Defense: " << masterList[i].defense << endl;
	cout << "Special: " << masterList[i].special << endl;
	cout << endl;
}
void game::battle()
{
	string input = "";
	int i = 0;
	bool found = false;
	while(input != "concede")
	{
		i = 0;
		cout << "Your next opponent is " << compList[0].name << "\n" << endl;
		cout << "Enter your next fighter or type \"concede\"\n" << endl;
		printUserList();
		getline(cin, input);
		cout << endl;
		if(input == "concede")
		{
			cout << "You conceded. The computer wins!" << endl;
			cout << "Resetting your inventory ... \n" << endl;
			resetUserPicks();
			resetCompPicks();
			return;
		}
		found = false;
		for(; i < userListSize; i++)
		{
			if(userList[i].name == input)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			cout << "You don't have that character!" << endl;
			return battle();
		}
		result(userList[i]);
		if(compListSize == 0)
		{
			cout << "You have won the battle! Congratulations!\n" << endl;
			resetUserPicks();
			resetCompPicks();
			return;
		}
		else if(userListSize == 0)
		{
			cout << "You have lost the battle. Try again!\n" << endl;
			resetUserPicks();
			resetCompPicks();
			return;
		}
		found = false;
	}
}
void game::removeFigure(figure figure1, string list)
{
	int i = 0;
	if(list == "user")
	{
		for(i = 0; i < userListSize; i++)
		{
			if(userList[i].name == figure1.name)
				break;
		}
		for(;i < userListSize-1;i++)
			userList[i] = userList[i+1];
		userListSize--;
	}
	if(list == "comp")
	{
		for(int i = 0; i < compListSize-1; i++)
			compList[i] = compList[i+1];
		compListSize--;
	}
}
void game::result(figure userPick)
{
	bool userSpeed = false;
	bool compSpeed = false;
	figure compPick = compList[0];
	srand(time(NULL));
	int compRandom = rand()%28;
	int userRandom = rand()%28;
	if(compPick.special > compRandom&&userPick.special > userRandom)
	{
		cout << "Both characters were too amazing to lose. Draw!" << endl;
		return;
	}
	if(userPick.special > userRandom)
	{
		cout << "Luck was on your character's side. You win!" << endl;
		removeFigure(compPick, "comp");
		return;
	}
	if(compPick.special > compRandom)
	{
		cout << "Luck was on the computer character's side. You lose." << endl;
		removeFigure(userPick, "user");
		return;
	}
	userRandom = rand()%15;
	compRandom = rand()%15;
	if(userPick.speed > userRandom)
	{
		userPick.attack+=2;
		userPick.defense+=2;
		userSpeed = true;
		cout << "Due to your speed, your attack and defense have each been raised two points!" << endl;
	}
	if(compPick.speed > compRandom)
	{
		compPick.attack+=2;
		compPick.defense+=2;
		compSpeed = true;
		cout << "Due to the computer's speed, their attack and defense have each been raised two points." << endl;
	}
	int user = userPick.attack - compPick.defense;
	int comp = compPick.attack - userPick.defense;
	if(user > comp)
	{
		cout << "You have defeated " << compPick.name << "!" << endl;
		removeFigure(compPick, "comp");
	}
	else if(comp > user)
	{
		cout << "The computer has defeated your " << userPick.name << "." << endl;
		removeFigure(userPick, "user");
	}
	else
	{
		cout << "Both characters are equal. Draw!" << endl;
	}
	if(userSpeed)
	{
		userPick.attack-=2;
		userPick.defense-=2;
	}
	if(compSpeed)
	{
		compPick.attack-=2;
		compPick.defense-=2;
	}
}