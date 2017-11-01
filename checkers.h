//********************************************************************************************************
//
//	Name: Mackenzie Schnaekel
//	
//	Date: April 10, 2017
//
//	Description: This is the delcaration of the checkers class
//
//********************************************************************************************************

#include<iostream>
#include"space.h"
#include"game.h"

namespace main_savitch_14{

class checkers:public game{

		public:
			checkers();//Constructor
		
			void make_move(const std:: string& move);//Allows the user to input their move
			void display_status()const;//Displays the current status of the board
			bool is_legal(const std::string& move)const;//Determines if the move is legal
		
			int return_int(std::string c)const;
			void restart();//Restarts the board
			bool is_game_over()const;
			bool is_jump_possible()const;
			game* clone()const;
			void compute_moves(std::queue<std::string>& moves)const; 
			int evaluate()const;
			main_savitch_14::game::who winning()const;
			main_savitch_14::game::who last_mover()const;
		private:
			space board[8][8];//The checker board
			int r_counter,b_counter,turn,temp;




};//End checkers
}//End savitch







