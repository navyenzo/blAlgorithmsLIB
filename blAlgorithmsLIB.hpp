#ifndef BL_ALGORITHMSLIB_HPP
#define BL_ALGORITHMSLIB_HPP



//-------------------------------------------------------------------
// FILE:            blAlgorithmsLIB.hpp
//
//
//
// PURPOSE:         A collection of buffer parsing algorithms useful
//                  in extracting information from strings or generic
//                  data-streams / data-buffers
//
//                  -- All functions/algorithms are defined within
//                     the "blAlgorithmsLIB" namespace
//
//
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
//
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
//
//
// DEPENDENCIES:    c++98
//-------------------------------------------------------------------



//-------------------------------------------------------------------

// Generic function that simplify reading from a stream
// into a variable or a contiguous buffer and writing to
// a stream from a variable or a contiguous buffer

#include "blStreamReadWrite.hpp"



// Generic functions check whether two buffers
// are equal or whether they are partially equal
// to each other.

#include "blCheckForEquality.hpp"



// Cyclic versions of common stl-algorithms such
// as std::copy and std::find but with a parameter
// that allows a user to specify the maximum
// number of cycles when using cyclic iterators

#include "blCyclicStlAlgorithms.hpp"



// Counting algorithms useful that count "rows" and/or
// "columns" of data in generic data streams/buffers,
// as well as finding algorithms that find the beginning
// and/or end of a specified "row" and/or "column", that
// find the beginning and/or end of the "Nth" row and
// "Mth" column and more.

#include "blCountAndFind.hpp"



// Function used to convert a sequence of characters
// into a floating point number.
// The function accepts "begin" and "end" iterators
// and allows the user to specify the decimal point
// delimiter/token
// The function also return an iterator pointing to the
// place right after the last character used to convert
// to a number

#include "blConvertToNumber.hpp"



// Custom iterator useful in parsing serialized data
// from generic text-data streams (for ex. files) and
// turn it into a numeric matrix
//
// NOTE:  The iterator assumes that the text data is
//        formatted as a single column vector so that
//        it only contains one number per row, where
//        each row is separated by the '\n' newline
//        token

#include "blTextColumnVectorIterator.hpp"



// Another Custom iterator useful in parsing serialized
// data from generic text-data streams
//
// This iterator assumes the string is an (n x 1) column vector
// of values, representing data points, where each data point
// is a matrix of data of size (rows x cols), the string is assumed
// to be formatted as follows:
//
// Line 0 -- Serial number (a number representing a signature/type)
// Line 1 -- rows
// Line 2 -- cols
// Line 3 - Line n-1 -- The data points one matrix at a time
//
// NOTE:  If the matrix is a 2d matrix then the cols = 1, for 3d matrices
//        the cols > 1
//
// For example a (2xN) matrix would look like the following:
//
// 123454321 (some serial number)
// 2 (the rows in each data point)
// 1 (the columns in each data point, so this means each data point
//   is a single column vector of size (2x1)
// 0,0
// 1,0
// 2,0
// 0,1
// 1,1
// 2,1
// 0,2
// 1,2
// 2,2
// 0,3
// ...
// 2,N
// End of file

#include "blTextMatrixIterator.hpp"



// A custom iterator same as the above one
// but that works with binary data instead
// of text data
// During iteration the user can specify
// how this iterator advances through the
// user supplied binary data stream
// The user can specify the iterator to
// advance in the following ways:
// - column-major format (default)
// - row-major format
// - column-page-major format
// - row-page-major format

#include "blBinaryMatrixIterator.hpp"



// Functions that calculate the page number of a string
// and the corresponding string from a given page number
//
// -- The page number would correspond to the string's
//    position in a theoretical library big enough to hold
//    all the knowledge that could ever be expressed
//    using the number of characters in the string
//
// -- This is like an example of a "Library of Babel"
// -- Each string has a unique page number
// -- The functions are NOT case sensitive

#include "blLibraryOfBabel.hpp"

//-------------------------------------------------------------------



#endif // BL_ALGORITHMSLIB_HPP
