//minesweeper

//include library
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//function decoration
void randBomb();
void infobox();
int openBoard(int,int);

//global variables
int original[10][10];
int data[10][10];
int choose[10][10];

//main function
int main(){
	//declare variables
	int row,column,enter = 1;
	//greeting
	cout<<"Welcome to play minesweeper. This is 10x10 board."<<endl<<"There are total 10 Bomb. Please choose all the box which doesn't contain Bomb."<<endl<<" Good Luck! >.<"<<endl;
	//print board
	cout<<"   ";
	for(int i = 0;i<10;i++){
		cout<<i+1<<" ";
	}
	cout<<endl;
	for(int i = 0;i < 10;i++){
		if(i == 9){
			cout<<i+1<<"|";
		}
		else{
			cout<<i+1<<" |";
		}
		for(int j = 0;j < 10;j++){
			cout<<original[i][j]<<'|';
		}
		cout<<endl;
		cout<<"  |-|-|-|-|-|-|-|-|-|-|"<<endl;
	}
	
	//put random bomb in original array
	randBomb();
	
	//set all data in data array
	infobox();
	
	
	//get box (for loop may change to counter of the sum of choose array (100-10))
	for(int i = 0;i<10;i++){
		cout<<"Please enter a box (row column): "<<endl;
		cin>>row>>column;
		//error check
		if(row < 0||row > 10|| column < 0|| column >10 || choose[row-1][column-1] == 1){
			cout<<"You cannot open this box. ";
			i -= 1;
		}
		else{
			
			choose[row-1][column-1] = openBoard(row-1,column-1);
			
			//if it is a bomb
			if(choose[row-1][column-1] == 888){
				
				//print board with chosen boxes
				cout<<"   ";
				for(int i = 0;i<10;i++){
					cout<<i+1<<" ";
				}
				cout<<endl;
				for(int i = 0;i < 10;i++){
					if(i == 9){
						cout<<i+1<<"|";
					}
					else{
						cout<<i+1<<" |";
					}
					for(int j = 0;j < 10;j++){
						//if it is a bomb
						if(choose[i][j] == 888){
							//show "B"
							cout<<"B"<<'|';
						}
						//if chosen, show data
						else if(choose[i][j] == 1){
							cout<<data[i][j]<<'|';
						}
						//if not yet chosen, show "X"
						else{
							cout<<"X"<<'|';
						}
					}
					cout<<endl;
				}
				
				//tell user that he is lost
				cout<<"BOMB!!!! You lost."<<endl;
//				return 0;
			}
			
			//if it is not a bomb
			else if(choose[row-1][column-1] == 1||choose[row-1][column-1] == 0){
			
				//print board with chosen boxes
				cout<<"   ";
				for(int i = 0;i<10;i++){
					cout<<i+1<<" ";
				}
				cout<<endl;
				for(int i = 0;i < 10;i++){
					if(i == 9){
						cout<<i+1<<"|";
					}
					else{
						cout<<i+1<<" |";
					}
					for(int j = 0;j < 10;j++){
						//if chosen, show the box data
						if(choose[i][j] == 1){
							cout<<data[i][j]<<'|';
						}
						//if not yet chosen, show "X"
						else{
							cout<<"X"<<'|';
						}
					}
					cout<<endl;
				}	
			}
		}
	}
	
/*	cout<<endl<<endl<<endl;
	for(int i = 0;i < 10;i++){
		if(i == 9){
			cout<<i+1<<"|";
		}
		else{
			cout<<i+1<<" |";
		}
		for(int j = 0;j < 10;j++){
			if(data[i][j] == 999){
				cout<<"B"<<'|';
			}
			else{
				cout<<data[i][j]<<'|';
			}
		}
		cout<<endl;
		cout<<"  |-|-|-|-|-|-|-|-|-|-|"<<endl;
	}
*/
	
	return 0;
}



//putting random bomb data in original array
void randBomb(){
	int x,y;
	srand(time(0));
	//store all value in null in original array
	for(int i = 0;i<10;i++){
		for(int j = 0;j<10;j++){
			original[i][j] = 0;
		}
	}
	
	//put random bomb show by 999
	for(int i = 0;i<10;i++){
		x = rand()%10;
		y = rand()%10;
		cout<<x<<" "<<y<<endl;
		if(original[x][y] == 0){
			original[x][y] = 999;
		}
		else{
			i -= 1;
		}
	}
}



//finding the information of surrounding boxes into data array
void infobox(){
	//declare variable for sum of bomb around the box
	int sumb = 0,checkB;
	//set bomb data in data array
	for(int i = 0;i<10;i++){
		for(int j = 0;j<10;j++){
			if(original[i][j] == 999){
				data[i][j] = 999;
			}
		}
	}
	
	//for grid in the middle (1-8,1-8) - without 0 & 9
	for(int i = 1;i<9;i++){
		for(int j = 1;j<9;j++){
			//check if the box have bomb
			if(data[i][j] == 999){
				checkB = 1;
			}
			else{
				checkB = 0;
			}
			
			//if no bomb
			if(checkB == 0){	
				//add up the bomb arond the boxes
				if(original[i-1][j-1] == 999){
					sumb++;
				}
				if(original[i-1][j] == 999){
					sumb++;
				}
				if(original[i-1][j+1] == 999){
					sumb++;
				}
				if(original[i][j-1] == 999){
					sumb++;
				}
				if(original[i][j+1] == 999){
					sumb++;
				}
				if(original[i+1][j-1] == 999){
					sumb++;
				}
				if(original[i+1][j] == 999){
					sumb++;
				}
				if(original[i+1][j+1] == 999){
					sumb++;
				}
			
				data[i][j] = sumb;
				sumb = 0;
			}
		}
	}
	
	//reset sumb counter
	sumb = 0;
	
	
	//for grid on the corner
	//left top corner
	if(original[0][0] != 999){
		if(original[0][1] == 999){
			sumb++;
		}
		if(original[1][0] == 999){
			sumb++;
		}
		if(original[1][1] == 999){
			sumb++;
		}
		data[0][0] = sumb;
		sumb = 0;
	}
	
	//right top corner
	if(original[0][9] != 999){
		if(original[0][8] == 999){
			sumb++;
		}
		if(original[1][9] == 999){
			sumb++;
		}
		if(original[1][8] == 999){
			sumb++;
		}
		data[0][9] = sumb;
		sumb = 0;
	}
	
	//left bottom corner
	if(original[9][0] != 999){
		if(original[9][1] == 999){
			sumb++;
		}
		if(original[8][0] == 999){
			sumb++;
		}
		if(original[8][1] == 999){
			sumb++;
		}
		data[9][0] = sumb;
		sumb = 0;
	}
	
	//right bottom corner
	if(original[9][9] != 999){
		if(original[9][8] == 999){
			sumb++;
		}
		if(original[8][9] == 999){
			sumb++;
		}
		if(original[8][8] == 999){
			sumb++;
		}
		data[9][9] = sumb;
		sumb = 0;
	}
	
	
	//for grid on the edge (upper lower left right)
	//left
	for(int i = 1;i<9;i++){
		//see if the box have bomb
		if(original[i][0] == 999){
			checkB = 1;
		}
		else{
			checkB = 0;
		}
		
		//if no bomb
		if(checkB == 0){
			
			if(original[i-1][0] == 999){
				sumb++;	
			}
			if(original[i-1][1] == 999){
				sumb++;
			}
			if(original[i][1] == 999){
				sumb++;
			}
			if(original[i+1][0] == 999){
				sumb++;
			}
			if(original[i+1][1] == 999){
				sumb++;
			}
		
			data[i][0] = sumb++;
			sumb = 0;
		}
	}
	
	//right
	for(int i = 1;i<9;i++){
		//see if the box have bomb
		if(original[i][9] == 999){
			checkB = 1;
		}
		else{
			checkB = 0;
		}
		
		//if no bomb
		if(checkB == 0){
			if(original[i-1][9] == 999){
				sumb++;	
			}
			if(original[i-1][8] == 999){
				sumb++;
			}
			if(original[i][8] == 999){
				sumb++;
			}
			if(original[i+1][8] == 999){
				sumb++;
			}
			if(original[i+1][9] == 999){
				sumb++;
			}
		
			data[i][9] = sumb++;
			sumb = 0;
		}
	}
	
	//upper
	for(int j = 1;j<9;j++){
		//see if the box have bomb
		if(original[0][j] == 999){
			checkB = 1;
		}
		else{
			checkB = 0;
		}
		
		//if no bomb
		if(checkB == 0){
			if(original[0][j-1] == 999){
				sumb++;	
			}
			if(original[0][j+1] == 999){
				sumb++;
			}
			if(original[1][j-1] == 999){
				sumb++;
			}
			if(original[1][j] == 999){
				sumb++;
			}
			if(original[1][j+1] == 999){
				sumb++;
			}
			
			data[0][j] = sumb++;
			sumb = 0;
		}
	}
	
	//lower
	for(int j = 1;j<9;j++){
		//see if the box have bomb
		if(original[9][j] == 999){
			checkB = 1;
		}
		else{
			checkB = 0;
		}
		
		//if no bomb
		if(checkB == 0){
			if(original[9][j-1] == 999){
				sumb++;	
			}
			if(original[9][j+1] == 999){
				sumb++;
			}
			if(original[8][j-1] == 999){
				sumb++;
			}
			if(original[8][j] == 999){
				sumb++;
			}
			if(original[8][j+1] == 999){
				sumb++;
			}
			
			data[9][j] = sumb++;
			sumb = 0;
		}
	}
}


//open the box and the surronding box according the user entered
int openBoard(int r,int c){
	if(data[r][c] == 999){
		return 888;
	}
	else if(data[r][c] || data[r][c] == 0){
		return 1;
	}
//	else if(data[r][c] == 0){
//		return 0;
//	}
}



