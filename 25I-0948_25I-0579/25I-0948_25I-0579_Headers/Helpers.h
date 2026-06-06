#pragma once
#include<iostream>

// Helpers for strings

// Helper function to get lenght of string
int getLength(const char* str);


// Helper function to compare string
bool stringCompare(const char* str1, const char* str2);




// Helper to copy string
char* copyString(const char* str);


void copyToStatic(char* store, const char* toStore);


int compareOrder(const char* str1, const char* str2);


int stringToInt(char* str);



int pow(int num, int exp);


float stringToFloat(char* str);



int* copyIntegars(int* data, int size);


float* copyFloat(float* data, int size);