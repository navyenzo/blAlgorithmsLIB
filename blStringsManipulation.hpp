#ifndef BL_STRINGSMANIPULATION_HPP
#define BL_STRINGSMANIPULATION_HPP



//-------------------------------------------------------------------
// FILE:            blStringManipulation.hpp
//
//
//
// PURPOSE:         Functions useful in manipulating strings
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
// Includes needed for these functions
//-------------------------------------------------------------------
#include <string>
#include <algorithm>
#include "blCyclicStlAlgorithms.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to search for substrings in a user
// specified string
//-------------------------------------------------------------------
template<typename blContainerType,
         typename blStringType>

inline bool is_in_container(const blContainerType& container,
                            const blStringType& stringToSearchFor)
{
    return ( blAlgorithmsLIB::search(container.begin(),container.end(),stringToSearchFor.begin(),stringToSearchFor.end()) != container.end());
}



template<typename blContainerType,
         typename blStringType>

inline auto search_in_container(const blContainerType& container,
                                const blStringType& stringToSearchFor)
{
    return blAlgorithmsLIB::search(container.begin(),container.end(),stringToSearchFor.begin(),stringToSearchFor.end());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to know whether a container starts/ends
// with a specified string
//-------------------------------------------------------------------
template<typename blContainerType,
         typename blStringType>

inline bool starts_with(const blContainerType& container,
                        const blStringType& stringToSearchFor)
{
    return blAlgorithmsLIB::is_partially_equal(container.begin(),
                                               container.end(),
                                               stringToSearchFor.begin(),
                                               stringToSearchFor.end());
}



template<typename blContainerType,
         typename blStringType>

inline bool ends_with(const blContainerType& container,
                      const blStringType& stringToSearchFor)
{
    if(container.size() < stringToSearchFor.size())
        return false;

    auto containerBeginIter = container.begin();
    std::advance(containerBeginIter,container.size() - stringToSearchFor.size());

    return blAlgorithmsLIB::is_partially_equal(containerBeginIter,
                                               container.end(),
                                               stringToSearchFor.begin(),
                                               stringToSearchFor.end());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to replace all substrings matching a user
// specified "old substring" with a user specified "new substring"
//-------------------------------------------------------------------
inline void findAndReplaceAllMatchingSubstrings(std::string& sourceString,
                                                const std::string& oldSubstring,
                                                const std::string& newSubstring)
{
    auto positionWhereOldSubstringWasFound = std::distance(sourceString.begin(),
                                                           std::search(sourceString.begin(),
                                                                       sourceString.end(),
                                                                       oldSubstring.begin(),
                                                                       oldSubstring.end()));

    auto endPosition = std::distance(sourceString.begin(),sourceString.end());



    while(positionWhereOldSubstringWasFound < endPosition)
    {
        sourceString.replace(positionWhereOldSubstringWasFound,oldSubstring.length(),newSubstring);



        endPosition = std::distance(sourceString.begin(),sourceString.end());

        positionWhereOldSubstringWasFound += newSubstring.size();



        positionWhereOldSubstringWasFound = std::distance(sourceString.begin(),
                                                          std::search(sourceString.begin() + positionWhereOldSubstringWasFound,
                                                                      sourceString.end(),
                                                                      oldSubstring.begin(),
                                                                      oldSubstring.end()));
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_STRINGSMANIPULATION_HPP
