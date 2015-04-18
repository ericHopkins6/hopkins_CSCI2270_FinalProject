#include <iostream>
#include "game.h"
using namespace std;

int main(int argc, char* argv[])
{
	game* obj = new game();
	obj->readIn(argv[1]);
	string input = "";
	string sizeStr = "";
	string name = "";
	int size = 0;
	cout << "\nWelcome to All-Star Arena!" << endl;
	while(input != "4")
	{
		cout << "\n1. See entire inventory" << endl;
		cout << "2. Inspect Characters" << endl;
		cout << "3. Get Started!" << endl;
		cout << "4. Quit\n" << endl;
		getline(cin, input);
		cout << endl;
		if(input == "1")
		{
			obj->printMasterList();
		}
		else if(input == "2")
		{
			cout << "Which character would you like to learn about?\n" << endl;
			getline(cin, name);
			cout << endl;
			obj->displayStats(name);
		}
		else if(input == "3")
		{
			input = "";
			obj->resetCompPicks();
			obj->resetUserPicks();
			bool hit1 = false;
			while(input != "6")
			{
				cout << "1. Pick your inventory" << endl;
				cout << "2. Inspect your inventory" << endl;
				cout << "3. Reset the computer's inventory" << endl;
				cout << "4. Inspect the computer's inventory" << endl;
				cout << "5. Battle!" << endl;
				cout << "6. Back to the main menu\n" << endl;
				getline(cin, input);
				cout << endl;
				if(input == "1")
				{
					size = 11;
					while(size>5||size<1)
					{
						cout << "How many characters would you like?\n" << endl;
						getline(cin, sizeStr);
						cout << endl;
						size = stoi(sizeStr);
						if(size>5 ||size<1)
							cout << "Invalid size\n" << endl;
					}
					obj->resetUserPicks();
					obj->userPick(size);
					obj->compPick();
					hit1 = true;
				}
				else if(input == "2")
				{
					if(!hit1)
						cout << "Pick your characters first!\n" << endl;
					else
						obj->printUserList();
				}
				else if(input == "3")
				{
					if(!hit1)
						cout << "Pick your characters first!\n" << endl;
					else
					{
						obj->resetCompPicks();
						obj->compPick();
					}
				}
				else if(input == "4")
				{
					if(!hit1)
						cout << "Pick your characters first!\n" << endl;
					else
						obj->printCompList();
				}
				else if(input == "5")
				{
					if(!hit1)
						cout << "Pick your characters first!\n" << endl;
					else
					{
						obj->battle();
						hit1 = false;
					}
				}
			}
		}
	}
	cout << "Goodbye!" << endl;
	obj->~game();
}