//*************************************************************
//	
//	Name: Mackenzie Schnaekel
//
//	Date: April 10, 2017
//
//	Description: This is the space class declaration file
//
//*************************************************************

#ifndef SPACE_H
#define SPACE_H
#include<iostream>

class space{
		public:
			space();

			void make_empty();
			bool is_empty()const;
			void make_magenta();
			bool is_magenta()const;
			void make_green();
			bool is_green()const;
			void magenta_king_me();
			void green_king_me();
			bool is_king()const;

		private:
			bool magenta,green,king,empty;
			

};




#endif
