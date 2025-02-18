#include <iostream>
#include <stdlib.h>
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

Board::Board(){
	doors = (door*) malloc(0);
	maps = (map*) malloc(0);
	mapsSize=0;
	doorsSize=0;
	//Sets the size of the arrays to 0 and reserves memory
	
	currentMap=0;
	maps = (map*) malloc(sizeof(map));
	mapsSize++;
	maps[currentMap].map = (char **) malloc(3*sizeof(char*));
	for(int i=0; i<3; i++){
		maps[currentMap].map[i]= (char *) malloc(3*sizeof(char));
		for(int j=0; j<3;j++){
			maps[currentMap].map[i][j]=' ';
		}
		maps[currentMap].map[i][0]='[';
		maps[currentMap].map[i][2]=']';
	}
	//Initializes starting map (0) to a 3x3 empty
	//Can be changed later
	//Each char must be set individually
}

void Board::printBoard(Player player){
	char temp = maps[currentMap].map[player.getY()][player.getX()];
	//saves the char the player was on
	maps[currentMap].map[player.getY()][player.getX()] = player.getIcon();
	//places the player char down
	for(int i=0; i<maps[currentMap].rows; i++){
		for(int j=0; j<maps[currentMap].columns; j++){
			cout << maps[currentMap].map[i][j];
		}
		cout << endl;
	}
	//prints each char
	maps[currentMap].map[player.getY()][player.getX()] = temp;
	//replaces where the player was with the stored char
}

void Board::addDoor(int origin,int originx,int originy,int target,int targetx,int targety){
	doors = (door*) realloc(doors,sizeof(door)*(doorsSize+1));
	doorsSize++;
	//increases the size of the doors array by one
	doors[doorsSize-1].origin = origin;
	doors[doorsSize-1].originX = originx;
	doors[doorsSize-1].originY = originy;
	doors[doorsSize-1].target = target;
	doors[doorsSize-1].targetX = targetx;
	doors[doorsSize-1].targetY = targety;
	//assigns the new door information
}

void Board::addMap(int r, int c,char** m){
	maps = (map*) realloc(maps,sizeof(map)*(mapsSize+1));
	mapsSize++;
	//increases the maps size by one
	maps[mapsSize-1].rows=r;
	maps[mapsSize-1].columns=c;
	//assigns basic information
	maps[mapsSize-1].map = (char**) malloc(r*sizeof(char*));
	for(int i=0; i<r; i++){
		maps[mapsSize-1].map[i] = (char*) malloc(c*sizeof(char));
		setRow(mapsSize-1,i,m[i]);
	}
	//assigns the map information one char at a time
}

void Board::addMap(int r, int c){
	maps = (map*) realloc(maps,sizeof(map)*(mapsSize+1));
	mapsSize++;
	//increases the maps size by one
	maps[mapsSize-1].rows=r;
	maps[mapsSize-1].columns=c;
	//assigns basic information
	maps[mapsSize-1].map = (char**) malloc(r*sizeof(char*));
	for(int i=0; i<r; i++){
		maps[mapsSize-1].map[i]= (char*) malloc(c*sizeof(char));
		for(int j=0; j<c;j++){
			maps[mapsSize-1].map[i][j]=' ';
		}
		maps[mapsSize-1].map[i][0]='[';
		maps[mapsSize-1].map[i][c-1]=']';
	}
	//assigns the map information one char at a time
}

int Board::findDoor(int* x,int* y){
	for(int i=0; i<doorsSize; i++){
		if(doors[i].origin==currentMap && *x == doors[i].originX && *y ==doors[i].originY){
			currentMap=doors[i].target;
			*y = doors[i].targetY;
			*x = doors[i].targetX;
			return 0;
		}
	}
	return -1;
	//cycles through each door checking if the X and Y position provided matches any door
	//if no door is found -1 is returned
	//if one is currentMap, entity X, and entity Y is changed
}

void Board::setMap(int mp,int r,int c,char** m){
	if(mp<0||mp>mapsSize-1){
		cout << "ERR: INDEX OUT OF BOUNDS in function Board::setMap(int,int,int,char**)" << endl;
		throw mp;
	}
	maps[mp].map = (char**) malloc(0);
	//clears old map
	maps[mp].rows=r;
	maps[mp].columns=c;
	//assigns basic data
	maps[mp].map = (char**) malloc(r*sizeof(char*));
	for(int i=0; i<r; i++){
		maps[mp].map[i]= (char*) malloc(c*sizeof(char));
		setRow(mp,i,m[i]);
	}
	//copies given map into new map
}

void Board::setMap(int mp,int r,int c){
	if(mp<0||mp>mapsSize-1){
		cout << "ERR: INDEX OUT OF BOUNDS in function Board::setMap(int,int,int)" << endl;
		throw mp;
	}
	maps[mp].map = (char**) malloc(0);
	//clears old map
	maps[mp].rows=r;
	maps[mp].columns=c;
	//copies basic data
	maps[mp].map = (char**) malloc(r*sizeof(char*));
	for(int i=0; i<r; i++){
		maps[mp].map[i]= (char*) malloc(c*sizeof(char));
		for(int j=0; j<c;j++){
			maps[mp].map[i][j]=' ';
		}
		maps[mp].map[i][0]='[';
		maps[mp].map[i][c-1]=']';
	}
	//sets new map to a blank area
}

void Board::setRow(int mp,int r,char* str){
	if(r<0||r>=maps[mp].rows){
		cout << "ERR: INDEX OUT OF BOUNDS in function Board::setRow(int,int,char)" << endl;
		throw r;
	}
	//throws an error if given information doesnt work
	for(int i=0;i<maps[mp].columns;i++){
		setChar(mp,i,r,str[i]);
	}
	//sets a row to a given string one char at a time
}

void Board::setChar(int mp,int x,int y,char c){
	if(y<0||y>=maps[mp].rows||x<0||x>maps[mp].columns){
		cout << "ERR: INDEX OUT OF BOUNDS in function Board::setChar(int,int,char)" << endl;
		throw x,y;
	}
	//throws an error if given information doesnt work
	maps[mp].map[y][x]=c;
	//finds a coordinate on a map and sets it to a given char
}

void Board::setcMap(int c){
	if(c<0||c>mapsSize-1){
		cout << "ERR: INDEX OUT OF BOUNDS in function Board::setcMap(int)" << endl;
		throw c;
	}
	currentMap=c;
}
int Board::getCurrentMap(){return currentMap;}

map Board::getMap(int mp){return maps[mp];}
map* Board::getPMap(int mp){return &maps[mp];}
char Board::getChar(int mp,int x,int y){return maps[mp].map[y][x];}

map Board::getMap(){return maps[currentMap];}
map* Board::getPMap(){return &maps[currentMap];}
char Board::getChar(int x,int y){return maps[currentMap].map[y][x];}