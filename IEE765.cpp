# include <iostream>
# include <stdlib.h>
# include <string.h>
# include <math.h>

using namespace std ;

typedef char Str40[ 40 ] ;

void FractionAnalysis(Str40 floatStr, bool &nonNegative, int & decimal, int & intOfFraction, int &numDigits)
{
	nonNegative = true ;
	int i = 0 ;
	Str40 temp1 = {'\0'} ;
	Str40 temp2 = {'\0'} ;
	int a = 0 ;
	if (floatStr[0] == '-')
	{
		nonNegative = false ;
		i = 1 ;
	}
	
	while (floatStr[i] != '.' && floatStr[i] != '\0')
	{
		temp1[a] = floatStr[i] ;
		i++ ;
		a++ ;
	}
	
	i++ ;
	while (floatStr[i] != '\0' && floatStr[i] == '0')
	{
		numDigits++ ;
		i++ ;
	}
	
	for (int a = 0 ; floatStr[i] != '\0' ; a++)
	{
		temp2[a] = floatStr[i] ;
		numDigits++ ;
		i++ ;
	}
	
	int len1 = strlen(temp1) - 1 ;
	int len2 = strlen(temp2) - 1 ;
	int cal = 1 ;
	while (len1 >= 0)
	{
		int num1 = temp1[len1] - '0' ;
		decimal = decimal + num1 * cal ;
		cal = cal * 10 ;
		len1-- ;
	}
	cal = 1 ;
	while (len2 >= 0)
	{
		int num2 = temp2[len2] - '0' ;
		intOfFraction = intOfFraction + num2 * cal ;
		cal  = cal * 10 ;
		len2-- ;
	}
	
}

void DecimalToBinary(int decimal , Str40 &binary)
{
	int i = 0 ;  
	Str40 temp = {'0'} ;
	while (decimal != 0)
	{
		int quot = decimal / 2 ;
		int remain = decimal % 2 ;
		if (remain == 0)
		  temp[i] = '0' ;
		else if (remain == 1)
		  temp[i] = '1' ;
		i++ ;
		decimal = quot ;
	}
	
	int length = strlen(temp) ;
	for (i = 0 ; i < length ; i++)
	  binary[i] = temp[length - i - 1] ;
}

void FractionToBinary(int inputNum, int numOfInputDigits, Str40 &outputNum)
{
	int check = 1 ;
	int two = 0 ;
	int i = 0 ;
	int a = numOfInputDigits ;
	while (a > 0)
	{
		check = check * 10 ;
		a-- ;
	}
	
	while ((inputNum % check) != 0 && i < 10)
	{
		inputNum = inputNum * 2 ;
		two = inputNum / check ;
		if (two == 0)
		  outputNum[i] = '0' ;
		else if (two == 1 )
		  outputNum[i] = '1' ;
		if (inputNum >= check)
		  inputNum = inputNum - check ;
		i++ ;
	}
}

void FindMantissaExponent(Str40 &inputDecimal, Str40 &inputFraction, Str40 &mantissa, int &exponent)
{
	Str40 temp = {'0'} ;
	Str40 temp3 ;
	int i = 0 ;
	for (i = 0 ; i < 23 ; i++)
	  temp3[i] = '0' ;
	int k = 0 ;
	char temp2 = '\0' ;
	strcpy(temp, inputDecimal ) ;
	int length = strlen(temp) ;
	temp[length] = '.' ;
	int a = length ;
	length++ ;
	for ( i = 0 ; inputFraction[i] != '\0' ; i++ )
	{
		temp[length] = inputFraction[i] ;
		length++ ;
	}
	
	i = 0 ;
	if (temp[i] == '0')
	{
		i = a ;
		while (temp[i+1] != '1' && temp[i+1] != '\0')
		{
			i++ ;
			temp[i] = temp[i-1] ;
			exponent-- ;
		}
		
		if (temp[i+1] == '\0')
		  exponent = -127 ;
		if (temp[i+1] != '\0')
		{
			temp[i+1] = temp[i] ;
			exponent-- ;
		}
		
		for ( k = 0 ; temp[i+2] != '\0' ; k++ )
		{
			mantissa[k] = temp[i+2] ;
			i++ ;
		}
	}
	
	i = 0 ;
	if ( temp[i] == '1' )
	{
		i = a ;
		while ( i > 1 )
		{
			temp2 = temp[i-1] ;
			temp[i-1] = temp[i+1] ;
			temp[i] = temp2 ;
			i-- ;
			exponent++ ;
		}
		
		k = 0 ;
		while( temp[i+1] != '\0' )
		{
			temp3[k] = temp[i+1] ;
			k++ ;
			i++ ;
		}
	}
	
	strcpy( mantissa, temp3 ) ;
}

void DecimalToExcess127( int exponent, Str40 &temp_excess127 )
{
	int num = exponent + 127 ;
	int i = 0 ;
	Str40 temp ;
	while ( i < 8 )
	{
		temp[i] == '0' ;
		i++ ;
	}
	
	i = 0 ;
	while (num != 0)
	{
		int quot = num / 2 ;
		int remain = num % 2 ;
		if (remain == 1)
		  temp[i] = '1' ;
		i++ ;
		num = quot ;
	}
	
	for ( i = 0 ; i < 8 && temp[i] != '\0' ; i++ )
	  temp_excess127[i] = temp[8 - i -1] ;
}

int main()
{
	Str40 inputString = " " ;
	bool sign = true ;
	int decimal = 0 ;
	int intOfFraction = 0 ;
	int numDigits =  0 ; 
	Str40 binary_decimal = " " ;
	Str40 binary_fraction = " " ;
	Str40 binary_mantissa = " " ;
	int exp = 0 ;
	Str40 temp_excess127 = " " ;
	Str40 binary_excess127 = " " ;
	
	cout << "Please enter a randon numbers or floats: " ;
	
	cin >> inputString ;
	
	FractionAnalysis( inputString, sign, decimal, intOfFraction, numDigits ) ;
	
	DecimalToBinary(decimal, binary_decimal) ;
	
	FractionToBinary(intOfFraction, numDigits, binary_fraction) ;
	
	FindMantissaExponent(binary_decimal, binary_fraction, binary_mantissa, exp) ;
	
	DecimalToExcess127(exp, temp_excess127) ;
	
	int count = 0 ;
	for (count = 0 ; count < 8 - strlen(temp_excess127) ; count ++)
	  binary_excess127[count] = '0' ;
	
	strcat( binary_excess127, temp_excess127 ) ;
	
	cout << "The IEE765 numbers after turning: " ;
	
	if (sign)
	  cout << "0" << binary_excess127 << " " << binary_mantissa ;
	else
	  cout << "1" << binary_excess127 << " " << binary_mantissa ;
	
	return 0 ;
}

