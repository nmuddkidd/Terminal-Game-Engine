class Player{
	private:
		int collision(char);
		//returns int based on what behavior should be exibited
		
		//location data
		int X;
		int Y;
		
		//icon for graphics
		char icon;
		
	public:
		Player(int,int,char);
		//initializes player with location
		int move(char, int, int, char**);
		//takes the input char and the char of the floor as inputs and increments X and Y respectively
		bool teleport(int,int);
		//getters and setters
		int getX();
		int getY();
		int* getpX();
		int* getpY();
		char getIcon();
		void setX(int);
		void setY(int);
		void setIcon(char);	
};

Player::Player(int x, int y, char i){
	X=x;
	Y=y;
	icon=i;
}

int Player::collision(char tile){
	//KEY
	// -1 = movement denied
	// 0 = movement permissive
	// 1 = door
	// Other things can be added for other interactions with the WORLD
	switch(tile){
		case ' ':
		case '*':
			return 0;
			break;
		case 'E':
			return 1;
			break;
	}
	return -1;
}

int Player::move(char input, int rows, int columns, char** map){
	//KEY
	// -1 = movement denied
	// 0 = movement permissive
	// 1 = door
	// Other things can be added for other interactions with the WORLD
	
	int x=X;
	int y=Y;
	//test varibles to see if movement is valid
	switch(input){
		case 'w':
			y--;
			break;
		case 'a':
			x--;
			break;
		case 's':
			y++;
			break;
		case 'd':
			x++;
			break;
	}
	//decoding movement chars into test varibles
	if(!(y>=0&&y<rows&&x>=0&&x<columns)){
		return -1;
	}
	//returns movement deny if movement would exit the confines of the array
	int temp = collision(map[y][x]);
	//tests that the coordinate being moved onto is movement permissible
	if(temp==-1){
		return temp;
	}
	//returns if its not
	X=x;
	Y=y;
	return temp;
	//sets new coordinates to player coordinates and returns outcome
}

bool Player::teleport(int x, int y){
	setX(x);
	setY(y);
	return true;
	//sets the players x and y coordinate to a value
}

int Player::getX(){return X;}
int Player::getY(){return Y;}
int* Player::getpX(){return &X;}
int* Player::getpY(){return &Y;}
char Player::getIcon(){return icon;}
void Player::setX(int x){X=x;}
void Player::setY(int y){Y=y;}
void Player::setIcon(char i){icon=i;}