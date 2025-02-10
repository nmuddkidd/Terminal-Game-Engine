#include <iostream>
using namespace std;

struct map{
	//Everything to make a map - displayed as multiple chars
	char** map;
	//Double pointer of chars, representing the playable grid
	int rows;
	//The number of rows in the map (Y)
	int columns;
	//The number of columns in the map (X)
};

struct door{
	//Everything to make a door - moving between worlds
	int target;
	//Target world
	int origin;
	//Origin/start world
	int originX;
	int originY;
	//Doorway location on doorway map
	int targetX;
	int targetY;
	//Target for placing the player on the new map
};

class Board{
	private:
		map* maps;
		//A dynamic array of maps, used to make new areas
		int mapsSize;
		//tracker for the maps array size
		door* doors;
		//A dynamic array of doors, used to travel between areas
		int doorsSize;
		//tracker for the doors array size
		int currentMap;
		//tracks the current map being displayed and interacted
		
	public:
		Board();
		//sets the size of the board
		void printBoard(Player);
		//prints the board with respect to the player
		void addDoor(int,int,int,int,int,int);
		//Adds a door with the data
		//origin map, origin x, origin y, target map, target x and target y
		//In that order
		void addMap(int,int,char**);
		//Adds a map with an already made design
		void addMap(int,int);
		//Adds a map with a default design
		//rows columns design
		int findDoor(int*,int*);
		//cycles through every door and teleports the entity if it fufills all the doors criteria
		//entity x, entity y
		
		//getters and setters
		void setMap(int,int,int,char**);
		//resets the map to a new map, with new size
		//targeted map, rows, columns, new map
		void setMap(int,int,int);
		//resets map with nothing in it
		//targeted map, rows, columns
		void setRow(int,int,char*);
		//sets the row to a string - mostly used in the set map method -- might privatize
		//targeted map, row, string
		void setChar(int,int,int,char);
		//sets char at a coordinate
		//targeted map, X position, Y position, new char
		void setcMap(int);
		//manually changes the current map -- might privatize
		int getCurrentMap();
		//returns the index of the current map
		map getMap(int);
		//returns a map struct at the given index
		map* getPMap(int);
		//returns the pointer of the map struct at the given index
		char getChar(int,int,int);
		//returns the char at location (map,X,Y)
		map getMap();
		//returns the selected map struct
		map* getPMap();
		//returns the pointer of the selected map
		char getChar(int,int);
		//returns the char at location (X,Y)
};