//stuednt Name: Meng Zhao
//student ID: 301173271

#ifdef _RedBlackTree_
#include "RedBlackTree.h"
#include"Node.h"
#include <iostream> 
#include <string> 
#include<iomanip> 
#include <fstream> 
#include <cstdlib> 
using namespace std;

// Default constructor
// PARAM: 
// PRE:
// POST: Creates an empty RedBlackTree
template <class T>
RedBlackTree<T>::RedBlackTree()
{
    root=NULL;
	n=0;
}

// Destructor
// PARAM:
// PRE:
// POST: Memory associated with RedBlackTree is de-allocated
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	deleteAll();
}


// Copy constructor
// PARAM: rb is the RedBlackTree to be assigned to the calling object
// PRE:
// POST: Creates an object that is a copy of rb
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &rb)
{
	if(rb.root == NULL){
		root = NULL;
		return;
	}

	root=new Node<T>(rb.root->data);
	n=rb.n;
	deepcopy(root,rb.root);
}

// Overloaded assignment operator
// In rb1 = rb2 assigns rb2 to rb1 and returns rb1
// PARAM: rb = list to be assigned to the calling object
// PRE:
// POST: Copies ls to calling object, returns calling object
template <class T>
RedBlackTree<T> & RedBlackTree< T>::operator= (const RedBlackTree<T> & rb)
{
	if(this!=&rb)
	{
		deleteAll();
		if(rb.root == NULL){
		root = NULL;
		return *this ;
	  }

	root=new Node<T>(rb.root->data);
	n=rb.n;
	deepcopy(root,rb.root);

	}
	return *this;
}

// load arr to the redblack tree
// PARAM: arr[] the array to be loaded, size, the size of the array
// PRE:
// POST: empty the redblack tree and load array using insert method
template <class T>
void RedBlackTree<T>::load(T arr[],int size)
{
	deleteAll();
	for(int i=0;i<size;i++)
	{
		insert(arr[i]);
	}
}
// insert data to the redblack tree
// PARAM: d is the data to be insert in the red black tree
// PRE:
// POST: if the data has already in the red black tree return false, otherwise insert the data in the red black tree
// using lecture notes  pseduo code as a reference
template <class T>
bool RedBlackTree<T>::insert(T d)
{
	bool result=(!search(d));
	if(result)
	{
		Node<T>* y;
        Node<T>* x=new Node<T>(d);
		bstInsert(x);

		while(x!=root &&x->parent->isBlack==false)
		{
			if(x->parent==x->parent->parent->left)
			{
				y=x->parent->parent->right;
				if(y!=NULL&&y->isBlack==false)
				{
					x->parent->isBlack=true;
					y->isBlack=true;
					x->parent->parent->isBlack=false;
					x=x->parent->parent;
			     }
				else
				{
					if(x==x->parent->right)
					{
						x=x->parent;
						left_rotate(x);
					}
						x->parent->isBlack=true;
						x->parent->parent->isBlack=false;
						if(x->parent->parent!=NULL)
						  right_rotate(x->parent->parent);
				 }

			  }
			else
			{
				y=x->parent->parent->left;
				if(y!=NULL&&y->isBlack==false)
				{
					x->parent->isBlack=true;
					y->isBlack=true;
					x->parent->parent->isBlack=false;
					x=x->parent->parent;
				}
				else
				{
                       if(x==x->parent->left)
					   {
						   x=x->parent;
						   right_rotate(x);
					   }
					   x->parent->isBlack=true;
					   x->parent->parent->isBlack=false;
					   if(x->parent->parent!=NULL)
					      left_rotate(x->parent->parent);
				}
              
			
			}
	   }
		root->isBlack=true;
	}
	
	return result;
}
// remove to the data redblack tree
// PARAM: d is the data to be remove
// PRE:
// POST: if data is in the redblack tree, return true and delete it, otherwise, return false
//using class notes  pseduo code as a reference
template <class T>
bool RedBlackTree<T>::remove(T d)
{
	if(!search(d))
	    return false;
	Node<T> *z=bstremove(d);
	Node<T>* x=NULL;
	Node<T>* y=NULL;
	
	
    if(root==z&&(root->left==NULL&&root->right==NULL))
	{
		delete root;
		root=NULL;
		n=0;
		return true;
	}

	n--;

	if(z->left==NULL||z->right==NULL)  //one or no children
		y=z;
	else
		y=GetSuccessorOf(z);  //two children

   if((z->left==NULL&&z->right!=NULL)||(z->right==NULL&&z->left!=NULL))
	{
		if(y->left!=NULL)              //identify if y's only child is right or left
		x=y->left;
	else
		x=y->right;

		x->parent=y->parent;

		if(y->parent==NULL)
		root=x;
	else
		if(y==y->parent->left)
			y->parent->left=x;
		else
			y->parent->right=x;

   }
   
   if(z->left==NULL&&z->right==NULL)
   {
	   if(y->parent==NULL)
		  {
			  root=NULL;
			  x=NULL;
	       }

	   if(y==y->parent->left)
		   {
			   x=NULL;
			  y->parent->left=NULL;

	       }
	   else
	   {
		   x=NULL;
		   y->parent->right=NULL;
	   }
   }

	if(y!=z)
	{
		z->data=y->data;
		if(y->right=NULL)
		{
			if(y==y->parent->left)
		      y->parent->left=NULL;
	       else
		   y->parent->right=NULL;

			x=NULL;
		}
		else
		{
			x=y->right;
			if(y==y->parent->left)
		      y->parent->left=y->right;
	       else
		   y->parent->right=y->right;
		}
	}
	

	if(y->isBlack&&x!=NULL)
		rbDeleteFixUp(x); // fix the red black tree

	

	
	delete y;
	
	return true;
}

// search the data in the red black tree
// PARAM: d is the data to be search
// PRE:
// POST: if data is in the redblack tree, return true , otherwise, return false
//using class notes  pseduo code as a reference
template <class T>
bool RedBlackTree<T>::search(T d) const
{
	return recursiveSearch(d,root);
	
}

// search to the datas between two values in redblack tree
// PARAM: d1 is beginning data, d2 is the ending data, number is the size of the return array 
// PRE:
// POST: return an array pointer contains the first element address searched between d1 and d2.

template <class T>
T* RedBlackTree<T>::search(T d1,T d2,int& number)const
{
	number=0;
    inordersreachindex(root,number,d1,d2);
	T* arr=new T[number];
	int b=0;
	inordersreach(root,b,arr,d1, d2);
	return arr ;
}
// delete verything in the tree;
// PARAM: 
// PRE:
// POST: empties the tree, de-allocates dynamic memory allocated by the tree 
template <class T>
void RedBlackTree<T>::deleteAll()
{
	destroy(root);
	n=0;
}

// return the array contains all of the elements in red black tree
// PARAM:  a , the size of the array
// PRE:
// POST: returns a pointer to an array in dynamic memory that contains all of the values in the tree; the contents of the array are in ascending order;
template <class T>
T* RedBlackTree<T>::dump(int& a)const
{
   T* arr=new T[n];
   a=0;
   inorderheper(root, a, arr);
	return arr;
}

// size of the red black tree
// PARAM: 
// PRE:
// POST: return the returns the number of items in the tree
template <class T>
int RedBlackTree<T>::size() const
{
	return n;
}

// height of the red black tree
// PARAM: 
// PRE:
// POST:  returns the height of the tree ¨C the length of the longest path from the root to a leaf, where leaves are null children; that is the height of the tree should equal the number of levels of internal (real) nodes; 
template <class T>
int RedBlackTree<T>::height() const
{
	return rbtheight(root);
	
}

//  black height of the red black tree
// PARAM: 
// PRE:
// POST:  returns the black height of the tree ¨C the number of black nodes on the path from the root to the null leaves, not including the root itself; 
template <class T>
int RedBlackTree<T>::b_height() const
{
	Node<T>* temp=root;
	int bhight=0;
	while(temp!=NULL)
	{
		if(temp->isBlack)
			bhight++;
		temp=temp->left;
	}
	return bhight;
}
// Checks that the rb tree is valid with respect to its red property

// PRE:

// PARAM:

// POST: Returns true iff there are no red nodes with red children

template <class T>

bool RedBlackTree<T>::redCheck() const

{

      bool result = true;

      redProperty(root, result);

      return result;

} 

 

// Performs a post-order traversal checking the rb red property

// PRE:

// PARAM: nd - the node to be tested

//        ok - reference parameter that records result

// POST: Returns true iff there are no red nodes with red children

template <class T>

void RedBlackTree<T>::redProperty(Node<T>* nd, bool & ok) const

{

      if(nd != NULL){

            redProperty(nd->left, ok);

            redProperty(nd->right, ok);

            if(nd != root && (!nd->isBlack && !nd->parent->isBlack)){

                  ok = false;

            }

      }

}

// PARAM: d, data to be searched. nd  the node to be be searched
// PRE:
// POST: helper function recursively to build search function
// using lecture notes pseudo code as a reference
template <class T>
bool RedBlackTree<T>::recursiveSearch(T d,Node<T>* nd) const
{
	if (nd == NULL){ 
		return false;
	}else if(d == nd->data){ 
		return true; 
	} else if (d < nd->data){
		return recursiveSearch(d, nd->left); 
	} else { 
		return recursiveSearch(d, nd->right);
	}
}

// PARAM:  x , new nodes to be insert in binary search tree
// PRE:
// POST: helper method to build red black tree insert
template <class T>
void RedBlackTree<T>::bstInsert(Node<T>* x)
{
	
	Node<T>* temp=root;
	Node<T>* temp2=root;
	if(root==NULL)
		root=x;
	else
 {

	while(temp!=NULL)
	{
		temp2=temp;
		if(x->data<temp->data)
			temp=temp->left;
		else
			temp=temp->right;
	}
	x->parent=temp2;
	if(x->data<temp2->data)
		temp2->left=x;
	else
		temp2->right=x;

 }
	n++;

}
// PARAM: 
// PRE:
// POST: print function , print the elements in preorder
template <class T>
void RedBlackTree<T>::print() const
{
	
	preorderTraversal(root);
}

// PARAM: nd, node to be traversal
// PRE:
// POST: helper method to build print
// using letcure notes pseudo code as a reference
template <class T>
void RedBlackTree<T>::preorderTraversal(Node<T>* nd) const
{
	if (nd != NULL) {
		cout<<nd->data<<endl;
    preorderTraversal(nd->left);
    preorderTraversal(nd->right);
	
    }

}
// PARAM: x , node to nbe left rotate
// PRE:
// POST: rotate the node x. helper function to build insert and remove fixup methods.
// using lecture notes pseudo code as a reference
template <class T>
void RedBlackTree<T>::left_rotate(Node<T>* x)
{
    Node<T>* y=NULL;
	y=x->right;
	 x->right=y->left;
	  if (y->left != NULL) 
		  y->left->parent=x;
	    y->parent=x->parent; 
		if(x->parent==NULL)
			root=y;

		else  if( x == x->parent->left) {
            x->parent->left=y;
            }
	          else {
             x->parent->right=y;
            }
         y->left=x;
         x->parent=y;

}

// PARAM: y , node to nbe right rotate
// PRE:
// POST: rotate the node y. helper function to build insert and remove fixup methods.
// using lecture notes pseudo code as a reference
template <class T>
void RedBlackTree<T>::right_rotate(Node<T>* y)
{
    Node<T>* x=NULL;
	x=y->left;
     y->left=x->right;

     if ( x->right!=NULL)  
	     x->right->parent=y; 
	  x->parent=y->parent;

	  if(y->parent==NULL)
			root=x;

	  else   if( y == y->parent->left) {
                y->parent->left=x;
              }
	         else {
                y->parent->right=x;
             }
       x->right=y;
       y->parent=x;

}
// PARAM: nd, node to be delete
// PRE:
// POST: helper method to build delete all.
// using lecture notes pseudo code as a reference
template <class T>
void RedBlackTree<T>:: destroy(Node<T>* nd)
{
	if(nd!=NULL){
		destroy(nd->left);
		destroy(nd->right);
		delete nd;
	}
	root=NULL;
}
// PARAM: nd, node will copy the rb notes data
// PRE:
// POST: helper method to build copy constructor
// using lecture notes pseudo code as a reference
template <class T>
void RedBlackTree<T>::deepcopy(Node<T>* nd,Node<T>* rb)
{
	if(rb!=NULL)
  {
	  
	nd->data=rb->data;
	nd->isBlack=rb->isBlack;

	if(rb->left != NULL){
		nd->left=new Node<T>(rb->left->data);
		nd->left->isBlack=rb->left->isBlack;
		nd->left->parent=nd;
		deepcopy( nd->left, rb->left);
	}else{
		nd->left = NULL;
	}

   if(rb->right!=NULL){

	nd->right=new Node<T>(rb->right->data);
	
	nd->right->isBlack=rb->right->isBlack;
	nd->right->parent=nd;
	
	deepcopy( nd->right, rb->right);
   }
   else{
	   nd->right=NULL;
   }
  }
}

// debug print
// PARAM: 
// PRE:
// POST: print the address , colur , data in the red black tree to debug
template <class T>
void RedBlackTree<T>::debugPrint() const {
	debugPrint(root);
	cout<<n<<endl;
	cout<<root->data<<endl;
}

// PARAM: node, node to traversal to be print
// PRE:
// POST: helper method for debugprint
template <class T>
void RedBlackTree<T>::debugPrint(Node<T>* node) const{
	if(node == NULL){
		return;
	}
	cout<<"Node ="<<node<< " item = "<<node->data<<
		" " << node->color()<<endl;
	cout<<"\t left = "<<node->left<<endl;
	cout<<"\t right = "<<node->right<<endl;

	debugPrint(node->left);
	debugPrint(node->right);
}

// in order traversal
// PARAM: nd , the node to search the data, a, size of the array. arr the pointer to the array
// PRE:
// POST: fill up the elements to the array . helper method to build dump
template <class T>
void RedBlackTree<T>::inorderheper(Node<T>* nd,int& a, T* arr) const
{
	if(nd!=NULL){
	inorderheper(nd->left,a,  arr);
	  arr[a]=nd->data;
	  a++;
	inorderheper(nd->right, a, arr);
	}
}

// inordersreachindex
// PARAM:  nd, the node to traversal. a , the size of the array. d1, the begining value, d2, the ending value
// PRE:
// POST: get the size of the new array. helper method to build search(value, vaule, int&)
template <class T>
void RedBlackTree<T>::inordersreachindex(Node<T>* nd,int& a,T d1,T d2) const
{
	if(nd!=NULL){
	inordersreachindex(nd->left, a,d1,d2);
	if(nd->data>=d1&&nd->data<=d2)
		a++;
	  
	inordersreachindex(nd->right,a,d1,d2);
	}
}

// inordersreach
// PARAM:  nd, the node to traversal. a , the size of the array. d1, the begining value, d2, the ending value
// PRE:
// POST: fill up the array. helper method to build search(value, vaule, int&)
template <class T>
void RedBlackTree<T>::inordersreach(Node<T>* nd,int& a, T* arr,T d1,T d2) const
{
	if(nd!=NULL){
	inordersreach(nd->left, a,arr,d1,d2);
	if(nd->data>=d1&&nd->data<=d2)
		{
			arr[a]=nd->data;
			a++;
	    }
	  
	inordersreach(nd->right,a,arr,d1,d2);
	}
}


// PARAM:  nd, the node to traversal. 
// PRE:
// POST: helper method to build red black tree height
template <class T>
int RedBlackTree<T>::rbtheight(Node<T>* nd) const
{
	int l=0;
	int r=0;
	if(nd==NULL)
		return 0;
	else
	{
		l=rbtheight(nd->left);
		r=rbtheight(nd->right);
		if(l>r||l==r)
			return (l+1);
		else
			return(r+1);
	}
}
// PARAM:  x, the node to pass and search for successor
// PRE:
// POST: return new node which is the successor of the x . helper method to build remove
// using lecture notes as reference
template <class T>
Node<T>* RedBlackTree<T>::GetSuccessorOf(Node<T> * x) const
{
	Node<T>* y;
	if((y = x->right)!=NULL)
	{
		while(y->left!=NULL)
		{
			y=y->left;
		}
		return y;
	}
	else{
		y=x->parent;
		while(x==y->right&&y!=NULL)
		{
			x=y;
			y=y->parent;
		}
		if(y==root)
			return NULL;
		return y;
     }
}

// PARAM: x, the data to be remove in the red black tree
// PRE:
// POST: search for the node which contains the data x. helper method to build remove
template <class T>
Node<T>* RedBlackTree<T>::bstremove(T x) const
{
     Node<T>* temp=root;
	
	if(root->data==x)
		return temp;
	else
 {

	while(temp!=NULL)
	{
		
		if(x<temp->data)
			temp=temp->left;
		else if(x>temp->data)
			temp=temp->right;
		    else
				return temp;
	}
	return temp;
	

 }

}

// PARAM:  x, node to pass to fix the tree
// PRE:
// POST: maintain the black property in the red black tree. helper method to build remove
// using the lecture notes pseudo code as a reference
template <class T>
void RedBlackTree<T>::rbDeleteFixUp(Node<T>* x)
{
	Node<T>* w=  NULL;
 
	while(x!=root&&x->isBlack==true)
	{
        if(x==x->parent->left)
		{
			w=x->parent->right;
			if(w!=NULL&&w->isBlack==false)
			{
				w->isBlack=true;
				w->parent->isBlack=false;
				left_rotate(x->parent);
				w=x->parent->right;
			}
			 
			if((w->left!=NULL&&w->right!=NULL)&&(w->left->isBlack==true&&w->right->isBlack==true))
			{
				w->isBlack=false;
				x=x->parent;
			}
			else
			{
			 if((w->right!=NULL)&&w->right->isBlack==true)
			{
				if(w->left!=NULL)
				    w->left->isBlack=true;

				w->isBlack=false;
				right_rotate(w);
				w=x->parent->right;
			}
			w->isBlack=x->parent->isBlack;
			x->parent->isBlack=true;

			if(w->right!=NULL)
			    w->right->isBlack=true;

			left_rotate(x->parent);
			x=root;
			}
		}
		else
		{
          w=x->parent->left;
		  if(w!=NULL&&w->isBlack==false)
		  {
			  w->isBlack=true;
			  w->parent->isBlack=false;
			  right_rotate(x->parent);
			   w=x->parent->left;
		  }
		 
		  if(w!=NULL&&(w->left!=NULL&&w->right!=NULL)&&(w->right->isBlack==true&&w->left->isBlack==true))
		  {
			  w->isBlack=false;
			  x=x->parent;
		  }
		  else
		  {
			  if(w!=NULL&&(w->left!=NULL)&&w->left->isBlack==true)
		    {
				if(w->right!=NULL)
			       w->right->isBlack=true;

			  w->isBlack=false;
			  left_rotate(w);
			  w=x->parent->left;
		     }

			  if(w!=NULL)
			  w->isBlack=x->parent->isBlack;

		       x->parent->isBlack=true;

			if(w!=NULL&&w->left!=NULL)
		        w->left->isBlack=true;

		     right_rotate(x->parent);
		     x=root;
		   
		  }
		}
	}
	x->isBlack=true;
}

#endif