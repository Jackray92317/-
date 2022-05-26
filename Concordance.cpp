# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <iostream>

using namespace std ;

# define NOT !
# define AND &&
# define OR ||
# define EQ == 

enum  TokenType { IDENTIFIER = 1, CONSTANT = 2, SPECIAL = 3 };
typedef char * CharPtr ;

struct Column {
	int column ;
	Column * next ;
};

typedef Column * ColumnPtr ;

struct Line {
	int line ;
	ColumnPtr firstAppearAt ;
	ColumnPtr lastAppearAt ;
	Line * next ;
};

typedef Line * LinePtr ;

struct Token {
	CharPtr tokenStr ;
	TokenType type ;
	LinePtr firstAppearOn ;
	LinePtr lastAppearOn ;
	Token * next ;
};

typedef Token * TokenPtr ;

int gLine = 1 ;
int gColumn = 1 ;

char gNextChar = '\0' ;
int gNextCharLine = -1 ;
int gNextCharColumn = -1 ;

TokenPtr gFront = NULL ;

void GetNextChar( char & ch, int & line, int & column ) ;

CharPtr GetToken( TokenType & tokenType, int & firstCharLine, int & firstCharColumn ) ;

void OrderInsertToken( TokenPtr & head, CharPtr tokenStr, TokenType tokenType, int tokenLine, int tokenColumn ) ;

void PrintAllTokenInfo( int maxNumOfTokenToPrint, TokenPtr head ) ;

void HandleUI( TokenPtr head ) ;

void FindEnd() ;

bool IsWhiteSpace( char ch ) ;

bool IsDigit( char ch ) ;

bool IsLetter( char ch ) ;

bool IsSpecial( char ch ) ;

void SkipWhiteSpaces() ;

void SkipMultiLineComment() ;

CharPtr GetID() ;

CharPtr GetNum() ;

CharPtr GetCharConst() ;

CharPtr GetStringConst() ;

CharPtr GetSpecial() ;

int NumOfToken( TokenPtr head ) ;

int NumOfType( TokenPtr head, int type ) ;

void PrintOneToken( TokenPtr head, char token[150], bool & exist ) ;

void PrintOneLine( TokenPtr head, int line ) ;

int main() {
	char ch = '\0' ;
	CharPtr tokenStr = NULL ;
	int tokenLine = 0, tokenColumn = 0 ;
	TokenType tokenType ;
	TokenPtr listHead = NULL ;
	
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	
	do {
		tokenStr = GetToken( tokenType, tokenLine, tokenColumn ) ;
		if ( strcmp( tokenStr, "END_OF_FILE" ) != 0 )
		  OrderInsertToken( listHead, tokenStr, tokenType, tokenLine, tokenColumn ) ;	  
	} while( strcmp( tokenStr, "END_OF_FILE" ) != 0 ) ;
	
	PrintAllTokenInfo( 1000, listHead ) ;
	HandleUI( listHead ) ;
	
}

void GetNextChar( char & ch, int & line, int & column ) {
	ch = getchar() ;
	line = gLine ;
	column = gColumn ;
	if ( ch == '\n' ) {
		gColumn = 1 ;
		gLine++ ;
	}
	else gColumn++ ;
}

void FindEnd() {
	while ( gNextChar != '*' )
	  GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
    GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
    if ( gNextChar == '/' )
      GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
    else
      FindEnd() ;
}

bool IsSpecial( char ch ) {
	bool special = false ; 
	if ( ch == '^' )
	  special = true ;
	else if ( ch == ',' )
	  special = true ;
	else if ( ch == '(' )
	  special = true ;
	else if ( ch == ')' )
	  special = true ;
	else if ( ch == '{' )
	  special = true ;
	else if ( ch == '}' )
	  special = true ;
	else if ( ch == '!' )
	  special = true ;
	else if ( ch == ':' )
	  special = true ;
	else if ( ch == ';' )
	  special = true ;
	else if ( ch == '#' )
	  special = true ;
	else if ( ch == '?' )
	  special = true ;
	else if ( ch == '+' )
	  special = true ;
	else if ( ch == '-' )
	  special = true ;
	else if ( ch == '*' )
	  special = true ;
	else if ( ch == '/' )
	  special = true ;
	else if ( ch == '>' )
	  special = true ;
	else if ( ch == '<' )
	  special = true ;
	else if ( ch == '=' )
	  special = true ;
	else if ( ch == '%' )
	  special = true ;
	else if ( ch == '&' )
	  special = true ;
	else if ( ch == '|' )
	  special = true ;
	else if ( ch == '[' )
	  special = true ;
	else if ( ch == ']' )
	  special = true ;
	return special ;
}

bool IsDigit( char ch ) {
	bool number = false ;
	if ( ch == '0' )
	  number = true ;
	else if ( ch == '1' )
	  number = true ;
	else if ( ch == '2' )
	  number = true ;
	else if ( ch == '3' )
	  number = true ;
	else if ( ch == '4' )
	  number = true ;
	else if ( ch == '5' )
	  number = true ;
	else if ( ch == '6' )
	  number = true ;
	else if ( ch == '7' )
	  number = true ;
	else if ( ch == '8' )
	  number = true ;
	else if ( ch == '9' )
	  number = true ;
	return number ;
}

bool IsLetter( char ch ) {
	bool letter = false ;
	if ( ch == 'a' OR ch == 'A' )
	  letter = true ;
	else if ( ch == 'b' OR ch == 'B' ) 
	  letter = true ;
	else if ( ch == 'c' OR ch == 'C' ) 
	  letter = true ;
	else if ( ch == 'd' OR ch == 'D' ) 
	  letter = true ;
	else if ( ch == 'e' OR ch == 'E' ) 
	  letter = true ;
	else if ( ch == 'f' OR ch == 'F' ) 
	  letter = true ;
	else if ( ch == 'g' OR ch == 'G' ) 
	  letter = true ;
	else if ( ch == 'h' OR ch == 'H' ) 
	  letter = true ;
	else if ( ch == 'i' OR ch == 'I' ) 
	  letter = true ;
	else if ( ch == 'j' OR ch == 'J' ) 
	  letter = true ;
	else if ( ch == 'k' OR ch == 'K' ) 
	  letter = true ;
	else if ( ch == 'l' OR ch == 'L' ) 
	  letter = true ;
	else if ( ch == 'm' OR ch == 'M' ) 
	  letter = true ;
	else if ( ch == 'n' OR ch == 'N' ) 
	  letter = true ;
	else if ( ch == 'o' OR ch == 'O' ) 
	  letter = true ;
	else if ( ch == 'p' OR ch == 'p' ) 
	  letter = true ;
	else if ( ch == 'q' OR ch == 'Q' ) 
	  letter = true ;
	else if ( ch == 'r' OR ch == 'R' ) 
	  letter = true ;
	else if ( ch == 's' OR ch == 'S' ) 
	  letter = true ;
	else if ( ch == 't' OR ch == 'T' ) 
	  letter = true ;
	else if ( ch == 'u' OR ch == 'U' ) 
	  letter = true ;
	else if ( ch == 'v' OR ch == 'V' ) 
	  letter = true ;
	else if ( ch == 'w' OR ch == 'W' ) 
	  letter = true ;
	else if ( ch == 'x' OR ch == 'X' ) 
	  letter = true ;
	else if ( ch == 'y' OR ch == 'Y' ) 
	  letter = true ;
	else if ( ch == 'z' OR ch == 'Z' ) 
	  letter = true ;
	return letter ;
}

bool IsWhiteSpace( char ch ) {
	if ( ch == ' ' OR ch == '\t' OR ch == '\n' )  return true ;
	else return false ;	
}

void SkipWhiteSpaces() {
	if ( IsWhiteSpace( gNextChar ) ) {
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		SkipWhiteSpaces() ;
	}
}

void SkipLineComment() {
	int line = gNextCharLine ;
	if ( gNextChar == '/' ) {
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		while ( gNextCharLine = line ) 
		  GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	}
}

void SkipMultiLineComment() {
	if ( gNextChar == '*' ) {
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		FindEnd() ;
	}
}

CharPtr GetID() {
	CharPtr heap = new char[60] ;
	for ( int i = 0 ; i <= 59 ; i++ )
	  heap[i] = '\0' ;
	heap[0] = gNextChar ;
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	int i = 1 ;
	while ( IsLetter( gNextChar ) OR IsDigit( gNextChar ) OR gNextChar == '_' ) {
		heap[i] = gNextChar ;
		i++ ;
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	}
	
	return heap ;
}

CharPtr GetNum() {
	CharPtr heap = new char[20] ;
	for ( int i = 0 ; i <= 19 ; i++ )
	  heap[i] = '\0' ;
	heap[0] = gNextChar ;
	int k = 0 ;
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	for ( k = 1 ; IsDigit( gNextChar ) OR gNextChar == '.' ; k++ ) {
		heap[k] = gNextChar ;
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;	
	}
	
	return heap ;
}

CharPtr GetCharConst() {
	CharPtr heap = new char[10] ;
	for ( int i = 0 ; i <= 9 ; i++ )
	  heap[i] = '\0' ;
	heap[0] = gNextChar ;
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	if ( gNextChar == '\\' ) {
		heap[1] = gNextChar ;
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		if ( gNextChar == 't' OR gNextChar == 'n' OR gNextChar == '\'' OR gNextChar == '0' ) {
			heap[2] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
			heap[3] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
		
		else {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
			heap[2] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	else {
		heap[1] = gNextChar ;
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		heap[2] = gNextChar ;
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	}
	
	return heap ;
}

CharPtr GetStringConst() {
	CharPtr heap = new char[150] ;
	for ( int k = 0 ; k <= 149 ; k++ )
	  heap[k] = '\0' ;
	char temp = '\0' ;
	heap[0] = gNextChar ;
	int i = 1 ;
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	while ( gNextChar != '\"' ) {
		temp = gNextChar ;
		GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		if ( temp == '\\' ) {
			if ( gNextChar == 'n' OR gNextChar == 't' OR gNextChar == '\'' OR gNextChar == '0' OR gNextChar == '\"' ) {
				heap[i] = temp ;
				heap[i+1] = gNextChar ;
				i += 2 ;
				GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
 			}
 			else
 			  GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
		else {
			heap[i] = temp ;
			i++ ;
		}
	}
	
	heap[i] = gNextChar ;
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	return heap ;
}

CharPtr GetSpecial() {
	CharPtr heap = new char[10] ;
	for ( int i = 0 ; i <= 9 ; i++ )
	  heap[i] = '\0' ;
	char temp = '\0' ;
	heap[0] = gNextChar ;
	temp = gNextChar ;
	GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
	if ( temp == '=' OR temp == '*' ) {
		if ( gNextChar == '=' ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	else if ( temp == '!' OR temp == '%' ) {
		if ( gNextChar == '=' ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}  
	else if ( temp == '-' ) {
		if ( gNextChar == '>' OR gNextChar == '=' OR gNextChar == '-' ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	else if ( temp == '+' ) {
		if ( gNextChar == '+' OR gNextChar == '=' ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	else if ( temp == '>' ) {
		if ( gNextChar == '=' OR gNextChar == '>' ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	else if ( temp == '<' ) {
		if ( gNextChar == '=' OR gNextChar == '<' ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	else if ( temp == '&' OR temp == '|' ) {
		if ( gNextChar == temp ) {
			heap[1] = gNextChar ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
		}
	}
	
	return heap ;
}

CharPtr GetToken( TokenType & tokenType, int & firstCharLine, int & firstCharColumn ) {
	CharPtr tokenStr = NULL ;
	int lineOfDivide = -1, columnOfDivide = -1 ;
	bool slashIsDivide = false ;
	while ( IsWhiteSpace( gNextChar ) OR ( gNextChar == '/' AND NOT slashIsDivide ) ) {
		if ( IsWhiteSpace( gNextChar ) )
		  SkipWhiteSpaces() ;
		
		else if ( gNextChar == '/' ) {
			lineOfDivide = gNextCharLine ;
			columnOfDivide = gNextCharColumn ;
			GetNextChar( gNextChar, gNextCharLine, gNextCharColumn ) ;
			
			if ( gNextChar == '/' )
			  SkipLineComment() ;
			else if ( gNextChar == '*' )
			  SkipMultiLineComment() ;
			else 
			  slashIsDivide = true ;
		}
	}
	
	firstCharLine = gNextCharLine ;
	firstCharColumn = gNextCharColumn ;
	if ( slashIsDivide ) {
		CharPtr heap = new char[10] ;
		for ( int k = 0 ; k <= 9 ; k++ ) 
		  heap[k] = '\0' ;
		heap[0] = '/' ;
		firstCharLine = lineOfDivide ;
		firstCharColumn = columnOfDivide ;
		tokenStr = heap ;
		tokenType = SPECIAL ;
	}
	else {
		if ( IsLetter( gNextChar ) OR gNextChar == '_' ) {
			tokenStr = GetID() ;
			tokenType = IDENTIFIER ;
		}
		else if ( IsDigit( gNextChar ) OR gNextChar == '.' ) {
			tokenStr = GetNum() ;
			tokenType = CONSTANT ;
		}
		else if ( gNextChar == '\'' ) {
			tokenStr = GetCharConst() ;
			tokenType = CONSTANT ;
		}
		else if ( gNextChar == '\"' ) {
			tokenStr = GetStringConst() ;
			tokenType = CONSTANT ;
		}
		else if ( IsSpecial( gNextChar ) ) {
			tokenStr = GetSpecial() ;
			tokenType = SPECIAL ;
		}
		
	}
	
	return tokenStr ;
}

void OrderInsertToken( TokenPtr & head, CharPtr tokenStr, TokenType tokenType, int tokenLine, int tokenColumn ) {
	TokenPtr check = head ;
	if ( head == NULL ) {
		head = new Token ;
		head -> tokenStr = tokenStr ;
		head -> type = tokenType ;
		head -> firstAppearOn -> line = tokenLine ;
		head -> firstAppearOn -> firstAppearAt = new Column ;
		head -> firstAppearOn -> firstAppearAt -> column = tokenColumn ;
		head -> firstAppearOn -> firstAppearAt -> next = NULL ;
		head -> firstAppearOn -> lastAppearAt = head -> firstAppearOn -> firstAppearAt ;
		head -> firstAppearOn -> next = NULL ;
		head -> lastAppearOn = head -> firstAppearOn ;
		head -> next  = NULL ;	
	}
	else if ( strcmp( check -> tokenStr, tokenStr ) < 0 ) 
	  OrderInsertToken( check -> next, tokenStr, tokenType, tokenLine, tokenColumn ) ;
	else if ( strcmp( check -> tokenStr, tokenStr ) == 0 ) {
		if ( check -> lastAppearOn -> line == tokenLine ) {
			ColumnPtr temp = NULL ;
			temp = new Column ;
			temp -> column = tokenColumn ;
			temp -> next = NULL ;
			check -> lastAppearOn -> lastAppearAt -> next = temp ;
			check -> lastAppearOn -> lastAppearAt = temp ;
			temp = NULL ;
			delete temp ;
		}
		else {
			LinePtr temp = NULL ;
			temp = new Line ;
			temp -> line = tokenLine ;
			temp -> firstAppearAt -> column = tokenColumn ;
			temp -> firstAppearAt -> next = NULL ;
			temp -> lastAppearAt = temp -> firstAppearAt ;
			temp -> next = NULL ;
			check -> lastAppearOn -> next = temp ;
			check -> lastAppearOn = temp ;
			temp = NULL ;
			delete temp ;
		}
	}
	else if ( strcmp( check -> tokenStr, tokenStr ) > 0 ) {
		TokenPtr newT = NULL ;
		newT -> tokenStr = tokenStr ;
		newT -> type = tokenType ;
		newT -> firstAppearOn -> line = tokenLine ;
		newT -> firstAppearOn -> firstAppearAt -> column = tokenColumn ;
		newT -> firstAppearOn -> firstAppearAt -> next = NULL ;
		newT -> firstAppearOn -> lastAppearAt = newT -> firstAppearOn -> firstAppearAt ;
		newT -> firstAppearOn -> next = NULL ;
		newT -> lastAppearOn = newT -> firstAppearOn ;
		newT -> next = head ;
		head = newT ;
		newT = NULL ;
		delete newT ;
	}
}

void PrintAllTokenInfo( int maxNumOfTokenToPrint, TokenPtr head ) {
	TokenPtr temp1 = head ;
	int count ;
	if ( temp1 != NULL ) {
		LinePtr temp2 = temp1 -> firstAppearOn ;
		ColumnPtr temp3 = temp2 -> firstAppearAt ;
		while ( temp1 != NULL AND count < maxNumOfTokenToPrint ) {
			printf( "%s", temp1 -> tokenStr ) ;
			temp2 = temp1 -> firstAppearOn ;
			while ( temp2 != NULL ) {
				temp3 = temp2 -> firstAppearAt ;
				while ( temp3 != NULL ) {
					if ( temp2 != temp1 -> lastAppearOn )
					  printf( "(%d,%d) ", temp2 -> line, temp3 -> column ) ;
					else {
						if ( temp3 != temp2 -> lastAppearAt ) 
						  printf( "(%d,%d) ", temp2 -> line, temp3 -> column ) ;
						else
						  printf( "(%d,%d)\n", temp2 -> line, temp3 -> column ) ;
					}
					
					temp3 = temp3 -> next ;
				}
				
				temp2 = temp2 -> next ;
			}
			
			temp1 = temp1 -> next ;
			count++ ;
		}
	}
}

int NumOfToken( TokenPtr head ) {
	int num = 0 ;
	TokenPtr temp = head ;
	while ( temp != NULL ) {
		num++ ;
		temp = temp -> next ;
	}
	
	return num ;
}

int NumOfType( TokenPtr head, int type ) {
	TokenPtr temp = head ;
	int num = 0 ;
	while ( temp != NULL ) {
		if ( temp -> type == type )
		  num++ ;
		temp = temp -> next ;
	}
	
	return num ;
}

void PrintOneToken( TokenPtr head, char token[150], bool & exist ) {
	TokenPtr temp1 = head ;
	if ( temp1 != NULL ) {
		LinePtr temp2 = temp1 -> firstAppearOn ;
		ColumnPtr temp3 = temp2 -> firstAppearAt ;
		while ( temp1 != NULL ) {
			if ( strcmp( temp1 -> tokenStr, token ) == 0 ) {
				printf( "%s", temp1 -> tokenStr ) ;
				exist = true ;
				temp2 = temp1 -> firstAppearOn ;
				while ( temp2 != NULL ) {
					temp3 = temp2 -> firstAppearAt ;
					while ( temp3 != NULL ) {
						if ( temp2 != temp1 -> lastAppearOn )
						  printf( "(%d,%d) ", temp2 -> line, temp3 -> column ) ;
						else {
							if ( temp3 != temp2 -> lastAppearAt ) 
							  printf( "(%d,%d) ", temp2 -> line, temp3 -> column ) ;
							else 
							  printf( "(%d,%d)\n", temp2 -> line, temp3 -> column ) ;
						}
						
						temp3 = temp3 -> next ;
					}
					
					temp2 = temp2 -> next ;
				}
				
				temp1 = NULL ;
			}
			
			else 
			  temp1 = temp1 -> next ;
		}
	}
}

void PrintOneLine( TokenPtr head, int line ) {
	TokenPtr temp1 = head ;
	if ( temp1 != NULL ) {
		LinePtr temp2 = temp1 -> firstAppearOn ;
		while ( temp1 != NULL ) {
			temp2 = temp1 -> firstAppearOn ;
			while ( temp2 != NULL ) {
				if ( temp2 -> line == line )
				  printf( "%s\n", temp1 -> tokenStr ) ;
				
				temp2 = temp2 -> next ;
			}
			
			temp1 = temp1 -> next ;
		}
	}
}

void HandleUI( TokenPtr head ) {
	printf( "\nWelcome to interactive I/O.\n" ) ;
	printf( "1. How many different tokens are there for each case?\n" ) ;
	printf( "2. How many tokens are there for each case?\n" ) ;
	printf( "3. Print(line number, column number) of this token ->\n" ) ;
	printf( "4. What tokens appear on this line ->\n" ) ;
	printf( "5. End.\n" ) ;
	int command = -1 ;
	printf( "\n> " ) ;
	int test = scanf( "%d", &command ) ;
	while ( command != 5 AND test != EOF ) {
		if ( command == 1 )
		  printf( "There are %d different tokens in total.\n", NumOfToken( head ) ) ;
		else if ( command == 2 ) {
			printf( "Identifier: %d\n", NumOfType( head, IDENTIFIER ) ) ;
			printf( "Constant: %d\n", NumOfType( head, CONSTANT ) ) ;
			printf( "Special: %d\n", NumOfType( head, SPECIAL ) ) ;
		}
		else if ( command == 3 ) {
			char token[150] ;
			for ( int k = 0 ; k <= 149 ; k++ )
			  token[k] = '\0' ;
			cin >> token ;
			bool bRun = false ;
			PrintOneToken( head, token, bRun ) ;
			if ( !bRun )
			  printf( "There is no such token : %s\n", token ) ;
		}
		else if ( command == 4 ) {
			int line = -1 ;
			cin >> line ;
			PrintOneLine( head, line ) ;
		}
		else 
		  printf( "There is no such command %d.\n", command ) ;
		
		printf( "\n> " ) ;
		test = scanf( "%d", &command ) ;
	}
}
