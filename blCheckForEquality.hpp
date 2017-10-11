#ifndef BL_CHECKFOREQUALITY_HPP
#define BL_CHECKFOREQUALITY_HPP



//-------------------------------------------------------------------
// FILE:            blCheckForEquality.hpp
//
//
//
// PURPOSE:         Generic functions check whether two buffers
//                  are equal or whether they are partially equal
//                  to each other.
//
//                  -- For the partially equal check, the functions
//                     check if the "bufferToCheck" is entirily
//                     contained within the "bufferToCheckAgainst"
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
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function checks
// two buffers to see if they are
// partially equal
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType>

inline bool isPartiallyEqual(blBuffer1IteratorType beginOfBufferToCheck,
                             const blBuffer1IteratorType& endOfBufferToCheck,
                             blBuffer2IteratorType beginOfBufferToCheckAgainst,
                             const blBuffer2IteratorType& endOfBufferToCheckAgainst)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer or
    // until two elements
    // don't match

    while((beginOfBufferToCheck != endOfBufferToCheck) &&
          (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst))
    {
        if(!(*beginOfBufferToCheck == *beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // If the first buffer
    // hasn't reached its
    // end, then it's not
    // partially equal

    if(beginOfBufferToCheck != endOfBufferToCheck)
        return false;
    else
        return true;
}



template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blPredicateFunctorType>
inline bool isPartiallyEqual(blBuffer1IteratorType beginOfBufferToCheck,
                             const blBuffer1IteratorType& endOfBufferToCheck,
                             blBuffer2IteratorType beginOfBufferToCheckAgainst,
                             const blBuffer2IteratorType& endOfBufferToCheckAgainst,
                             const blPredicateFunctorType& predicateFunctor)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer or
    // until two elements
    // don't match

    while((beginOfBufferToCheck != endOfBufferToCheck) &&
          (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst))
    {
        if(!predicateFunctor(*beginOfBufferToCheck,*beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // If the first buffer
    // hasn't reached its
    // end, then it's not
    // partially equal

    if(beginOfBufferToCheck != endOfBufferToCheck)
        return false;
    else
        return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions check if
// two buffers are equal
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType>

inline bool isEqual(blBuffer1IteratorType beginOfBufferToCheck,
                    const blBuffer1IteratorType& endOfBufferToCheck,
                    blBuffer2IteratorType beginOfBufferToCheckAgainst,
                    const blBuffer2IteratorType& endOfBufferToCheckAgainst)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer.
    // If we don't reach
    // the ends of both
    // buffers at the same
    // time, then they are
    // not equal

    while( (beginOfBufferToCheck != endOfBufferToCheck) &&
           (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst) )
    {
        if(!(*beginOfBufferToCheck == *beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // Let's make sure that
    // the ends of both
    // buffers have been
    // reached, otherwise
    // we return false.

    if( (beginOfBufferToCheck == endOfBufferToCheck) &&
        (beginOfBufferToCheckAgainst == endOfBufferToCheckAgainst) )
    {
        return true;
    }
    else
    {
        return false;
    }
}



template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blPredicateFunctorType>

inline bool isEqual(blBuffer1IteratorType beginOfBufferToCheck,
                    const blBuffer1IteratorType& endOfBufferToCheck,
                    blBuffer2IteratorType beginOfBufferToCheckAgainst,
                    const blBuffer2IteratorType& endOfBufferToCheckAgainst,
                    const blPredicateFunctorType& predicateFunctor)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer.
    // If we don't reach
    // the ends of both
    // buffers at the same
    // time, then they are
    // not equal

    while( (beginOfBufferToCheck != endOfBufferToCheck) &&
           (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst) )
    {
        if(!predicateFunctor(*beginOfBufferToCheck,*beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // Let's make sure that
    // the ends of both
    // buffers have been
    // reached, otherwise
    // we return false.

    if( (beginOfBufferToCheck == endOfBufferToCheck) &&
        (beginOfBufferToCheckAgainst == endOfBufferToCheckAgainst) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CHECKFOREQUALITY_HPP
