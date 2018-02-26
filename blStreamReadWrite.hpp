#ifndef BL_STREAMREADWRITE_HPP
#define BL_STREAMREADWRITE_HPP



//-------------------------------------------------------------------
// FILE:            blReadWrite.hpp
//
//
//
// PURPOSE:         Generic functions that simplify reading from a
//                  stream into a variable or a contiguous buffer
//                  and writing to a stream from a variable or a
//                  contiguous buffer
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
// The following functions can be used to:
// -- Read from a stream into a buffer/variable
//    of any type
// -- Write from a buffer/variable of
//    any type into a stream
//
// It assumes the following:
//
// -- stream defines the functions: "read" and "write" that look
//    like the iostream functions
//
// -- buffer defines data() function that returns pointer
//    to its first element
//
// -- buffer defines size() function that returns
//    the size/length of the buffer
//-------------------------------------------------------------------
template<typename blInputStreamType,
         typename blValueType>

inline blInputStreamType& readValue(blInputStreamType& is,blValueType& value)
{
    is.read(reinterpret_cast<char*>(&value),sizeof(value));
    return is;
}



template<typename blInputStreamType,
         typename blBufferType>

inline blInputStreamType& readBuffer(blInputStreamType& is,blBufferType& buffer)
{
    is.read(reinterpret_cast<char*>(buffer.data()),sizeof(buffer.data()[0])*buffer.size());
    return is;
}



template<typename blInputStreamType,
         typename blBufferType>

inline blInputStreamType& readBuffer(blInputStreamType& is,blBufferType& buffer,const int& bufferLength)
{
    is.read(reinterpret_cast<char*>(buffer.data()),sizeof(buffer.data()[0])*bufferLength);
    return is;
}



template<typename blOutputStreamType,
         typename blValueType>

inline blOutputStreamType& writeValue(blOutputStreamType& os,const blValueType& value)
{
    os.write(reinterpret_cast<const char*>(&value),sizeof(value));
    return os;
}



template<typename blOutputStreamType,
         typename blBufferType>

inline blOutputStreamType& writeBuffer(blOutputStreamType& os,const blBufferType& buffer)
{
    os.write(reinterpret_cast<const char*>(buffer.data()),sizeof(buffer.data()[0])*buffer.size());
    return os;
}



template<typename blOutputStreamType,
         typename blBufferType>

inline blOutputStreamType& writeBuffer(blOutputStreamType& os,const blBufferType& buffer,const int& bufferLength)
{
    os.write(reinterpret_cast<const char*>(buffer.data()),sizeof(buffer.data()[0])*bufferLength);
    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function does buffered reading/writing from an input
// stream to an output stream.
// The function keeps reading/writing until no bytes are read
//
// -- The function assumes the following:
//
//    -- The input stream defines the functions "read" and "gcount"
//    -- The output stream defines the "write" function
//    -- The buffer defines the "operator[]" and "size" functions
//-------------------------------------------------------------------
template<typename blInputStreamType,
         typename blOutputStreamType,
         typename blBufferType>

inline int readFromStreamWriteToStream(blInputStreamType& inputStream,
                                       blOutputStreamType& outputStream,
                                       blBufferType& buffer)
{
    // Variable used to know how
    // many bytes were read from
    // the input stream during
    // the last read

    int numberOfBytesRead = 1;



    // Total number of bytes read

    int totalNumberOfBytesRead = 0;



    // Keep reading/writing until
    // no more bytes are read

    if(buffer.size() > 0)
    {
        while(numberOfBytesRead > 0)
        {
            inputStream.read(reinterpret_cast<char*>(&buffer[0]),sizeof(buffer[0]) * buffer.size());

            numberOfBytesRead = inputStream.gcount();

            totalNumberOfBytesRead += numberOfBytesRead;

            outputStream.write(reinterpret_cast<char*>(&buffer[0]),numberOfBytesRead);
        }
    }



    // We're done

    return totalNumberOfBytesRead;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_STREAMREADWRITE_HPP
