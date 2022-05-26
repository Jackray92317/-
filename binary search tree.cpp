# include <stdio.h>
# include <string.h>
# include <iostream>

using namespace std ;

struct Node {
	int data ;
	Node * left ;
	Node * right ;
};

typedef Node * TreePtr ;

void InOrder( TreePtr root ) {
	if ( root != NULL ) {
		InOrder( root -> left ) ;
		cout << root -> data << '\n' ;
		InOrder( root -> right ) ;
	}
}

void PreOrder( TreePtr root ) {
	if ( root != NULL ) {
		cout << root -> data << '\n' ;
		PreOrder( root -> left ) ;
		PreOrder( root -> right ) ;
	}
}

void PostOrder( TreePtr root ) {
	if ( root != NULL ) {
		PostOrder( root -> left ) ;
		PostOrder( root -> right ) ;
		cout << root -> data << '\n' ;	
	}
}

void Add( TreePtr & root, int data ) {
	TreePtr check = root ;
	if ( root == NULL ) {
		root = new Node ;
		root -> data = data ;
		root -> left = NULL ;
		root -> right = NULL ;
	}
	else if ( check -> data < data )
		Add( check -> right, data ) ;
	else if ( check -> data > data )	
		Add( check -> left, data ) ;
}

bool Ontree( TreePtr root , int data ) {
	bool answer = false ;
	if ( root != NULL ) {
		if ( root -> data == data )
			answer = true ;
		else{
			answer = Ontree( root -> left, data ) ;
			if ( !answer )
				answer = Ontree( root -> right, data ) ;
		}
	}
	return answer ;
}

int Height( TreePtr root ) {
	if ( root == NULL )
		return -1 ;
	else {
		int Lheight = Height( root -> left ) ;
		int Rheight = Height( root -> right ) ;
		
		if ( Lheight > Rheight )
			return ( Lheight + 1 ) ;
		else
			return ( Rheight + 1 ) ;
	}
}

int main() 
{
	char command[30] = "\0" ;
	int data ;
	TreePtr binary_tree = NULL ;
	cin >> command ;
	while ( strcmp( command, "quit" ) != 0 && strcmp( command, "NULL" ) != 0 ) {
		if ( strcmp( command, "add" ) == 0 ) {
			cin >> data ;
			Add( binary_tree, data ) ;
		}
		
		else if ( strcmp( command, "init" ) == 0 )
			delete binary_tree ;
		
		else if ( strcmp( command, "empty" ) == 0 ) {
			if ( binary_tree != NULL )
				cout << "false" << '\n' ;
			else
				cout << "true" << '\n' ;
		}
		
		else if ( strcmp( command, "ontree" ) == 0 ) {
			cin >> data ;
			if ( Ontree( binary_tree, data ) )
				cout << "true" << '\n' ;
			else
				cout << "false" << '\n' ;
		}
		
		else if ( strcmp( command, "inorder" ) == 0 )
			InOrder( binary_tree ) ;
		else if ( strcmp( command, "preorder" ) == 0 )
			PreOrder( binary_tree ) ;
		else if ( strcmp( command, "postorder" ) == 0 )
			PostOrder( binary_tree ) ;
		else if ( strcmp( command, "height" ) == 0 )
			cout << Height( binary_tree ) << '\n' ;
			
		cin >> command ;
	}
}
