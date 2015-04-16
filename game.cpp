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
		}
		userList[i] = masterList[j];
	}
	cout << "You're now ready to fight!\n" << endl;
}
void game::compPick()
{
	compList = new figure[compListSize];
	for(int i = 0; i < compListSize; i++)
	{
		srand(time(NULL));
		compList[i]=masterList[(rand()+i*4)%10];
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
	string figure = "";
	int i = 0;
	bool found = false;
	while(input != "2")
	{
		cout << "Your opponent is " << compList[0].name << "\n" << endl;
		cout << "1. Pick your fighter" << endl;
		cout << "2. Concede\n" << endl;
		getline(cin, input);
		cout << endl;
		if(input == "1")
		{
			while(!found)
			{
				found = false;
				printUserList();
				getline(cin, figure);
				cout << endl;
				for(int i = 0; i < userListSize; i++)
				{
					if(userList[i].name == figure)
					{
						found = true;
						break;
					}
				}
				if(found)
					break;
				cout << "You don't have that character!" << endl;
			}
			result(figure);
		}
		else if(input == "2")
		{
			cout << "You conceded. The computer wins!\n" << endl;
			resetUserPicks();
			resetCompPicks();
			return;
		}
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
void game::removeFigure(string figure, string list)
{
	int i = 0;
	if(list == "user")
	{
		for(i = 0; i < userListSize; i++)
		{
			if(userList[i].name == figure)
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
void game::result(string figure1)
{
	bool userSpeed = false;
	bool compSpeed = false;
	figure userPick;
	for(int i = 0;i < userListSize; i++)
	{
		if(userList[i].name == figure1)
		{
			userPick = userList[i];
			break;
		}
	}
	figure compPick = compList[0];
	srand(time(NULL));
	int random = rand()%20;
	if(compPick.special > random&&userPick.special > random)
	{
		cout << "Both characters were too amazing to lose. Draw!" << endl;
		return;
	}
	if(userPick.special > random)
	{
		cout << "Luck was on your character's side. You win!" << endl;
		removeFigure(compPick.name, "comp");
		return;
	}
	if(compPick.special > random)
	{
		cout << "Luck was on the computer character's side. You lose." << endl;
		removeFigure(userPick.name, "user");
		return;
	}
	if(userPick.speed > random)
	{
		userPick.attack++;
		userPick.defense++;
		userSpeed = true;
		cout << "Due to your speed, your attack and defense have each been raised one point!" << endl;
	}
	if(compPick.speed > random)
	{
		compPick.attack++;
		compPick.defense++;
		compSpeed = true;
		cout << "Due to the computer's speed, their attack and defense have each been raised one point" << endl;
	}
	int user = userPick.attack - compPick.defense;
	int comp = compPick.attack - userPick.defense;
	if(user > comp)
	{
		cout << "You have defeated " << compPick.name << "!" << endl;
		removeFigure(compPick.name, "comp");
	}
	else if(comp > user)
	{
		cout << "The computer has defeated your " << userPick.name << "." << endl;
		removeFigure(userPick.name, "user");
	}
	else
	{
		cout << "Both characters are equal. Draw!" << endl;
	}
	if(userSpeed)
	{
		userPick.attack--;
		userPick.defense--;
	}
	if(compSpeed)
	{
		compPick.attack--;
		compPick.defense--;
	}
}