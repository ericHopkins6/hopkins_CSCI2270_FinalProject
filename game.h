#ifndef GAME_H
#define GAME_H
struct figure
{
	std::string name;
	int attack;
	int speed;
	int defense;
	int special;
};
class game
{
	private:
		figure* masterList;
		figure* userList;
		figure* compList;
		int userListSize;
		int compListSize;
		int masterListSize;
	public:
		game();
		virtual ~game();
		void resetUserPicks();
		void resetCompPicks();
		void readIn(std::string str);
		void printMasterList();
		void printUserList();
		void printCompList();
		void userPick(int num);
		void compPick();
		void displayStats(std::string name);
		void battle();
		void result(figure figure1);
		void removeFigure(figure userPick, std::string list);
};
#endif