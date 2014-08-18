StdLogicVector
==============

An easy to use C++ class, offering arbitrary-precision integer arithmetic for
basic operations often required during the development of hardware designs. The
`StdLogicVector` class provides a wrapper around the [GMP](https://gmplib.org/)
library, which should simplify the development of software models for hardware
designers in the field of cryptographic applications.

Motivation
----------

When developing hardware designs in the field of cryptographic applications, it
is pretty common to work with large integers (128bits and way beyond). While
hardware description languages (HDLs), like
[VHDL](http://en.wikipedia.org/wiki/VHDL), provide arbitrary-precision
arithmetic based on data types such as `std_logic_vector` and the like, writing
software models for these designs often requires custom-made solutions or the
use of third party libraries.

In order to simplify the development of software models, I have put together the
`StdLogicVector` class, which is a small wrapper around the
[GMP](https://gmplib.org/) library, offering arbitrary-precision arithmetic for
operations frequently used in the design of hardware architectures (bit-wise
operations such as those of logic gates, arithmetic functions, etc.).

Example
-------

Everything, what can be done with the `StdLogicVector` class, can, of course,
also be done with plain [GMP](https://gmplib.org/) data types and its
functions. However, `StdLogicVector` offers a more intuitive application
(somewhat similar to the
[`BigInteger`](http://docs.oracle.com/javase/6/docs/api/java/math/BigInteger.html)
class of Java), which allows to concatenate operations like the following:

```cpp
// Create a four-bit integer 'a' with value 5 and an eight-bit integer 'b' with
// value 210, initialized using binary representation.
StdLogicVector a = StdLogicVector(5, 4);
StdLogicVector b = StdLogicVector("11010010", 2, 8);

// Perform some operations on 'b'.
b.ShiftRight(2).TruncateAfter(4).Xor(a);
```

Usage
-----
TBD

Documentation
-------------

A documentation of the `StdLogicVector` class, created using
[Doxygen](http://www.doxygen.org/), is available
[here](http://mbgh.github.io/stdlogicvector/).

##FAQ

A couple of questions, which came to my mind when setting up this readme file. 

#### Is the `StdLogicVector` class intended for any special purpose?

No, I have written the `StdLogicVector` class to simplify working with
arbitrary-precision integers **in general**, without having any special purpose
in mind. Therefore, you will most-likely miss some operations when using it for
your own needs.

#### Which is the "final" version of the `StdLogicVector` class?

There is nothing like a "final version" of this class. I am extending its
functionality depending on my personal needs (which again depend on the projects
I am currently working on), which is why there exists (and will most-likely
never exist) something like a "final" version.
