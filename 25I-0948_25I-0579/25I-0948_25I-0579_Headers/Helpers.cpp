#include<iostream>
#include"Helpers.h"

// Helpers for strings

// Helper function to get lenght of string
int getLength(const char* str) {
	int i = 0;
	while (*(str + i) != '\0')
		i++;
	return i;
}




// Helper function to compare string
bool stringCompare(const char* str1, const char* str2) {
	int length1 = getLength(str1);
	int length2 = getLength(str2);

	if (length1 != length2)
		return false;

	for (int i = 0; i < length1; i++) {
		if (str1[i] != str2[i])
			return false;
	}
	return true;

}




// Helper to copy string
char* copyString(const char* str) {
	int len = getLength(str);
	char* copied = new char[len + 1];

	int i = 0;
	for (i = 0; i < len; i++) {
		copied[i] = str[i];
	}
	copied[i] = '\0';

	return copied;
}

void copyToStatic(char* store, const char* toStore)
{
	int i = 0;
	for (i = 0; toStore[i] != '\0'; i++)
		store[i] = toStore[i];

	store[i] = '\0';
}

int compareOrder(const char* str1, const char* str2)
{
	int i = 0;

	while (1) {
		if (str1[i] < str2[i])
			return -1;      // if it is less return -1
		if (str1[i] > str2[i])
			return 1;      // if it is greater return 1

		if (str1[i] == '\0')
			return 0;;       // return 0 if end reached

		i++;
	}


}

int stringToInt(char* str)
{
	int i = 0;
	bool isNeg = false;

	while (str[i] == ' ')        // to skip spaces
		i++;

	if (str[i] == '-') {
		isNeg = true;
		i++;
	}

	if (!(str[i] >= '0' && str[i] <= '9'))
		return 0;

	// i will first take the first character of buffer
	int num = str[i] - '0';        // now first number is saved at integar

	for (i += 1; (str[i] >= '0' && str[i] <= '9'); i++) {

		num *= 10;
		int a = str[i] - '0';          // seperate the number
		num += a;

	}

	if (isNeg)
		return -num;

	return num;
}



int pow(int num, int exp)
{
	int result = 1;

	for (int i = 0; i < exp; i++)
		result *= num;

	return result;
}

float stringToFloat(char* str)
{
	// now first i will copy the integar part then decimal part
	char integar[20];
	char decimal[20];
	int i = 0;
	int j = 0;


	// first copy integar part
	for (i = 0; str[i] != '.' && str[i] != '\0'; i++) {
		integar[j++] = str[i];
	}
	integar[j] = '\0';


	int intPart = stringToInt(integar);


	if (str[i] == '\0')
		return (float)intPart;     // if number only has integar part and no decimal part


	// now decimal part
	j = 0;
	for (i++; str[i] != '\0'; i++) {
		decimal[j++] = str[i];
	}
	decimal[j] = '\0';

	int decimalPart = stringToInt(decimal);

	// now i have both integar part and decimal part i also have count of decimal numbers
	// i will divide the decimal part by the decimalCount th power of 10, decimal count is j
	int div = pow(10, j);

	float decimalConv = (float)decimalPart / (float)div;

	float number = (float)intPart + decimalConv;

	return number;
}



int* copyIntegars(int* data, int size) {
	int* copy = new int[size];
	for (int i = 0; i < size; i++)
		copy[i] = data[i];

	return copy;
}

float* copyFloat(float* data, int size) {
	float* copy = new float[size];
	for (int i = 0; i < size; i++)
		copy[i] = data[i];

	return copy;
}
