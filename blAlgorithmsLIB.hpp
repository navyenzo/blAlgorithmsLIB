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
