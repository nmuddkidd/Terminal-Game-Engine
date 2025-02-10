#include "Player.h"
#include "World.h"

struct coordinates{
	int x;
	int y;
};

coordinates turn(Board*,Player*);

coordinates turn(Board *map, Player *guy){
	char input;
	int collision;
	coordinates temp;
	cout << "Movement (w/a/s/d): ";
	cin >>  input;
	while(!(input=='w'||input=='a'||input=='s'||input=='d')){
		cout << "Invalid movement, try again: ";
		cin >> input;
	}
	cin.ignore(256, '\n');
	collision = guy->move(input,map->getMap().rows,map->getMap().columns,map->getMap().map);
	if(collision==-1){
		cout << "You bumped into something ?? why ??" << endl;
	}
	if(collision==1){
		map->findDoor(guy->getpX(),guy->getpY());
	}
	map->printBoard(*guy);
	temp.x=guy->getX();
	temp.y=guy->getY();
	return temp;
}