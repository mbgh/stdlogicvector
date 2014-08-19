################################################################################
CXX       = g++
NAME      = StdLogicVector
RM        = rm -f
GMP_HDR   = /usr/ela/home/michmueh/software/gmp/build/include
GMP_LIB   = /usr/ela/home/michmueh/software/gmp/build/lib
GTEST_HDR = /usr/ela/home/michmueh/software/gtest/gtest-1.7.0/include
GTEST_LIB = /usr/ela/home/michmueh/software/gtest/gtest-1.7.0/build
################################################################################

all: lib$(NAME).so

lib$(NAME).so: $(NAME).o
	$(CXX) -shared $(NAME).o -o lib$(NAME).so -L$(GMP_LIB) -lgmp -lgmpxx

$(NAME).o: $(NAME).cpp
	$(CXX) -c $(NAME).cpp -o $(NAME).o -fPIC -I$(GMP_HDR)

test: $(NAME)Test

$(NAME)Test: $(NAME)Test.o
	$(CXX) $(NAME)Test.o -o $(NAME)Test -L. -L$(GTEST_LIB) -L$(GMP_LIB) -lpthread -lgtest -lgmp -lStdLogicVector

$(NAME)Test.o: $(NAME)Test.cpp
	$(CXX) -c $(NAME)Test.cpp -o $(NAME)Test.o -D TEST_ -I. -I$(GMP_HDR) -I$(GTEST_HDR)

run:
	LD_LIBRARY_PATH=.:$(GMP_LIB):$(GTEST_LIB):$(LD_LIBRARY_PATH) ./$(NAME)Test

clean:
	@$(RM) *.o *.so $(NAME)Test