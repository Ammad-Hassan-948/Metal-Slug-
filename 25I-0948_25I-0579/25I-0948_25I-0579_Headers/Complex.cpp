#include<iostream>
#include "Complex.h"

// constructors
Complex::Complex() : realPart(0.0f), imaginaryPart(0.0f) {  }


Complex::Complex(float r, float i) : realPart(r), imaginaryPart(i) {  }


// getters
float Complex::getRealPart() const
{
	return realPart;
}

float Complex::getImaginaryPart() const
{
	return imaginaryPart;
}


// operators
Complex Complex::operator+(const Complex& other) const
{
	float newR = this->realPart + other.realPart;
	float newI = this->imaginaryPart + other.imaginaryPart;
	// Now i will make new complex object toreturn
	Complex result(newR, newI);

	return result;

}

Complex Complex::operator-(const Complex& other) const
{
	float newR = this->realPart - other.realPart;
	float newI = this->imaginaryPart - other.imaginaryPart;
	// Now i will make new complex object toreturn
	Complex result(newR, newI);

	return result;
}

Complex Complex::operator*(const Complex& other) const
{
	// As multiplication (2+3i)(3+2i) = 2*3 + 2*2i + 3i*3 + 3i*2i
	// so real part will be real1*real2 - imag1*imag2  ( adding - beacuse of i square )
	// imaginary part will be real1*imag2 + imag1*real2

	float newR = (this->realPart * other.realPart) - (this->imaginaryPart * other.imaginaryPart);
	float newI = (this->realPart * other.imaginaryPart) + (this->imaginaryPart * other.realPart);
	// Now i will make new complex object toreturn
	Complex result(newR, newI);

	return result;
}

