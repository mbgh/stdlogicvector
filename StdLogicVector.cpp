/******************************************************************************
 *
 * An implementation of the std_logic_vector VHDL data type in C++
 * Copyright (C) 2014 ETHZ Zurich, Integrated Systems Laboratory
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

/**
 * @file StdLogicVector.cpp
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 03 April 2014
 * @brief An implementation of the std_logic_vector VHDL data type in C++
 * @version 0.1
 *
 * In order to generate bit-true C++ models of VHDL implementations, this file
 * provides an equivalent C++ class of the std_logic_vector data type available
 * in VHDL. Since the value of a StdLogicVector can be of arbitrary length, its
 * actual value is internally represented using the GMP library [1] for
 * arbitrary arithmetic functions. Therefore, this class represents kind of
 * a wrapper around the GMP library, which allows simple arithmetic as it is
 * often used when designing with VHDL or other hardware description languages.
 *
 * @see [1] https://gmplib.org/
 */
#include <iostream>
#include <sstream>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include <math.h>
#include <algorithm>

#include "StdLogicVector.h"

using namespace std;

// ****************************************************************************
// Constructors/Destructors
// ****************************************************************************
/**
 * @brief The default constructor creates a new StdLogicVector of length
 *   zero and initializes its value to zero.
 */

StdLogicVector::StdLogicVector() {
  mpz_init(value_);
  length_ = 0;
}

/**
 * @brief Creates a StdLogicVector of size @p _length and initializes its value
 *   to zero.
 * @param _length The length of the StdLogicVector in bits.
 */
StdLogicVector::StdLogicVector(unsigned int _length) {
  mpz_init(value_);
  length_ = _length;
}

/**
 * @brief Creates a StdLogicVector of size @p _length and initializes its value
 *   to the provided @p _value.
 *
 * @param _value The value to be assigned to the StdLogicVector.
 * @param _length The length of the StdLogicVector in bits.
 * @todo Check whether the bits are enough to represent the provided value.
 */
StdLogicVector::StdLogicVector(unsigned long long _value, unsigned int _length) {
  mpz_init(value_);
  // First version to initialize a GMP variable from unsigned long long.
  mpz_import(value_, 1, -1, sizeof(_value), 0, 0, &_value);
  // Second version to initialize a GMP variable from unsigned long long.
//  mpz_set_ui(value, (unsigned int)(_value >> 32));
//  mpz_mul_2exp(value, value, 32);
//  mpz_add_ui(value, value, (unsigned int)_value);
  length_ = _length;
}

/**
 * @brief Creates a StdLogicVector of size @p _length and initializes its value
 *   to the given @p _value provided as a string in the respective number
 *   @p _base.
 *
 * @param _value The value to be assigned to the StdLogicVector represented as
 *   a string. The left-most character (i.e., the first character) of the
 *   string represents to most significant digit, while the right-most
 *   character (i.e., the last character) of the string represents the least
 *   significant one.
 * @param _base The base in which the @p _value is given.
 * @param _length The length of the StdLogicVector in bits.
 * @todo Check whether the bits are enough to represent the provided value.
 */
StdLogicVector::StdLogicVector(string _value, int _base, unsigned int _length) {
  mpz_init_set_str(value_, _value.c_str(), _base);
  length_ = _length;
}

/**
 * @brief Creates a StdLogicVector of size @p _length and initializes its value
 *   using the byte array to which @p _value points.
 *
 * @param _value A pointer to the byte array to be used for the initialization
 *   of the StdLogicVector.
 * @param _bytes Number of bytes to be used for the initialization of the
 *   present StdLogicVector.
 * @param _length The length of the StdLogicVector in bits.
 * @todo Check whether the bits are enough to represent the provided value.
 */
StdLogicVector::StdLogicVector(unsigned char *_value, int _bytes,
     unsigned int _length) {
	mpz_init(value_);
  mpz_import(value_, _bytes, 1, sizeof(_value[0]), 1, 0, _value);
  length_ = _length;
}

/**
 * @brief Destructor
 */
StdLogicVector::~StdLogicVector() {
}

/**
 * @brief Copy-constructor. Creates a deep copy of both the @a length_ and the
 *   @a value_ of the StdLogicVector.
 * @param _other The StdLogicVector to be copied.
 */
StdLogicVector::StdLogicVector (const StdLogicVector & _other) {
	length_ = _other.getLength();
	mpz_init_set(value_, _other.getValue());
}



// ****************************************************************************
// Getter/Setter functions
// ****************************************************************************
/**
 * @brief Returns the value of the StdLogicVector as it is represented
 *   internally, i.e., as a GMP-specific @c mpz_t data type.
 * @return The value of the StdLogicVector as a GMP-specific data type.
 */
const mpz_t & StdLogicVector::getValue() const {
  return value_;
}

/**
 * @brief Returns the length of the StdLogicVector.
 * @return The length of the StdLogicVector.
 */
int StdLogicVector::getLength() const {
	 return length_;
}


// **************************************************************************
// Operator Overloadings
// **************************************************************************
/**
 * @brief Equality operator. Returns true of both the value and the length of
 *   the two StdLogicVectors are identical.
 * @param _input The StdLogicVector to compare with.
 * @return True if both the value and the length of the two StdLogicVectors are
 *   equal. Otherwise false.
 */
bool StdLogicVector::operator==(const StdLogicVector & _input) const {

	if ( _input.getLength() == this->getLength()) {
		if ( mpz_cmp(_input.getValue(), this->getValue()) == 0) {
			return true;
		}
	}
	return false;
}

/**
 * @brief Inequality operator. Returns true if one or both the value and the
 *   length of the two StdLogicVectors do not match.
 * @param _input The StdLogicVector to compare with.
 * @return True if both one or both the value and the length of the two
 *   StdLogicVectors do not match.
 */
bool StdLogicVector::operator!=(const StdLogicVector & _input) const {
	return !(*this == _input);
}

/**
 * @brief Provide a nice stream output showing the value of the StdLogicVector
 *   in hexadecimal representation and also its length.
 */
ostream & operator<<(ostream & _os, const StdLogicVector & _stdLogicVec)
{
    _os << _stdLogicVec.ToString(16, true) << "(" << _stdLogicVec.getLength() << "bits)";
    return _os;
}


// ****************************************************************************
// Public Methods
// ****************************************************************************
/**
 * @brief Tests a single bit of the StdLogicVector whether it is set or not.
 *
 * @param _index The index of the bit to be tested (zero-based).
 * @return A boolean value determining whether the bit at the provided index is
 *   set or not.
 * @retval 0 If bit is zero.
 * @retval 1 If bit is one.
 */
int StdLogicVector::TestBit(int _index) const {
  return mpz_tstbit(value_, _index);
}


/**
 * @brief Converts the value of the current StdLogicVector into an unsigned
 *        long long and returns it.
 *
 * @return The value of the StdLogicVector as an unsigned long long.
 *
 * @todo Throw an exception when the length of the StdLogicVector is larger
 *   than what fits into an unsigned long long (usually 64bits).
 */
unsigned long long StdLogicVector::ToULL() {
  return static_cast<const StdLogicVector &>( *this ).ToULL();
}

/**
 * @brief Converts the value of the current StdLogicVector into an unsigned
 *        long long and returns it.
 *
 * @return The value of the StdLogicVector as an unsigned long long.
 *
 * @todo Throw an exception when the length of the StdLogicVector is larger
 *   than what fits into an unsigned long long (usually 64bits).
 */
unsigned long long StdLogicVector::ToULL() const {
  unsigned int lowerWord, higherWord;
  mpz_t tmp;

  mpz_init( tmp );
  mpz_mod_2exp( tmp, value_, 64 );

  lowerWord = mpz_get_ui( tmp );
  mpz_div_2exp( tmp, tmp, 32 );
  higherWord = mpz_get_ui( tmp );

  mpz_clear( tmp );

  return (((unsigned long long)higherWord) << 32) + lowerWord;
}

/**
 * @brief Returns a string representing the value of the StdLogicVector as a
 *   decimal number.
 * @return The value of the StdLogicVector as a decimal string.
 */
string StdLogicVector::ToString(){
	return this->ToString(10, false);
}

/**
 * @brief Returns a string representing the value of the StdLogicVector as a
 *   decimal number with leading zeros (if desired).
 * @param _pad Determines whether to pad the returned value using leading zeros
 *   (as many as determined by the length of the StdLogicVector).
 * @return The value of the StdLogicVector as a decimal string (with leading
 *   zeros).
 */
string StdLogicVector::ToString(bool _pad){
	return this->ToString(10, _pad);
}

/**
 * @brief Returns a string representing the value of the StdLogicVector as a
 *   number in the provided base representation.
 * @param _base The base in which the number should be represented.
 * @return The value of the StdLogicVector in the provided base representation.
 */
string StdLogicVector::ToString(int _base) {
	return this->ToString(_base, false);
}

/**
 * @brief Returns a string representing the value of the StdLogicVector as a
 *   number in the provided base representation.
 * @param _base The base in which the number should be represented.
 * @return The value of the StdLogicVector in the provided base representation.
 */
string StdLogicVector::ToString(int _base) const{
	return this->ToString(_base, false);
}

/**
 * @brief Returns a string representing the value of the StdLogicVector as a
 *   number in the provided base representation and with leading zeros (if
 *   desired).
 * @param _base The base in which the number should be represented.
 * @param _pad Determines whether to pad the returned value using leading zeros
 *   (as many as determined by the length of the StdLogicVector).
 * @return The value of the StdLogicVector in the provided base representation.
 */
string StdLogicVector::ToString(int _base, bool _pad) {
	return  static_cast<const StdLogicVector &>( *this ).ToString(_base, _pad);
}

/**
 * @brief Returns a string representing the value of the StdLogicVector as a
 *   number in the provided base representation and with leading zeros (if
 *   desired).
 * @param _base The base in which the number should be represented.
 * @param _pad Determines whether to pad the returned value using leading zeros
 *   (as many as determined by the length of the StdLogicVector).
 * @return The value of the StdLogicVector in the provided base representation.
 */
string StdLogicVector::ToString(int _base, bool _pad) const {

  double baseLength;
  string strValue;
  string strTmp = mpz_get_str(NULL, _base, value_);

  // Determine size of the value (i.e., length of string) for the given base.
  baseLength = ceil(length_ / (log(_base)/log(2)));

  // Apply padding if required.
  if (strTmp.length() < baseLength && _pad) {
    strValue.append(baseLength-strTmp.length(), '0');
  }
  strValue.append(strTmp);

  return strValue;
}

/**
 * @brief Returns a pointer to an array of bytes containing the value of the
 *   StdLogicVector.
 * @return Pointer to the byte-array containing the StdLogicVector value.
 */
//unsigned char * StdLogicVector::ToByteArray() {
//void StdLogicVector::ToByteArray(unsigned char & _byteArray) {
//
////  return const_cast<unsigned char *>(static_cast<const StdLogicVector &>( *this ).ToByteArray());
//}

/**
 * @brief Fills the provided byte array with the respective bytes of the value
 *   of the StdLogicVector.
 * @param _byteArray The byte array to be filled with the byte values.
 */
void StdLogicVector::ToByteArray(unsigned char _byteArray[]) const {

  string hexString = this->ToString(16, true);
  int length       = hexString.length();
  unsigned int n;

  for (int i = 0; i < length; i=i+2) {
    sscanf(hexString.c_str() + i, "%2X", &n);
    _byteArray[i/2] = (char)n;
  }
}

/**
 * @brief Shift left operation.
 * @param _bits Number of bits to be shifted to the left.
 * @return The StdLogicVector shifted to the left by the determined number of
 *   bits.
 */
StdLogicVector& StdLogicVector::ShiftLeft(int _bits) {
  mpz_mul_2exp(value_, value_, _bits);
  return *this;
}

/**
 * @brief Shift right operation.
 * @param _bits Number of bits to be shifted to the right.
 * @return The StdLogicVector shifted to the right by the determined number of
 *   bits.
 */
StdLogicVector& StdLogicVector::ShiftRight(int _bits) {
  mpz_tdiv_q_2exp(value_, value_, _bits);
  return *this;
}

/**
 * @brief Bitwise AND operation.
 * @param _operand The StdLogicVector to perform the AND operation with.
 * @return The result of the bitwise AND operation.
 */
StdLogicVector & StdLogicVector::And(const StdLogicVector & _operand) {
  mpz_and(value_, value_, _operand.getValue());
  return *this;
}

/**
 * @brief Bitwise OR operation.
 * @param _operand The StdLogicVector to perform the OR operation with.
 * @return The result of the bitwise OR operation.
 */
StdLogicVector & StdLogicVector::Or(const StdLogicVector & _operand) {
  mpz_ior(value_, value_, _operand.getValue());
  return *this;
}

/**
 * @brief Bitwise XOR operation.
 * @param _operand The StdLogicVector to perform the XOR operation with.
 * @return The result of the bitwise XOR operation.
 */
StdLogicVector & StdLogicVector::Xor(const StdLogicVector & _operand) {
  mpz_xor(value_, value_, _operand.getValue());
  return *this;
}

/**
 * @brief Addition of another StdLogicVector. Per default, the resulting
 *   StdLogicVector will have the same @a length_ as the original one. If this
 *   is not the desired behavior, call the overloaded function and do not
 *   truncate the carry.
 * @param _operand The StdLogicVector to perform the addition with.
 * @return The sum of the two StdLogicVectors.
 */
StdLogicVector & StdLogicVector::Add(const StdLogicVector & _operand) {
	return this->Add(_operand, true);
}

/**
 * @brief Addition of another StdLogicVector.
 * @param _operand The StdLogicVector to perform the addition with.
 * @param _truncateCarry Determines whether to truncate the carry of the sum.
 *   If @c true, the sum will have the length as the original StdLogicVector.
 *   If @c false, the sum will have the length of the original StdLogicVector
 *   plus one bit (length_ + 1).
 * @return The sum of the two StdLogicVectors.
 */
StdLogicVector & StdLogicVector::Add(const StdLogicVector & _operand,
		bool _truncateCarry) {
  mpz_add(value_, value_, _operand.getValue());
  if ( _truncateCarry ){
  	// Length should be kept the same as the original StdLogicVector. Thus,
  	// truncate a potential carry.
  	this->And(StdLogicVector(Ones(length_), 2, length_));
  } else {
  	// Resulting StdLogicVector (sum) may have increased by one bit. Thus,
  	// also increase its length.
  	length_ = length_ + 1;
  }

  return *this;
}

/**
 * @brief Truncates the StdLogicVector after @p _width bits.
 * @param _width Number of preserved bits (others will be truncated).
 * @return The truncated StdLogicVector.
 * @todo Error handling when size of StdLogicVector is smaller than @p _width.
 */
StdLogicVector & StdLogicVector::TruncateAfter(int _width) {
	StdLogicVector tmp(Ones(_width), 2, _width);
	length_ = _width;
	this->And(tmp);
	return *this;
}

/**
 * @brief Replaces a number of bits within the current StdLogicVector with
 *   another StdLogicVector.
 *
 * @param _begin The 0-based index of the first bit to be replaced. If this
 *   value is smaller than 0, the replacement will start at the 0th bit.
 * @param _input The StdLogicVector which should be used as a replacement. If
 *   size(@p _input) + @p _begin} exceeds size(this), only the first
 *   size(this)- @p _begin bits of this will be replaced.
 * @return A StdLogicVector where some bits have been replaced by those of
 *   another StdLogicVector.
 */
StdLogicVector & StdLogicVector::ReplaceBits(int _begin, const StdLogicVector & _input) {
	// Determine which bits have to be masked.
	string leadingOnes = Ones(max(length_ - (_begin + _input.getLength()), 0));
	string intermediateZeroes = Zeros(min(_input.getLength(), length_));
	string trailingOnes = Ones(max(length_ - static_cast<int>(leadingOnes.length())
			- _input.getLength(), 0));

	// Create a mask for the bits to be replaces.
	StdLogicVector tmp = StdLogicVector(
			(leadingOnes + intermediateZeroes + trailingOnes), 2, length_);

	// Clear the bits to be replaced.
	this->And(tmp);

	// Generate the replacement bit vector.
	tmp = StdLogicVector((Zeros(leadingOnes.length()) +
			_input.ToString(2,true) + Zeros(trailingOnes.length())), 2, length_);

	// Replace the previously cleared bits with those from the replacement bit
	// vector.
	return this->Or(tmp);
}

/**
 * @brief Appends zeroes on the right of the StdLogicVector in order to reach a
 *   certain with of @p _width bits.
 *
 * @param _width The target width of the StdLogicVector.
 * @return The StdLogicVector padded with @p _width - @a length_ zeros on the
 *   right.
 *
 * Appends zeroes on the right of the StdLogicVector in order to reach a
 * certain width of @p _bits bits. If @p _bits is smaller than the @a length_
 * of the current StdLogicVector, @c this will be returned.
 */
StdLogicVector & StdLogicVector::PadRightZeros(int _width) {
	if ( _width < length_ ) {
		//TODO: Throw error.
	}
	this->ShiftLeft(_width - length_);
	length_ = _width;

	return *this;
}


// ****************************************************************************
// Utility functions
// ****************************************************************************
string StdLogicVector::Zeros(int _length) {
  return string(_length, '0');
}

string StdLogicVector::Ones(int _length) {
  return string(_length,'1');
}
