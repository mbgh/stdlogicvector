/******************************************************************************
 *
 * Unit tests for the StdLogicVector class.
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
 * @file StdLogicVectorTest.cpp
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 06 August 2014
 * @brief Unit tests for the StdLogicVector class
 * @version 0.1
 *
 * This file contains several unit tests for the StdLogicVector class based on
 * the Google C++ Testing Framework.
 */

// Macro determining that the following code should only be run during the unit
// testing of the shared library.
#ifdef TEST_

#include <string>
#include "limits.h"

#include "StdLogicVector.h"
#include "gtest/gtest.h"

using namespace std;


// ****************************************************************************
// Constructor Tests
// ****************************************************************************
class StdLogicVectorTestConstructors : public ::testing::Test{
protected:
	// Variables to be used throughout the tests.
	StdLogicVector dut_;
	unsigned int length_;             // Length to be assigned to the StdLogicVector.
	unsigned long long int value_;		// Value to be assigned to the StdLogicVector.
};

// Test StdLogicVector::StdLogicVector() constructor.
TEST_F(StdLogicVectorTestConstructors, ConstructorDefault) {
	dut_ = StdLogicVector();
	// Check that both the result as well as the size of the result are correct.
	EXPECT_EQ(0, dut_.ToULL());
	EXPECT_EQ(0, dut_.getLength());
};

// Test StdLogicVector::StdLogicVector(_length) constructor.
TEST_F(StdLogicVectorTestConstructors, ConstructorLength) {
	length_ = 64;
	dut_ 		= StdLogicVector(length_);
	// Check that both the result as well as the size of the result are correct.
	EXPECT_EQ(0, dut_.ToULL());
	EXPECT_EQ(length_, dut_.getLength());
};

// Test StdLogicVector::StdLogicVector(_value, _length) constructor.
TEST_F(StdLogicVectorTestConstructors, ConstructorValueLength) {
	length_ = 64;
	value_ 	= 453562;
	dut_ 		= StdLogicVector(value_, length_);
	// Check that both the result as well as the size of the result are correct.
	EXPECT_EQ(value_, dut_.ToULL());
	EXPECT_EQ(length_, dut_.getLength());
};

// Test StdLogicVector::StdLogicVector(_value, _base, _length) constructor.
TEST_F(StdLogicVectorTestConstructors, ConstructorValueBaseLength) {
	string value;
	int base;

	length_ = 128;
	value		= "AA";
	base 		= 16;
	dut_ 		= StdLogicVector(value, base, length_);

	// Check that both the result as well as the size of the result are correct.
	EXPECT_EQ(170, dut_.ToULL());
	EXPECT_EQ(length_, dut_.getLength());

	length_ = 13;
	value		= "1010001110101";
	base 		= 2;
	dut_ 		= StdLogicVector(value, base, length_);

	// Check that both the result as well as the size of the result are correct.
	EXPECT_EQ(5237, dut_.ToULL());
	EXPECT_EQ(length_, dut_.getLength());
};

// Test StdLogicVector::StdLogicVector(_value, _size, _length) constructor.
TEST_F(StdLogicVectorTestConstructors, ConstructorByteArray) {

	// Test case 1: Value = 0
	unsigned char value1 [8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	length_ = 64;
	dut_ 		= StdLogicVector(value1, 8, length_);

	// Check that both the result as well as the size of the result are correct.
	EXPECT_EQ(0, dut_.ToULL());
	EXPECT_EQ(length_, dut_.getLength());

	// Test case 2: Value = 0xABCD
	unsigned char value2 [8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xCD};
	length_ = 64;
	dut_ 		= StdLogicVector(value2, 8, length_);

	// Check that both the result as well as the size of the result are correct.
	// ABCD(hex) = 43981(dec)
	EXPECT_EQ(43981, dut_.ToULL());
	EXPECT_EQ(length_, dut_.getLength());

	// Test case 3: Value = 0x37BC2013ADE74CAA11204
	unsigned char value3 [16] = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x7B, 0xC2,
			0x01, 0x3A, 0xDE, 0x74, 0xCA, 0xA1, 0x12, 0x04};
	length_ = 128;
	dut_ 		= StdLogicVector(value3, 16, length_);

	// Check that both the result as well as the size of the result are correct.
	// 37BC2013ADE74CAA11204(hex) = 4211207293214889422688772(dec)
	EXPECT_EQ("4211207293214889422688772", dut_.ToString(10,false));
	EXPECT_EQ(length_, dut_.getLength());
};


// ****************************************************************************
// Utility Function Tests
// ****************************************************************************
TEST(StdLogicVectorUtils, ToULL) {
	StdLogicVector inp = StdLogicVector("1100110011001100", 2, 16);
	EXPECT_EQ(52428, inp.ToULL());
};

// Test the StdLogicVector::ToString() function.
TEST(StdLogicVectorUtils, ToString) {

	StdLogicVector dut;
	string expOutp, actOutp;

	// Test case 1
	dut 		= StdLogicVector(21, 8);
	expOutp = "21";
	actOutp	= dut.ToString();
	EXPECT_EQ(expOutp, actOutp);

	// Test case 2
	dut 		= StdLogicVector(21, 8);
	expOutp = "21";
	actOutp	= dut.ToString(false);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 3
	dut 		= StdLogicVector(21, 8);
	expOutp = "021";
	actOutp	= dut.ToString(true);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 4
	dut 		= StdLogicVector(21, 8);
	expOutp = "10101";
	actOutp	= dut.ToString(2);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 5
	dut 		= StdLogicVector(21, 8);
	expOutp = "00010101";
	actOutp	= dut.ToString(2, true);
	EXPECT_EQ(expOutp, actOutp);
}

// Test the StdLogicVector::ToString() function.
TEST(StdLogicVectorUtils, ToByteArray) {

	StdLogicVector dut;
	unsigned char expOutp[4] = {
			0xA0, 0xB1, 0xC2, 0xD3 };
	unsigned char actOutp[4];

	// Test case 1
	dut 		= StdLogicVector("A0B1C2D3", 16, 32);
	dut.ToByteArray(actOutp);
	EXPECT_EQ(expOutp[0], actOutp[0]);
}


// ****************************************************************************
// Comparison Operators Tests
// ****************************************************************************
// Test the equality operator ("==").
TEST(StdLogicVectorOperators, Equality) {

	StdLogicVector inp1, inp2;

	// Test case 1
	inp1	= StdLogicVector();
	inp2	= StdLogicVector();
	EXPECT_EQ(inp1, inp2);

	// Test case 2
	inp1	= StdLogicVector(16);
	inp2	= StdLogicVector(16);
	EXPECT_EQ(inp1, inp2);

	// Test case 3
	inp1	= StdLogicVector(546, 32);
	inp2	= StdLogicVector(546, 32);
	EXPECT_EQ(inp1, inp2);

	// Test case 4
	inp1	= StdLogicVector("1000", 2, 4);
	inp2	= StdLogicVector(8, 4);
	EXPECT_EQ(inp1, inp2);

	// Test case 5
	inp1	= StdLogicVector("1100110011001100", 2, 16);
	inp2	= StdLogicVector(52428, 16);
	EXPECT_EQ(inp1, inp2);

	// Test case 6
	inp1	= StdLogicVector("1100110011001100", 2, 16);
	inp2	= StdLogicVector("CCCC", 16, 16);
	EXPECT_EQ(inp1, inp2);

	// Test case 7
	inp1	= StdLogicVector("1100110011001100", 2, 16);
	inp2	= StdLogicVector("52428", 10, 16);
	EXPECT_EQ(inp1, inp2);
}

// Test the inequality operator ("!=").
TEST(StdLogicVectorOperators, Inequality) {

	StdLogicVector inp1, inp2, expOutp, actOutp;

	// Test case 1
	inp1	= StdLogicVector();
	inp2	= StdLogicVector(16);
	EXPECT_NE(inp1, inp2);

	// Test case 2
	inp1	= StdLogicVector(7);
	inp2	= StdLogicVector(15);
	EXPECT_NE(inp1, inp2);

	// Test case 3
	inp1	= StdLogicVector(545, 32);
	inp2	= StdLogicVector(546, 32);
	EXPECT_NE(inp1, inp2);

	// Test case 4
	inp1	= StdLogicVector(546, 16);
	inp2	= StdLogicVector(546, 32);
	EXPECT_NE(inp1, inp2);

	// Test case 5
	inp1	= StdLogicVector("1000", 2, 4);
	inp2	= StdLogicVector(7, 4);
	EXPECT_NE(inp1, inp2);

	// Test case 6
	inp1	= StdLogicVector("1100110011001100", 2, 16);
	inp2	= StdLogicVector(52427, 16);
	EXPECT_NE(inp1, inp2);

	// Test case 7
	inp1	= StdLogicVector("1100110011001100", 2, 16);
	inp2	= StdLogicVector("1100110011001100", 2, 32);
	EXPECT_NE(inp1, inp2);

	// Test case 8
	inp1	= StdLogicVector("1100110011001100", 2, 32);
	inp2	= StdLogicVector("CCCC", 16, 16);
	EXPECT_NE(inp1, inp2);

	// Test case 9
	inp1	= StdLogicVector("1100110011001100", 2, 16);
	inp2	= StdLogicVector("2428", 10, 16);
	EXPECT_NE(inp1, inp2);
}


// ****************************************************************************
// Unary Operator Tests
// ****************************************************************************
class StdLogicVectorTestUnaryOperators : public ::testing::Test{
protected:
	// Variables to be used throughout the tests.
	StdLogicVector dut_;
	int randOps_; 		                // Number of operations to perform with random inputs.
	unsigned long long int inp_;			// Input value to the bitwise operation.
	unsigned long long int expOutp_;	// Expected output value from the bitwise operation.
	unsigned long long int actOutp_;	// Actual output value from the bitwise operation.

	StdLogicVectorTestUnaryOperators() {
		// Determine the number of operations to be performed with random inputs.
		randOps_ = 10;
	}
};

// Test StdLogicVector::ShiftLeft() with some random input values.
TEST_F(StdLogicVectorTestUnaryOperators, ShiftLeftRandomInputs) {

	if (sizeof(int) < sizeof(long)) {
		// It is most likely that "int" is smaller on your system than "long". So,
		// generate two random "ints" and concatenate them to a single "long".
		int bitShift;

		for (int i = 0; i < randOps_; ++i) {
			bitShift = rand() % 64;           // Number of bits to be shifted.

			inp_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());

			expOutp_  = inp_ << bitShift;
			dut_      = StdLogicVector(inp_, 64);
			actOutp_  = dut_.ShiftLeft(bitShift).ToULL();

			// Check that both the result as well as the size of the result are
			// correct.
			EXPECT_EQ(expOutp_, actOutp_);
			EXPECT_EQ(64, dut_.getLength());
		}
	}
};

// Test StdLogicVector::ShiftRight() with some random input values.
TEST_F(StdLogicVectorTestUnaryOperators, ShiftRightRandomInputs) {

	if (sizeof(int) < sizeof(long)) {
		// It is most likely that "int" is smaller on your system than "long". So,
		// generate two random "ints" and concatenate them to a single "long".
		int bitShift;
		StdLogicVector dut;

		for (int i = 0; i < randOps_; ++i) {
			bitShift = rand() % 64;           // Number of bits to be shifted.

			inp_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());

			expOutp_  = inp_ >> bitShift;
			dut_      = StdLogicVector(inp_, 64);
			actOutp_  = dut_.ShiftRight(bitShift).ToULL();
			EXPECT_EQ(expOutp_, actOutp_);
		}
	}
};


// ****************************************************************************
// Binary Operator Tests
// ****************************************************************************
class StdLogicVectorTestBinaryOperators : public ::testing::Test{
protected:
	// Variables to be used throughout the tests.
	int randOps_; 			              // Number of operations to perform with random inputs.
	unsigned long long int inp1_;			// First input value to the bitwise operation.
	unsigned long long int inp2_;			// Second input value to the bitwise operation.
	unsigned long long int expOutp_;	// Expected output value from the bitwise operation.
	StdLogicVector actOutp_;					// Actual output value from the bitwise operation.
	StdLogicVector inp1Std_;
	StdLogicVector inp2Std_;

	StdLogicVectorTestBinaryOperators() {
		// Determine the number of operations to be performed with random inputs.
		randOps_ = 10;
	}
};

// Tests some special cases of the StdLogicVector::And() function.
TEST_F(StdLogicVectorTestBinaryOperators, AndSpecialCases) {
	// And with minimum and maximum values of unsigned long long ints.
	inp1_ 		= 0;
	inp2_ 		= ULLONG_MAX;
	expOutp_ 	= inp1_ & inp2_;
	inp1Std_	= StdLogicVector(inp1_, 64);
	inp2Std_	= StdLogicVector(inp2_, 64);
	actOutp_	= inp1Std_.And(inp2Std_).ToULL();
	EXPECT_EQ(expOutp_, actOutp_.ToULL());
	EXPECT_EQ(64, inp1Std_.getLength());

	// And with two maximum values.
	inp1_ 		= ULLONG_MAX;
	inp2_ 		= ULLONG_MAX;
	expOutp_ 	= inp1_ & inp2_;
	inp1Std_	= StdLogicVector(inp1_, 64);
	inp2Std_	= StdLogicVector(inp2_, 64);
	actOutp_	= inp1Std_.And(inp2Std_);
	EXPECT_EQ(expOutp_, actOutp_.ToULL());
	EXPECT_EQ(64, inp1Std_.getLength());
}

// Test StdLogicVector::And() with some random input values.
TEST_F(StdLogicVectorTestBinaryOperators, AndRandomInputs) {
	if (sizeof(int) < sizeof(long)) {
		// It is most likely that "int" is smaller on your system than "long". So,
		// generate two random "ints" and concatenate them to a single "long" in
		// order to use them as random test inputs.
		for (int i = 0; i < randOps_; ++i) {
			inp1_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());
			inp2_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());

			expOutp_	= inp1_ & inp2_;
			inp1Std_	= StdLogicVector(inp1_, 64);
			inp2Std_	= StdLogicVector(inp2_, 64);
			actOutp_	= inp1Std_.And(inp2Std_);

			// Check that both the result as well as the size of the result are
			// correct.
			EXPECT_EQ(expOutp_, actOutp_.ToULL());
			EXPECT_EQ(64, inp1Std_.getLength());
		}
	}
}

// Tests some special cases of the StdLogicVector::Or() function.
TEST_F(StdLogicVectorTestBinaryOperators, OrSpecialCases) {
	// Or with minimum and maximum values of unsigned long long ints.
	inp1_ 		= 0;
	inp2_ 		= ULLONG_MAX;
	expOutp_ 	= inp1_ | inp2_;
	inp1Std_	= StdLogicVector(inp1_, 64);
	inp2Std_  = StdLogicVector(inp2_, 64);
	actOutp_	= inp1Std_.Or(inp2Std_);
	EXPECT_EQ(expOutp_, actOutp_.ToULL());
	EXPECT_EQ(64, inp2Std_.getLength());

	// And with two maximum values.
	inp1_ 		= ULLONG_MAX;
	inp2_ 		= ULLONG_MAX;
	expOutp_ 	= inp1_ | inp2_;
	inp1Std_	= StdLogicVector(inp1_, 64);
	inp2Std_	= StdLogicVector(inp2_, 64);
	actOutp_	= inp1Std_.Or(inp2Std_);
	EXPECT_EQ(expOutp_, actOutp_.ToULL());
	EXPECT_EQ(64, inp1Std_.getLength());
}

// Test StdLogicVector::Or() with some random input values.
TEST_F(StdLogicVectorTestBinaryOperators, OrRandomInputs) {
	if (sizeof(int) < sizeof(long)) {
		// It is most likely that "int" is smaller on your system than "long". So,
		// generate two random "ints" and concatenate them to a single "long" in
		// order to use them as random test inputs.
		for (int i = 0; i < randOps_; ++i) {
			inp1_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());
			inp2_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());

			expOutp_	= inp1_ | inp2_;
			inp1Std_	= StdLogicVector(inp1_, 64);
			inp2Std_	= StdLogicVector(inp2_, 64);
			actOutp_	= inp1Std_.Or(inp2Std_);

			// Check that both the result as well as the size of the result are
			// correct.
			EXPECT_EQ(expOutp_, actOutp_.ToULL());
			EXPECT_EQ(64, inp1Std_.getLength());
		}
	}
}

// Tests some special cases of the StdLogicVector::Xor() function.
TEST_F(StdLogicVectorTestBinaryOperators, XorSpecialCases) {
	// Or with minimum and maximum values of unsigned long long ints.
	inp1_ 		= 0;
	inp2_ 		= ULLONG_MAX;
	expOutp_ 	= inp1_ xor inp2_;
	inp1Std_ 	= StdLogicVector(inp1_, 64);
	inp2Std_	= StdLogicVector(inp2_, 64);
	actOutp_	= inp1Std_.Xor(inp2Std_);
	EXPECT_EQ(expOutp_, actOutp_.ToULL());
	EXPECT_EQ(64, inp2Std_.getLength());

	// And with two maximum values.
	inp1_ 		= ULLONG_MAX;
	inp2_ 		= ULLONG_MAX;
	expOutp_ 	= inp1_ xor inp2_;
	inp1Std_ 	= StdLogicVector(inp1_, 64);
	inp2Std_	= StdLogicVector(inp2_, 64);
	actOutp_	= inp1Std_.Xor(inp2Std_);
	EXPECT_EQ(expOutp_, actOutp_.ToULL());
	EXPECT_EQ(64, inp1Std_.getLength());

	inp2Std_ = inp1Std_.Xor(inp1Std_).And(inp2Std_);
}

// Test StdLogicVector::Or() with some random input values.
TEST_F(StdLogicVectorTestBinaryOperators, XorRandomInputs) {
	if (sizeof(int) < sizeof(long)) {
		// It is most likely that "int" is smaller on your system than "long". So,
		// generate two random "ints" and concatenate them to a single "long" in
		// order to use them as random test inputs.
		for (int i = 0; i < randOps_; ++i) {
			inp1_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());
			inp2_ = static_cast<unsigned long long>(rand()) << sizeof(int) * 8 |
					static_cast<unsigned long long>(rand());

			expOutp_	= inp1_ xor inp2_;
			inp1Std_	= StdLogicVector(inp1_, 64);
			inp2Std_	= StdLogicVector(inp2_, 64);
			actOutp_	= inp1Std_.Xor(inp2Std_);

			// Check that both the result as well as the size of the result are
			// correct.
			EXPECT_EQ(expOutp_, actOutp_.ToULL());
			EXPECT_EQ(64, inp1Std_.getLength());
		}
	}
}

// Test the StdLogicVector::Truncate() function.
TEST(StdLogicVectorOperations, TruncateBits) {

	StdLogicVector dut, expOutp, actOutp;
	int bits;

	// Test case 1
	dut  		= StdLogicVector("0101010101010101", 2, 16);
	bits 		= 5;
	expOutp = StdLogicVector("10101", 2, bits);
	actOutp	= dut.TruncateAfter(bits);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 2
	dut  		= StdLogicVector("1010111010100111", 2, 16);
	bits 		= 12;
	expOutp = StdLogicVector("111010100111", 2, bits);
	actOutp	= dut.TruncateAfter(bits);
	EXPECT_EQ(expOutp, actOutp);

}

// Test the StdLogicVector::ReplaceBits() function.
TEST(StdLogicVectorOperations, ReplaceBits) {

	StdLogicVector dut, repl, expOutp, actOutp;

	// Test case 1
	dut  		= StdLogicVector("0101010101010101", 2, 16);
	repl		=         StdLogicVector("11111111", 2, 8);
	expOutp = StdLogicVector("0101010111111111", 2, 16);
	actOutp	= dut.ReplaceBits(0, repl);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 2
	dut  		= StdLogicVector("0101010101010101", 2, 16);
	repl		=         StdLogicVector("1111", 2, 4);
	expOutp = StdLogicVector("0101010111110101", 2, 16);
	actOutp	= dut.ReplaceBits(4, repl);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 3
	dut  		= StdLogicVector("111111100000", 2, 12);
	repl		=      StdLogicVector("0011", 2, 4);
	expOutp = StdLogicVector("111110011000", 2, 12);
	actOutp	= dut.ReplaceBits(3, repl);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 4
	dut  		= StdLogicVector("010011001010001111", 2, 18);
	repl		=    StdLogicVector("10011110", 2, 8);
	expOutp = StdLogicVector("010100111100001111", 2, 18);
	actOutp	= dut.ReplaceBits(7, repl);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 5
	dut  		= StdLogicVector("10110010101", 2, 11);
	repl		= StdLogicVector("01001", 2, 5);
	expOutp = StdLogicVector("01001010101", 2, 11);
	actOutp	= dut.ReplaceBits(6, repl);
	EXPECT_EQ(expOutp, actOutp);
}

// Test the StdLogicVector::PadRightZeros() function.
TEST(StdLogicVectorOperations, PadRightZeros) {

	StdLogicVector dut, expOutp, actOutp;

	// Test case 1
	dut  	=         StdLogicVector("0101010101010101", 2, 16);
	expOutp = StdLogicVector("010101010101010100000000", 2, 24);
	actOutp	= dut.PadRightZeros(24);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 2
	dut  	=       StdLogicVector("01010101010101010101", 2, 20);
	expOutp = StdLogicVector("01010101010101010101000000", 2, 26);
	actOutp	= dut.PadRightZeros(26);
	EXPECT_EQ(expOutp, actOutp);
}

// Test the StdLogicVector::ReverseBitOrder() function.
TEST(StdLogicVectorOperations, ReverseBitOrder) {

	StdLogicVector dut, expOutp, actOutp;

	// Test case 1
	dut  	= StdLogicVector("11110000", 2, 8);
	expOutp = StdLogicVector("00001111", 2, 8);
	actOutp	= dut.ReverseBitOrder();
	EXPECT_EQ(expOutp, actOutp);

	// Test case 2
	dut  	= StdLogicVector("001100110011", 2, 12);
	expOutp = StdLogicVector("110011001100", 2, 12);
	actOutp	= dut.ReverseBitOrder();
	EXPECT_EQ(expOutp, actOutp);

	// Test case 3
	dut  	= StdLogicVector("111000111000111000111000111000111000", 2, 36);
	expOutp = StdLogicVector("000111000111000111000111000111000111", 2, 36);
	actOutp	= dut.ReverseBitOrder();
	EXPECT_EQ(expOutp, actOutp);

}

// ****************************************************************************
// Testing arithmetic functions.
// ****************************************************************************

// Test StdLogicVector::Add() with some special inputs.
TEST_F(StdLogicVectorTestBinaryOperators, AddSpecialInputs) {

	StdLogicVector inp1, inp2, expOutp, actOutp;

	// Test case 1
	inp1 		= StdLogicVector("00000000", 2, 8);
	inp2 		= StdLogicVector("00000000", 2, 8);
	expOutp	= StdLogicVector("00000000", 2, 8);
	actOutp	= inp1.Add(inp2);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 2
	inp1 		= StdLogicVector("00000001", 2, 8);
	inp2 		= StdLogicVector("00000001", 2, 8);
	expOutp	= StdLogicVector("00000010", 2, 8);
	actOutp	= inp1.Add(inp2);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 3
	inp1 		= StdLogicVector("01010101", 2, 8);
	inp2 		= StdLogicVector("01010101", 2, 8);
	expOutp	= StdLogicVector("10101010", 2, 8);
	actOutp	= inp1.Add(inp2);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 4
	inp1 		= StdLogicVector("10101010", 2, 8);
	inp2 		= StdLogicVector("10101010", 2, 8);
	expOutp	= StdLogicVector("01010100", 2, 8);
	actOutp	= inp1.Add(inp2);
	EXPECT_EQ(expOutp, actOutp);

	// Test case 5
	inp1 		=  StdLogicVector("10101010", 2, 8);
	inp2 		=  StdLogicVector("10101010", 2, 8);
	expOutp	= StdLogicVector("101010100", 2, 9);
	actOutp	= inp1.Add(inp2, false); // Do not truncate the carry bit.
	EXPECT_EQ(expOutp, actOutp);

};

// Test StdLogicVector::Add() with some random input values.
TEST_F(StdLogicVectorTestBinaryOperators, AddRandomInputs) {
	for (int i = 0; i < randOps_; ++i) {
		// Use to "ints" and add them to a long.
		inp1_ = rand();
		inp2_ = rand();

		expOutp_	= inp1_ + inp2_;
		inp1Std_	= StdLogicVector(inp1_, 32);
		inp2Std_	= StdLogicVector(inp2_, 32);
		actOutp_	= inp1Std_.Add(inp2Std_);

		// Check that both the result as well as the size of the result are correct.
		EXPECT_EQ(expOutp_, actOutp_.ToULL());
		EXPECT_EQ(32, inp1Std_.getLength());
		}
}


// ****************************************************************************
// Main function initiating all tests previously set up.
// ****************************************************************************
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif /* TEST_ */
