#include "Interaction.h"
using namespace std;

int main(){
	//class initialization
	Player guy = Player(1,0,'@');
	Board world = Board();
	
	world.setMap(0,4,8);
	world.setRow(0,0,(char*)"[      ]");
	world.setRow(0,1,(char*)"[ Andy ]");
	world.setRow(0,2,(char*)"[ Phan ]");
	world.setRow(0,3,(char*)"[      ]");
	
	world.printBoard(guy);
	while(true){
		coordinates temp;
		temp = turn(&world,&guy);
	}
}