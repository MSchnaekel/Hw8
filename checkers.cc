
//******************************************************************************************
//
//	Name: Mackenzie Schnaekel
//
//	Date: April 10, 2017
//
//	Description: This is the implementation of the checkers class.
//
//******************************************************************************************

//NOTE: RED IS MAGENTA AND BLACK IS GREEN

#include<iostream>
#include"checkers.h"
#include"colors.h"
#include<string>
#include<iomanip>
#include<algorithm>
#include<sstream>
using namespace std;
namespace main_savitch_14{

checkers::checkers()
{
	for(int i=0; i <8 ; i++)
	{
		for(int d=0; d <8 ; d++)
		{
			board[i][d].make_empty();
		}
	}
	r_counter = 12;
	b_counter = 12;
	turn = 0;
}
		
void checkers::make_move(const string& move)
{
	string start,moving;

	start = move.substr(0,1); //Pulls apart the string move to make the starting piece (start) and the desired location (moving)
	
	moving = move.substr(3,4);
	moving = moving.substr(0,1);

	transform(start.begin(),start.end(),start.begin(),::toupper); //Makes the starting letter uppercase
	transform(moving.begin(),moving.end(),moving.begin(),::toupper); //Makes the moving letter uppercase

	int column1 = return_int(start); //Changes string to int (could not come up with an easier way
	int column2 = return_int(moving); //Changes string to int	

	int row1 = atoi(move.substr(1,2).c_str())-1; //Converts the starting number to int
	int row2 = atoi(move.substr(4,5).c_str())-1; //Converts the moving number to int
	
	

	if(!is_jump_possible()) //Checks to see if a jump is available
	{
		if(board[row1][column1].is_green() == true)//Is the piece green
		{		

			if(board[row1][column1].is_king())//Moves a king
			{
				board[row2][column2].green_king_me();
			}
			else//Normal move
			{
				board[row2][column2].make_green();
			}
			board[row1][column1].make_empty();
			turn++;	
			if(row2 == 0)//Allows the player to be a king, aka kings spot
			{
				board[row2][column2].green_king_me();
			}
		
		}
		else if(board[row1][column1].is_magenta() == true)//Is the piece magenta, the code is the same except for the kings spot
		{
			board[row2][column2].make_magenta();
			if(board[row1][column1].is_king())
			{
				board[row2][column2].magenta_king_me();
			}
			board[row1][column1].make_empty();
			turn++;		
			if(row2 == 7)
			{
				board[row2][column2].magenta_king_me();
			}
		}
	}
	else
	{
			
		if(last_mover() == COMPUTER)
		{
			if(board[row1][column1].is_green())
			{
				if(board[row1][column1].is_king()==true)
				{
					board[row2][column2].green_king_me();
					board[row1][column1].make_empty();
					if((column1 < column2)&&(row1 < row2))
					{
						board[row1+1][column1+1].make_empty();
					}
					else if((column1 < column2)&&(row1 > row2))
					{
						board[row1-1][column1+1].make_empty();
					}
					else if((column1 > column2)&&(row1 > row2))
					{
						board[row1-1][column1-1].make_empty();	
					}
					else if((column1 > column2)&&(row1 < row2))
					{
						board[row1+1][column1-1].make_empty();
					}
				}
				else
				{
					board[row2][column2].make_green();
					board[row1][column1].make_empty();	
					if(column1 < column2)
					{	
						board[row2+1][column2-1].make_empty();//Jump forward right
					}
					else
					{
						board[row2+1][column2+1].make_empty();//Jump forward left	
					}
					if(row2 == 0)//Allows the player to be a king, aka kings spot	
					{
						board[row2][column2].green_king_me();
					}
				}
				if(is_jump_possible() == false)//Checks if the user can jump again. Will stay on their turn.
				{
					turn++;	
				}
					r_counter--;//Lowers magenta chips
			}
	
			else if(board[row1][column1].is_magenta())
			{
				if(board[row1][column1].is_king()==true)
				{
					board[row2][column2].magenta_king_me();
					board[row1][column1].make_empty();
					if((column1 < column2)&&(row1 < row2))
					{
						board[row1+1][column1+1].make_empty();
					}
					else if((column1 < column2)&&(row1 > row2))
					{
						board[row1-1][column1+1].make_empty();
					}
					else if((column1 > column2)&&(row1 > row2))
					{
							board[row1-1][column1-1].make_empty();	
					}
					else if((column1 > column2)&&(row1 < row2))
					{
						board[row1+1][column1-1].make_empty();
					}
				}
				else
				{
					board[row2][column2].make_magenta();	
					if(column1 >  column2)
					{
						board[row2-1][column2+1].make_empty();//Jump down left	
					}
					else
					{
						board[row2-1][column2-1].make_empty();//Jump down right	
					}
				}
				if(is_jump_possible() == false)//Checks if the user can jump again. Will stay on their turn.
				{
					turn++;	
				}
				board[row1][column1].make_empty();
				if(row2 == 0)//Allows the player to be a king, aka kings spot
				{
					board[row2][column2].green_king_me();
				}
				b_counter--;//Lowers green chips
			}//End else if
	}//End computer
	else//HUMAN
	{
	
		if(board[row1][column1].is_green())
			{
				if(board[row1][column1].is_king()==true)
				{
					
					board[row2][column2].green_king_me();
					board[row1][column1].make_empty();
					if((column1 < column2)&&(row1 < row2))
					{
						board[row1+1][column1+1].make_empty();
					}
					else if((column1 < column2)&&(row1 > row2))
					{
						board[row1-1][column1+1].make_empty();
					}
					else if((column1 > column2)&&(row1 > row2))
					{
						board[row1-1][column1-1].make_empty();	
					}
					else if((column1 > column2)&&(row1 < row2))
					{
						board[row1+1][column1-1].make_empty();
					}
				}
				else
				{
					
					board[row2][column2].make_green();
					board[row1][column1].make_empty();	
					if(column1 < column2)
					{	
						board[row2+1][column2-1].make_empty();//Jump forward right
					}
					else
					{
						board[row2+1][column2+1].make_empty();//Jump forward left	
					}
					if(row2 == 0)//Allows the player to be a king, aka kings spot	
					{
						board[row2][column2].green_king_me();
					}
				}
				if(last_mover() == HUMAN)
				{
					turn++;
					
				}
				r_counter--;//Lowers magenta chips
			
			}
	
			else if(board[row1][column1].is_magenta())
			{
				
				if(board[row1][column1].is_king()==true)
				{
					
					board[row2][column2].magenta_king_me();
					board[row1][column1].make_empty();
					if((column1 < column2)&&(row1 < row2))
					{
						board[row1+1][column1+1].make_empty();
					}
					else if((column1 < column2)&&(row1 > row2))
					{
						board[row1-1][column1+1].make_empty();
					}
					else if((column1 > column2)&&(row1 > row2))
					{
						board[row1-1][column1-1].make_empty();	
					}
					else if((column1 > column2)&&(row1 < row2))
					{
						board[row1+1][column1-1].make_empty();
					}
				}
				else
				{
					
					board[row2][column2].make_magenta();	
					if(column1 >  column2)
					{
						board[row2-1][column2+1].make_empty();//Jump down left	
					}
					else
					{
						board[row2-1][column2-1].make_empty();//Jump down right	
					}
				}
				
				board[row1][column1].make_empty();
				if(row2 == 7)//Allows the player to be a king, aka kings spot
				{
					board[row2][column2].magenta_king_me();
				}
				if(last_mover() == HUMAN)
				{
					turn++;
					
				}
				b_counter--;//Lowers green chips
			}
				
			
		}//End HUMAN
	}//End else



}//End function

void checkers::display_status()const//Sets up the current status of the board with background color
{
	char letter = 'A';
		
		cout<<endl<<BLUE<<setw(3)<<letter; 
		letter++;
		for(int i=0; i < 7; i++)
		{
			cout<<setw(5)<<letter;
			letter++;
		}
		cout<<endl;
	
		for(int i=0; i < 8 ; i++)
		{
			

			if(i%2 == 0)//Checks if row is even or odd
			{
				for(int d=0; d < 8 ; d++)
				{
					if(d%2 == 0)//Checks to see if column is even or odd
					{
						if((board[i][d].is_king()==false))//Is there a "red" piece
						{
						
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
							cout<<B_BLACK<<GREEN<<"  O  "<<RESET;
							}
							else if((board[i][d].is_magenta() == true))
							{
								cout<<B_BLACK<<MAGENTA<<"  O  "<<RESET;
							}
							else
							{
								cout<<B_BLACK<<"     "<<RESET;
							}
						}
						else
						{
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
							cout<<B_BLACK<<GREEN<<"  @  "<<RESET;
							}
							else
							{
								cout<<B_BLACK<<MAGENTA<<"  @  "<<RESET;
							}
						}
					}
					else
					{
						if((board[i][d].is_king()==false))//Is there a "red" piece
						{
						
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
								cout<<B_RED<<GREEN<<"  O  "<<RESET;
							}
							else if((board[i][d].is_magenta() == true))
							{
								cout<<B_RED<<MAGENTA<<"  O  "<<RESET;
							}
							else
							{
								cout<<B_RED<<"     "<<RESET;
							}
						}
						else
						{
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
							cout<<B_RED<<GREEN<<"  @  "<<RESET;
							}
							else
							{
								cout<<B_RED<<MAGENTA<<"  @  "<<RESET;
							}
						}
					}//End else
				}//End for
			}//End if
			else//For odd rows
			{
				for(int d=0; d < 8 ; d++)
				{
					if(d%2 == 0)
					{
						if((board[i][d].is_king()==false))//Is there a "red" piece
						{
						
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
							cout<<B_RED<<GREEN<<"  O  "<<RESET;
							}
							else if((board[i][d].is_magenta() == true))
							{
								cout<<B_RED<<MAGENTA<<"  O  "<<RESET;
							}
							else
							{
								cout<<B_RED<<"     "<<RESET;
							}
						}
						else
						{
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
							cout<<B_RED<<GREEN<<"  @  "<<RESET;
							}
							else
							{
								cout<<B_RED<<MAGENTA<<"  @  "<<RESET;
							}
						}	
					}//End if
					else
					{
						if((board[i][d].is_king()==false))//Is there a "red" piece
						{
						
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
								cout<<B_BLACK<<GREEN<<"  O  "<<RESET;
							}
							else if((board[i][d].is_magenta() == true))
							{
								cout<<B_BLACK<<MAGENTA<<"  O  "<<RESET;
							}
							else
							{
								cout<<B_BLACK<<"     "<<RESET;
							}
						}
						else
						{
							if((board[i][d].is_green() == true))//Is there a "black" piece
							{
							cout<<B_BLACK<<GREEN<<"  @  "<<RESET;
							}
							else
							{
								cout<<B_BLACK<<MAGENTA<<"  @  "<<RESET;
							}
						}
				
					}//End if
				}//End for
			}//End else
			

			cout<<" "<<BLUE<<i+1<<endl<<RESET;
		}//End for
	if(turn%2 ==0)
	{
		cout<<"Player one's turn: \n";
	}
	else
	{
		cout<<"Player two's turn: \n";
	}
	if(is_jump_possible())
	{
		cout<<"!!!YOU HAVE A JUMP!!!\n";
	}
	
}//End display

bool checkers::is_legal(const string& move)const
{

	if(move.find(",") > 3)//Makes sure the input is correct
	{
		cout<<"Please enter the correct format.\n";
		return false;
	}
	else if(move.length() < 5)//Makes sure the input is correct
	{
		cout<<"Please enter the correct format.\n";
		return false;
	}

	string start,moving;

	start = move.substr(0,1);// Row string

	moving = move.substr(3,4);
	moving = moving.substr(0,1);// Row string

	transform(start.begin(),start.end(),start.begin(),::toupper); //Start to upper
	transform(moving.begin(),moving.end(),moving.begin(),::toupper); //Moving to upper

	int row1 = atoi(move.substr(1,2).c_str())-1;//int starting row
	int row2= atoi(move.substr(4,5).c_str())-1;//int starting column	
	int column1 = return_int(start);//int moving row
	int column2 = return_int(moving);//int moving column	

	

	if(!is_jump_possible())
	{	
		if(board[row1][column1].is_king())//Legal king moves
		{
			if(((column1 - column2 ==1)||(column1 - column2 == -1))&&(board[row2][column2].is_empty()==true)&&((row1 == row2+1)||(row1 == row2-1)))
			{
				return true;	
			}
			else
			{
				return false;
			}
		}		
			
		else if(board[row1][column1].is_green() == true)//Legal green moves
		{
			if(((column1 - column2 == 1)||(column1 - column2 == -1))&&(row1 == row2+1)&&(board[row1][column1].is_empty()==false)&&(board[row2][column2].is_empty()==true)&&(turn%2 ==0))//Makes sure the move is legal
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(board[row1][column1].is_magenta() == true)//Legal magenta moves
		{
			if(((column1 - column2 == -1)||(column1 - column2 == 1))&&(row1 == row2-1)&&(board[row1][column1].is_empty()==false)&&(board[row2][column2].is_empty()==true)&&(turn%2 != 0))//Makes sure the move is legal
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	
	}
	else //Jump possible
	{
		if(board[row1][column1].is_king())//Legal king jump moves
		{
			if(((column1 - column2 == 2)||(column1-column2 == -2))&&(board[row2][column2].is_empty() == true)&&((row1+2 == row2)||(row1-2 == row2)))
			{
				return true;
			}
			else 
			{
				return false;
			}
		}		
		else if(board[row1][column1].is_green())//Legal green jumps
		{	
			if(((column1 - column2 == 2)||(column1 - column2 == -2))&&(row1-2 == row2)&&(board[row2][column2].is_empty()==true))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(board[row1][column1].is_magenta())//Legal magenta jumps
		{
			if(((column1 - column2 == 2)||(column1 - column2 == -2))&&(board[row2][column2].is_empty()==true)&&(row1+2 == row2))
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
	}

}//End move
void checkers::restart()
{
	for(int i=0; i <3 ; i++)//Sets up the top half of the board
	{
		for(int d=0; d <8 ; d++)
		{
			if((d%2 == 0)&&(i%2 == 0))
			{
				board[i][d].make_magenta();	
			}
			else if((d%2 != 0)&&(i%2 != 0))
			{
				board[i][d].make_magenta();
			}
			else
			{
				board[i][d].make_empty();
			}
		}
	}
	for(int i= 3; i <4; i++)//Sets up the middle of the board
	{
		for(int d=0; d < 8; d++)
		{
			board[i][d].make_empty();
		}
	}
	for(int i=5; i <8 ; i++)//Sets up the bottom half of the board
	{
		for(int d=0; d < 8 ; d++)
		{
			if((d%2 == 0)&&(i%2 == 0))
			{
				board[i][d].make_green();
			}
			else if((d%2 != 0)&&(i%2 != 0))
			{
				board[i][d].make_green();
			}
			else
			{
				board[i][d].make_empty();
			}
		}
	}
}

bool checkers::is_game_over()const
{
	if(r_counter == 0) 
	{
		cout<<"!!!PLAYER ONE HAS WON!!!\n";
		return true;
	}
	else if(b_counter == 0)
	{
		cout<<"!!!PLAYER TWO HAS WON!!!\n";
		return true;
	}
	else
	{
		return false;
	}
}//End is_game_over

bool checkers::is_jump_possible(/*const string& move*/)const //This function reads the whole board to determine if there is a jump possible for each player
{
	

	for(int i=0; i < 8; i++)
	{
		for(int d=0; d < 8; d++)
		{
			if(turn%2 ==0)
			{
				if(board[i][d].is_green())
				{
					if(board[i][d].is_king())
					{
						if((board[i-1][d-1].is_magenta())&&(board[i-2][d-2].is_empty())&&(d-2>=0))
						{
							return true;
						}
						else if((board[i-1][d+1].is_magenta())&&(board[i-2][d+2].is_empty())&&(d+2<=7))
						{
							return true;
						}
						else if((board[i+1][d+1].is_magenta())&&(board[i+2][d+2].is_empty())&&(d+2<=7))
						{
							return true;
						}
						else if((board[i+1][d-1].is_magenta())&&(board[i+2][d-2].is_empty())&&(d-2>=0))
						{
							return true;
						}
						else
						{
							return false;
						}	
						
					}	
					else
					{
						if((board[i-1][d-1].is_magenta())&&(board[i-2][d-2].is_empty())&&(d-2>=0))
						{
							return true;		
						}
						else if((board[i-1][d+1].is_magenta())&&(board[i-2][d+2].is_empty())&&(d+2<=7))	
						{	
							return true;
						}
						else if(((board[i-1][d-1].is_magenta())&&(board[i-2][d-2].is_empty())&&(d-1>=0))&&((board[i-1][d+1].is_magenta())&&(board[i-2][d+2].is_empty())&&(d+2<=7)&&(d-2>=0)))
						{
							return true;
						}
					}
				}
					
				
			}
			else
			{	
						
				if(board[i][d].is_magenta())
				{	
					if(board[i][d].is_king())
					{
						
						if((board[i-1][d-1].is_green())&&(board[i-2][d-2].is_empty())&&(d-2>=0))
						{
							return true;
						}
						else if((board[i-1][d+1].is_green())&&(board[i-2][d+2].is_empty())&&(d+2<=7))
						{
							return true;
						}
						else if((board[i+1][d+1].is_green())&&(board[i+2][d+2].is_empty())&&(d+2<=7))
						{
							return true;
						}
						else if((board[i+1][d-1].is_green())&&(board[i+2][d-2].is_empty())&&(d-2>=0))
						{
							return true;
						}
						else
						{
							return false;
						}	
					}
					else
					{
						if((board[i+1][d+1].is_green())&&(board[i+2][d+2].is_empty())&&(d+2<=7))
						{
							return true;
						}
						else if((board[i+1][d-1].is_green())&&(board[i+2][d-2].is_empty())&&(d-2>=0))		
						{
							return true;
						}
						
					} 
			}	}
		}	
	}	

}


game* checkers::clone()const
{
	return new checkers(*this);
}

void checkers::compute_moves(queue<string>& moves) const
{
	string temp ="     ";
	char i,j,k,l;
	for(i = 'A'; i < 'I'; i++)
	{
		for(j = '1'; j < '9'; j++)
		{
			for(k = 'A'; k < 'I'; k++)	
			{
				for(l = '1'; l < '9'; l++)
				{
					temp[0] = i;
					temp[1] = j;
					temp[2] = ',';
					temp[3] = k;
					temp[4] = l;
					int column1 = int(tolower(i) -'a');
					int row1 = int(tolower(j) - '1');
					int column2 = int(tolower(k) -'a');
					int row2 = int(tolower(l) - '1');
					if(board[row1][column1].is_magenta() == true&& last_mover() == HUMAN)//Legal magenta moves
					{
						if(is_legal(temp)&&(board[row1][column1].is_king()))
						{						
							moves.push(temp);
						}
						else if(is_legal(temp)&&!is_jump_possible())
						{
							moves.push(temp);
						}
						else if(is_legal(temp)&&is_jump_possible())
						{
							if(is_legal(temp)&&(column1 - column2 == 2)&&(row1+2 == row2)&&(board[row2][column2].is_empty())&&(board[row1+1][column1-1].is_green()))
							{
								
								moves.push(temp);
							}
							else if(is_legal(temp)&&(column1 - column2 == -2)&&(row1+2 == row2)&&(board[row2][column2].is_empty())&&(board[row1+1][column1+1].is_green()))
							{
								moves.push(temp);	
							}
			
						}
					}
							
										
					else if(board[row1][column1].is_green() == true&& last_mover() == COMPUTER)
					{	
						if(is_legal(temp)&&(board[row1][column1].is_king()))
						{						
							moves.push(temp);
						}
						else if(is_legal(temp)&&!is_jump_possible())
						{
							moves.push(temp);
						}
						else if(is_legal(temp)&&is_jump_possible())
						{
							if(is_legal(temp)&&(column1 - column2 == 2)&&(row1+2 == row2)&&(board[row2][column2].is_empty())&&(board[row1-1][column1-1].is_green()))
							{
								
								moves.push(temp);
							}
							else if(is_legal(temp)&&(column1 - column2 == -2)&&(row1+2 == row2)&&(board[row2][column2].is_empty())&&(board[row1-1][column1+1].is_green()))
							{
								moves.push(temp);	
							}
			
						}	
						
						/*if(is_legal(temp)&&!is_jump_possible())
						{
							moves.push(temp);
						}
						else if(is_legal(temp)&&!is_jump_possible())
						{
							moves.push(temp);
						}*/


					}
				}
	
			}
		}
	}
	
			
	
}

main_savitch_14::game::who checkers::last_mover()const
{
	if(turn%2 == 0)
	{
		return COMPUTER;
	}
	else
	{
		return HUMAN;
	}
}

int checkers::evaluate()const
{
	int total_m=0,total_g=0;
	for(int i=0; i < 8; i++)
	{
		for(int d=0; d < 8; d++)
		{
			if(board[i][d].is_magenta() == true)
			{
				if(board[i][d].is_king()  == true)
				{
					total_m+=3;
				}
				else
				{
					total_m++;
				}
			}
			else if(board[i][d].is_green() == true)
			{
				if(board[i][d].is_king() == true)
				{
					total_g+=3;		
				}
				else
				{
					total_g++;
				}
			}	
		}
	}
	return total_m-total_g;
}

main_savitch_14::game::who checkers::winning()const
{
	int total_m=0,total_g=0;
	for(int i=0; i < 8; i++)
	{
		for(int d=0; d < 8; d++)
		{
			if(board[i][d].is_magenta() == true)
			{
				total_m++;	
			}
			else if(board[i][d].is_green() == true)
			{
				total_g++;
			}
		}//End second for loop
	}//End first for loop
	if(total_m > total_g)
	{
		return COMPUTER;
	}
	else
	{
		return HUMAN;
	}

}



int checkers::return_int(string c)const//I could not get the string letter to int so I added an extra function to do so easily. I hope this is not an issue, i tried making an int[] of move but it would not work.
{
	if(c == "A")
	{
		return 0;
	}
	else if(c == "B")
	{
		return 1;
	}
	else if(c == "C")
	{
		return 2;
	}
	else if(c == "D")
	{
		return 3;
	}
	else if(c == "E")
	{
		return 4;
	}
	else if(c == "F")
	{
		return 5;
	}
	else if(c == "G")
	{
		return 6;
	}
	else if(c == "H")
	{
		return 7;
	}
}

}//End savitch

