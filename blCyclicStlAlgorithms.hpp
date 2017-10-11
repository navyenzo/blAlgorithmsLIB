#ifndef BL_CYCLICSTLALGORITHMS_HPP
#define BL_CYCLICSTLALGORITHMS_HPP



//-------------------------------------------------------------------
// FILE:            blCyclicStlAlgorithms.hpp
//
//
//
// PURPOSE:         Cyclic versions of common stl-algorithms such
//                  as std::copy and std::find but with a parameter
//                  that allows a user to specify the maximum
//                  number of cycles when using cyclic iterators
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
// The following function copies content
// from input buffer to output buffer
// stopping whenever it reaches the end
// of either buffer
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blIntegerType>

inline blBuffer2IteratorType copy(const blBuffer1IteratorType& inputBegin,
                                  const blBuffer1IteratorType& inputEnd,
                                  const blBuffer2IteratorType& outputBegin,
                                  const blBuffer2IteratorType& outputEnd,
                                  const blIntegerType& numberOfTimesToCycleOverInputIfInputIteratorIsCyclic,
                                  const blIntegerType& numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic)
{
    auto currentInputIter = inputBegin;
    auto currentOutputIter = outputBegin;

    blIntegerType numberOfInputRepeats = 0;
    blIntegerType numberOfOutputRepeats = 0;

    while( (currentInputIter != inputEnd) &&
           (currentOutputIter != outputEnd) &&
           (numberOfInputRepeats <= numberOfTimesToCycleOverInputIfInputIteratorIsCyclic) &&
           (numberOfOutputRepeats <= numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic) )
    {
        (*currentOutputIter) = (*currentInputIter);

        ++currentInputIter;
        ++currentOutputIter;

        if(currentInputIter == inputBegin)
            ++numberOfInputRepeats;

        if(currentOutputIter == outputBegin)
            ++numberOfOutputRepeats;
    }

    return currentOutputIter;
}


template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blIntegerType>

inline blBuffer2IteratorType copy(const blBuffer1IteratorType& inputBegin,
                                  const blBuffer1IteratorType& inputEnd,
                                  const blBuffer2IteratorType& outputBegin,
                                  const blBuffer2IteratorType& outputEnd,
                                  const blIntegerType& numberOfTimesToCycleOverInputIfInputIteratorIsCyclic,
                                  const blIntegerType& numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic,
                                  blBuffer1IteratorType& inputBufferPlaceAfterLastCopiedElement)
{
    auto currentInputIter = inputBegin;
    auto currentOutputIter = outputBegin;

    blIntegerType numberOfInputRepeats = 0;
    blIntegerType numberOfOutputRepeats = 0;

    while( (currentInputIter != inputEnd) &&
           (currentOutputIter != outputEnd) &&
           (numberOfInputRepeats <= numberOfTimesToCycleOverInputIfInputIteratorIsCyclic) &&
           (numberOfOutputRepeats <= numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic) )
    {
        (*currentOutputIter) = (*currentInputIter);

        ++currentInputIter;
        ++currentOutputIter;

        if(currentInputIter == inputBegin)
            ++numberOfInputRepeats;

        if(currentOutputIter == outputBegin)
            ++numberOfOutputRepeats;
    }

    inputBufferPlaceAfterLastCopiedElement = currentInputIter;

    return currentOutputIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function searches for tokens
// in a buffer
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType>

inline blBufferIteratorType find(const blBufferIteratorType& beginIter,
                                 const blBufferIteratorType& endIter,
                                 const blTokenType& token,
                                 const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) == token)
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}


template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find(blBufferIteratorType beginIter,
                                 const blBufferIteratorType& endIter,
                                 const blTokenType& token,
                                 const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic,
                                 const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(predicateFunctor((*currentIter),token))
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions look for the
// last occurrence of a specified token
// in a buffer
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType>

inline blBufferIteratorType findLast(const blBufferIteratorType& beginIter,
                                     const blBufferIteratorType& endIter,
                                     const blTokenType& token,
                                     const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastOccurrence = currentIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) == token)
            iterToLastOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastOccurrence) == token)
        return iterToLastOccurrence;
    else
        return endIter;
}


template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType,
         typename blPredicateFunctorType>

inline blBufferIteratorType findLast(const blBufferIteratorType& beginIter,
                                     const blBufferIteratorType& endIter,
                                     const blTokenType& token,
                                     const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic,
                                     const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastOccurrence = currentIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(predicateFunctor(*currentIter,token))
            iterToLastOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastOccurrence) == token)
        return iterToLastOccurrence;
    else
        return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CYCLICSTLALGORITHMS_HPP
