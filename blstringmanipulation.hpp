#ifndef BL_STRINGMANIPULATION_HPP
#define BL_STRINGMANIPULATION_HPP



//-------------------------------------------------------------------
// FILE:            blStringManipulation.hpp
//
//
//
// PURPOSE:         // Functions useful in manipulating strings
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
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to replace all substrings matching a user
// specified "old substring" with a user specified "new substring"
//-------------------------------------------------------------------
inline void findAndReplaceAllMatchingSubstrings(std::string& sourceString,
                                                const std::string& oldSubstring,
                                                const std::string& newSubstring)
{
    auto sourceStringIter = sourceString.begin();

    while(sourceStringIter != sourceString.end())
    {
        sourceStringIter = std::search(sourceStringIter,
                                       sourceString.end(),
                                       oldSubstring.begin(),
                                       oldSubstring.end());

        if(sourceStringIter != sourceString.end())
        {
            sourceStringIter = sourceString.erase(sourceStringIter,sourceStringIter + oldSubstring.size());

            sourceStringIter = sourceString.insert(sourceStringIter,newSubstring.begin(),newSubstring.end());

            sourceStringIter += newSubstring.size();
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_STRINGMANIPULATION_HPP
