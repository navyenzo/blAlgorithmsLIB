#ifndef BL_CONVERTTONUMBER_HPP
#define BL_CONVERTTONUMBER_HPP



//-------------------------------------------------------------------
// FUNCTION:            convertToNumber
//
//
//
// ARGUMENTS:           - BeginIter
//                      - EndIter
//                      - DecimalPointDelimiter
//                      - ConvertedNumber
//
//
//
// TEMPLATE ARGUMENTS:  - blStringIteratorType
//                      - blCharacterType
//                      - blNumberType
//
//
//
// PURPOSE:             -- This function used to convert a sequence of
//                         characters into a floating point number
//
//                      -- The function accepts "begin" and "end" iterators
//                         and allows the user to specify the decimal point
//                         delimiter/token
//
//                      -- The function also return an iterator pointing to the
//                         place right after the last character used to convert
//                         to a number
//
//                      -- This Function is defined within the "blAlgorithmsLIB"
//                         namespace
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
// Includes and libs needed for this file
//-------------------------------------------------------------------
#include <cmath>
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>

inline blStringIteratorType convertToNumber(const blStringIteratorType& beginIter,
                                            const blStringIteratorType& endIter,
                                            const blCharacterType& decimalPointDelimiter,
                                            blNumberType& convertedNumber,
                                            const int& numberOfTimesToCycleIfIteratorIsCircular)
{
    // First we check
    // if the user
    // passed a zero
    // sized string

    if(beginIter == endIter)
    {
        // In this case
        // there's nothing
        // to convert so we
        // simply return

        return endIter;
    }

    // Initialize the
    // converted number

    convertedNumber = blNumberType(0);

    // Iterator used to
    // parse the string

    blStringIteratorType currentPos = beginIter;

    // Boolean to check
    // if the number is
    // negative

    bool isNumberNegative = false;

    // Boolean and
    // multiplier
    // used to handle
    // decimal point
    // digits

    bool hasDecimalPointBeenEncounteredAlready = false;
    blNumberType decimalPointMultiplier = blNumberType(1);

    // The first step
    // is to check the
    // first digit for
    // special characters

    if((*currentPos) == '-')
    {
        // This means the
        // number is negative

        isNumberNegative = true;

        // Advance the position

        ++currentPos;
    }
    else if((*currentPos) == '+')
    {
        // This means the
        // number is positive
        // so we simply advance
        // the position to the
        // next character

        ++currentPos;
    }
    else if((*currentPos) == decimalPointDelimiter)
    {
        // This means the
        // number starts with
        // a decimal point

        hasDecimalPointBeenEncounteredAlready = true;
        ++currentPos;
    }
    else if((*currentPos) == 'e' || (*currentPos) == 'E')
    {
        // In this case, the
        // first character of
        // the string is an 'e'
        // or 'E', which means
        // that the number is
        // an exponent.
        // Since it is the first
        // character, then the
        // number will be
        // 10^Exponent.
        // Therefore, we find
        // the exponent and
        // then raise 10
        // to its power

        ++currentPos;

        blNumberType exponent;

        blStringIteratorType newPos = convertToNumber(currentPos,
                                                      endIter,
                                                      decimalPointDelimiter,
                                                      exponent,
                                                      numberOfTimesToCycleIfIteratorIsCircular - 1);

        if(newPos == currentPos)
        {
            // We obviously
            // had no exponent
            // so we assume
            // that it was e0
            // or * 10^0, which
            // means it is 1

            convertedNumber = blNumberType(1);
            return currentPos;
        }
        else
        {
            // In this case,
            // we had a valid
            // exponent

            convertedNumber = blNumberType(std::pow(double(10),double(exponent)));
            currentPos = newPos;
        }

        return currentPos;
    }

    // Keep track of how
    // many times we go
    // over the BeginIter
    // in case of a circular
    // iterator

    int numberOfRepeats = 0;

    // Now we loop through
    // the remaining elements
    // of the string and
    // calculate the number
    // accordingly.

    // NOTE:    Remember that we
    //          are looping from
    //          left to right, so
    //          from the highest
    //          digit to the lowest
    //          value digit (numerically
    //          speaking)

    while((currentPos != endIter) &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCircular)
    {
        if((*currentPos) >= '0' && (*currentPos) <= '9')
        {
            // This means we
            // have a valid
            // numeric digit

            if(hasDecimalPointBeenEncounteredAlready)
            {
                // This means that
                // the digit is
                // after the decimal
                // point, so we add
                // the current digit
                // divided by its
                // place after the
                // decimal point

                decimalPointMultiplier *= blNumberType(10);
                convertedNumber = convertedNumber + blNumberType((*currentPos) - '0')/decimalPointMultiplier;
            }
            else
            {
                // This means that
                // the digit is before
                // the decimal point,
                // so we multiply the
                // current number by
                // 10 and add the new
                // digit

                convertedNumber = convertedNumber * blNumberType(10) + blNumberType((*currentPos) - '0');
            }
        }
        else if((*currentPos) == decimalPointDelimiter && !hasDecimalPointBeenEncounteredAlready)
        {
            // This means that
            // we have just found
            // the decimal point
            // so we just store the
            // fact that we found it
            // in the boolean

            hasDecimalPointBeenEncounteredAlready = true;
        }
        else if((*currentPos) == 'e' || (*currentPos) == 'E')
        {
            // In this case, it
            // means that we're
            // about to multiply
            // the current number
            // by 10^Exponent.
            // Thus, we find the value of the
            // exponent and then multiply

            // First we move
            // to the next
            // position in the
            // string (the one
            // after the 'e' or 'E')

            ++currentPos;

            // Then we calculate
            // the exponent by
            // recursively calling
            // this function

            blNumberType exponent;

            blStringIteratorType newPos = convertToNumber(currentPos,
                                                          endIter,
                                                          decimalPointDelimiter,
                                                          exponent,
                                                          numberOfTimesToCycleIfIteratorIsCircular - numberOfRepeats);

            if(newPos == currentPos)
            {
                // If the iterators
                // are equal, that
                // means that the
                // function did not
                // find a valid exponent.
                // In this case, we
                // assume the exponent
                // was zero and we
                // multiply the current
                // number by 10^0,
                // meaning multiply by 1.
                // So we are done
                break;
            }
            else
            {
                // In this case,
                // we had a valid
                // exponent, so
                // we multiply the
                // current number
                // by 10^Exponent

                convertedNumber = convertedNumber * blNumberType(std::pow(double(10),double(exponent)));

                currentPos = newPos;

                // We are done

                break;
            }
        }
        else
        {
            // In this case, we
            // found a non-valid
            // character, so we
            // are done

            break;
        }

        // Advance the
        // iterator

        ++currentPos;

        if(currentPos == beginIter)
            ++numberOfRepeats;
    }

    // Check if the number
    // is negative

    if(isNumberNegative)
        convertedNumber *= blNumberType(-1);

    // Now we return the
    // current position

    return currentPos;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CONVERTTONUMBER_HPP
