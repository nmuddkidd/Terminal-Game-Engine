#include "Player.h"
#include "World.h"
#include <conio.h>

struct coordinates{
	int x;
	int y;
};

coordinates turn(Board*,Player*);

coordinates turn(Board *map, Player *guy){
	char input;
	int collision;
	coordinates temp;
	//cout << "Movement (w/a/s/d): ";
	input = getch();
	/*while(!(input=='w'||input=='a'||input=='s'||input=='d')){
		cout << "Invalid movement, try again: ";
		cin >> input;
	}*/
	collision = guy->move(input,map->getMap().rows,map->getMap().columns,map->getMap().map);
	if(collision==-1){
		//cout << "You bumped into something ?? why ??" << endl;
	}
	if(collision==1){
		map->findDoor(guy->getpX(),guy->getpY());
	}
	cout << '\n';
	system("cls");
	map->printBoard(*guy);
	temp.x=guy->getX();
	temp.y=guy->getY();
	return temp;
}