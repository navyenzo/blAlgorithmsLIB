#ifndef BL_LIBRARYOFBABEL_HPP
#define BL_LIBRARYOFBABEL_HPP



//-------------------------------------------------------------------
// FILE:            blLibraryOfBabel.hpp
//
//
//
// PURPOSE:         Functions that calculate the page number of a string
//                  and the corresponding string from a given page number.
//
//                  -- The page number would correspond to the string's
//                     position in a theoretical library big enough to hold
//                     all the knowledge that could ever be expressed
//                     using the number of characters in the string
//
//                  -- This is like an example of a "Library of Babel"
//                  -- Each string has a unique page number
//                  -- The functions are NOT case sensitive
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
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes needed for this file
//-------------------------------------------------------------------

// Needed to carry out mathematical computations

#include <math.h>
#include <string>

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function calculates the
// page number of a string.
// The page number would correspond to the string's
// position in a theoretical library big enough to hold
// all the knowledge that could ever be expressed
// using the number of characters in the string
//
// This is like an example of a "Library of Babel"
//
// Each string has a unique page number
// The function is NOT case sensitive
//
// The calculation expects the number type to be
// an arbitrary precision number big enough to be
// able to hold all the possible combinations of
// the alphabet being considered
//
// As of now, the calcultion uses a base 29 to
// represent the 26 letters of the english alphabet
// plus the space, point and comma
//-------------------------------------------------------------------
template<typename numberType>

void calculatePageNumber(const std::string& textInput,
                         numberType& pageNumber)
{
    // This calculation is based
    // on the following:

    // space = 0
    // point = 1
    // comma = 2
    // 'A' thru 'Z' and 'a' thru 'z' = 3 thru 28
    // anything else for now = 0 (space)

    pageNumber = 0;
    numberType currentCharacterValue(0);
    numberType base = numberType(29);

    for(unsigned int i = 0; i < textInput.size(); ++i)
    {
        if(textInput[i] >= 'A' && textInput[i] <= 'Z')
            currentCharacterValue = numberType(static_cast<int>(textInput[i]) - static_cast<int>('A') + static_cast<int>(3)) * std::pow(base,i);

        else if(textInput[i] >= 'a' && textInput[i] <= 'z')
            currentCharacterValue = numberType(static_cast<int>(textInput[i]) - static_cast<int>('a') + static_cast<int>(3)) * std::pow(base,i);

        else if(textInput[i] == '.')
            currentCharacterValue =  pow(base,i);

        else if(textInput[i] == ',')
            currentCharacterValue = numberType(2) * pow(base,i);

        else
            currentCharacterValue = 0;


        pageNumber += currentCharacterValue;
    }

    return;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function calculates the string
// corresponding to a page number, the inverse
// calculation of the above function
//-------------------------------------------------------------------
template<typename numberType,
         typename stringIteratorType>

void calculateStringFromPageNumber(const numberType& pageNumber,
                                   const stringIteratorType& textBeginIterator,
                                   const stringIteratorType& textEndIterator)
{
    if(textBeginIterator == textEndIterator)
    {
        // We have no string to write
        // the result into

        return;
    }

    // This function calculates the string
    // from a page number using a base 29
    // system

    // The base 29 system is represented as follows:
    // ' ' -- space character = 0
    // '.' -- point character = 1
    // ',' -- comma character = 2
    // 'A' thru 'Z' and 'a' thru 'z' -- alphabetical characters = 3 thru 29

    // First let's save the current
    // iterators

    auto iterator = textBeginIterator;

    // Now let's create the necessary
    // variables needed to convert the
    // page number

    numberType quotient = pageNumber;
    char remainder = 0;
    numberType divisor = numberType(29);
    numberType zero = numberType(0);

    do
    {
        // Calculate the quotient and remainder

        remainder = static_cast<char>(quotient % divisor);
        quotient = quotient / divisor;

        // Convert the remainder to
        // the string character

        switch(remainder)
        {
        case 0:
            (*iterator) = ' ';
            break;
        case 1:
            (*iterator) = '.';
            break;
        case 2:
            (*iterator) = ',';
            break;
        default:
            (*iterator) = remainder - static_cast<char>(3) + 'a';
            break;
        }

        // Move on to the next
        // string position

        ++iterator;

    }
    while((iterator != textEndIterator) && (quotient > zero));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_LIBRARYOFBABEL_HPP
