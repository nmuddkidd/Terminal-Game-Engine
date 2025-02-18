#include <iostream>
#include "World.h"
using namespace std;

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