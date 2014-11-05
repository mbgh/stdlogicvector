/******************************************************************************
 *
 * An implementation of the std_logic_vector VHDL data type in C++
 * Copyright (C) 2014 ETHZ Zurich, Integrated Systems Laboratory
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
 * @file StdLogicVector.h
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 03 April 2014
 * @brief An implementation of the std_logic_vector VHDL data type in C++
 * @version 0.1
 *
 * In order to generate bit-true C++ models of future VHDL implementations,
 * this file provides an equivalent C++ class of the std_logic_vector data type
 * available in VHDL. Since the value of a StdLogicVector can be of arbitrary
 * length, its actual value is internally represented using the GMP library [1]
 * for arbitrary arithmetic functions.
 *
 * @see [1] https://gmplib.org/
 */

#ifndef STDLOGICVECTOR_H_
#define STDLOGICVECTOR_H_

#include <string>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

/**
 * @class StdLogicVector
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 03 April 2014
 * @brief An implementation of the std_logic_vector VHDL data type in C++
 * @version 0.1
 *
 * This class implements a C++ analogue to the VHDL std_logic_vector class.
 * Since the value of a StdLogicVector can be of arbitrary length, its actual
 * value is internally represented using the GMP library [1] for arbitrary
 * arithmetic functions. Therefore, this class represents kind of a wrapper
 * around the GMP library, which allows simple arithmetic as it is often used
 * when designing with VHDL or other hardware description languages.
 *
 * @see [1] https://gmplib.org/
 */
class StdLogicVector {

private:
	// **************************************************************************
	// Members
	// **************************************************************************
  mpz_t value_;
  int length_;

  // **************************************************************************
  // Utility functions
  // **************************************************************************
  string Zeros(int _length);
  string Ones(int _length);

public:
  // **************************************************************************
  // Constructors/Destructors
  // **************************************************************************
  StdLogicVector();
  StdLogicVector(unsigned int _length);
  StdLogicVector(unsigned long long _value, unsigned int _length);
  StdLogicVector(string _value, int _base, unsigned int _length);
  StdLogicVector(unsigned char *_value, int _size, unsigned int _length);
  virtual ~StdLogicVector();
  StdLogicVector (const StdLogicVector & _other);


  // **************************************************************************
  // Getter/Setter functions
  // **************************************************************************
  const mpz_t & getValue() const;
  int getLength() const;


  // **************************************************************************
  // Utility functions
  // **************************************************************************
  unsigned long long ToULL();
  unsigned long long ToULL() const;

  string ToString();
	string ToString(bool _pad);
	string ToString(int _base);
  string ToString(int _base) const;
  string ToString(int _base, bool _pad);
  string ToString(int _base, bool _pad) const;

  void ToByteArray(unsigned char _byteArray[]) const;

  // **************************************************************************
  // Operator overloadings
  // **************************************************************************
  bool operator==(const StdLogicVector & _input) const;
  bool operator!=(const StdLogicVector & _input) const;
  friend ostream & operator<<(ostream & _os, const StdLogicVector & _stdLogicVec);


  // **************************************************************************
  // Bitwise operations
  // **************************************************************************
  int TestBit(int _index) const;

  StdLogicVector & ShiftLeft(int _bits);
  StdLogicVector & ShiftRight(int _bits);
  StdLogicVector & And(const StdLogicVector & _operand);
  StdLogicVector & Or(const StdLogicVector & _operand);
  StdLogicVector & Xor(const StdLogicVector & _operand);

  StdLogicVector & TruncateAfter(int _width);
  StdLogicVector & ReplaceBits(int _begin, const StdLogicVector & _input);
  StdLogicVector & PadRightZeros(int _width);
  StdLogicVector & ReverseBitOrder();


  // **************************************************************************
  // Arithmetic operations
  // **************************************************************************
  StdLogicVector & Add(const StdLogicVector & _operand);
  StdLogicVector & Add(const StdLogicVector & _operand, bool _truncateCarry);
};

#endif /* STDLOGICVECTOR_H_ */
