/******************************************************************************
 *
 * Unit tests for the StdLogicVector class.
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


// ****************************************************************************
// Comparison Operators Tests
// ****************************************************************************
// Test the equality operator ("==").
TEST(StdLogicVectorOperators, Equality) {

	StdLogicVector inp1, inp2, expOutp, actOutp;

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


// ****************************************************************************
// Testing other member functions.
// ****************************************************************************

// Test the StdLogicVector::ToString() function.
TEST(StdLogicVectorUtils, ToString) {

	StdLogicVector dut;
	string expOutp, actOutp;

	// Test case 1
	dut  		= StdLogicVector(12, 8);
	expOutp = "00001100";
	actOutp	= dut.ToString(2,true);
	EXPECT_EQ(expOutp, actOutp);
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


// ****************************************************************************
// Main function initiating all tests previously set up.
// ****************************************************************************
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif /* TEST_ */
