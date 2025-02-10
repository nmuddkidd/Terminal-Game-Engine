#include "Interaction.h"
using namespace std;

int main(){
	//class initialization
	Player guy = Player(1,0,'@');
	Board world = Board();
	
	world.setMap(0,4,8);
	world.setRow(0,0,(char*)"[ Map1 ]");
	world.setRow(0,1,(char*)"[ Door ]");
	world.setRow(0,2,(char*)"[  EE  ]");
	world.setRow(0,3,(char*)"[      ]");
	world.addDoor(0,3,2,1,1,0);
	world.addDoor(0,4,2,1,1,0);
	
	world.addMap(3,8);
	world.setRow(1,0,(char*)"[ Map2 ]");
	world.setRow(1,1,(char*)"[  EE  ]");
	world.setRow(1,2,(char*)"[      ]");
	world.addDoor(1,3,1,0,1,0);
	world.addDoor(1,4,1,0,1,0);
	
	world.printBoard(guy);
	while(true){
		coordinates temp;
		temp = turn(&world,&guy);
	}
}