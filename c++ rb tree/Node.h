//stuednt Name: Meng Zhao
//student ID: 301173271

#ifndef _Node_

#define _Node_
#include <string>
using namespace std;

template <class T>
class Node{
	public:
		T data;
		Node* left;
		Node* right;
		Node* parent;
		bool isBlack;

		// defined constructor pass data prarmater
		Node(T d): data(d), left(NULL),right(NULL),parent(NULL),isBlack(false){};

		//helper method to print isblack property
		string color(){
			if(isBlack){
				return "Black";
			}
			return "Red";
		 }
	   };

#endif