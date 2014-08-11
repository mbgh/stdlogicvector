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


  // **************************************************************************
  // Getter/Setter functions
  // **************************************************************************
  mpz_t const & getValue() const;
  int getLength() const;

  unsigned long long ToULL();
  string ToString();
  string ToString(bool _pad);
  string ToString(int _base, bool _pad);
  string ToString(int _base, bool _pad) const;

  unsigned char * ToByteArray();


  // **************************************************************************
  // Comparison operators
  // **************************************************************************
  bool operator==(const StdLogicVector & _input) const;
  bool operator!=(const StdLogicVector & _input) const;


  // **************************************************************************
  // Bitwise operations
  // **************************************************************************
  int TestBit(int _index);

  StdLogicVector & ShiftLeft(int _bits);
  const StdLogicVector & ShiftLeft(int _bits) const;

  StdLogicVector & ShiftRight(int _bits);
  const StdLogicVector & ShiftRight(int _bits) const;

  StdLogicVector & And(StdLogicVector const & _operand);
  const StdLogicVector & And(StdLogicVector const & _operand) const;

  StdLogicVector & Or(StdLogicVector const & _operand);
	const StdLogicVector & Or(StdLogicVector const & _operand) const;

  StdLogicVector & Xor(StdLogicVector const & _operand);
  const StdLogicVector & Xor(StdLogicVector const & _operand) const;

  StdLogicVector & TruncateAfter(int _width);
  const StdLogicVector & TruncateAfter(int _width) const;

  StdLogicVector & ReplaceBits(int _begin, StdLogicVector const & _input);
  const StdLogicVector & ReplaceBits(int _begin, StdLogicVector const & _input) const;


  // **************************************************************************
  // Arithmetic operations
  // **************************************************************************
  StdLogicVector & Add(StdLogicVector _operand);
  const StdLogicVector & Add(StdLogicVector _operand) const;

};

#endif /* STDLOGICVECTOR_H_ */
