#pragma once
#include<iostream>

class Complex {
private:
	float realPart;
	float imaginaryPart;
public:
	// Constructors
	Complex();
	Complex(float r, float i);
	// getters
	float getRealPart() const;
	float getImaginaryPart() const;
	// operators
	Complex operator+(const Complex& other) const;
	Complex operator-(const Complex& other) const;
	Complex operator*(const Complex& other) const;
};