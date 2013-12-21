// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <stdint.h>
#include <vector>
#include <string>
#include "Poco/File.h"


namespace ofx {
namespace IO {


class AbstractByteSink;
class AbstractBufferedByteSource;
class ByteBuffer;


class AbstractByteSource
    /// \brief   Represents the abstract notion of a byte source.
    /// \details An AbstractByteSource has bytes that can be read.
{
public:
    virtual ~AbstractByteSource()
        ///< \brief Destroys the byte source.
    {
    }

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) const = 0;
        ///< \brief Read bytes from this source into a target buffer.
        ///< \param buffer is the target buffer to be filled with bytes.
        ///< \param size is the number of bytes to be written into the target buffer.
        ///< \returns the number of bytes that were successfully
        ///< written into the target buffer.

    virtual std::size_t readBytes(std::vector<uint8_t>& buffer) const = 0;
        ///< \brief Read bytes from this source into a target buffer.
        ///< \param buffer is the target buffer to be filled with bytes.
        ///< \returns the number of bytes that were successfully
        ///< written into the target buffer.

    virtual std::size_t readBytes(std::string& buffer) const = 0;
        ///< \brief Read bytes from this source into a target buffer.
        ///< \param buffer is the target buffer to be filled with bytes.
        ///< \returns the number of bytes that were successfully
        ///< written into the target buffer.

    virtual std::size_t readBytes(ByteBuffer& buffer) const = 0;
        ///< \brief Read bytes from this source into a target buffer.
        ///< \param buffer is the target buffer to be filled with bytes.
        ///< \returns the number of bytes that were successfully
        ///< written into the target buffer.

};



class AbstractByteSink
    /// \brief Represents the abstract notion of a byte sink.
    /// \details An AbstractByteSink can receive bytes written
    /// from various sources.
{
public:
    virtual ~AbstractByteSink()
        ///< \brief Destroys the byte sink.
    {
    }

    virtual std::size_t writeByte(uint8_t data) = 0;
        ///< \brief Write a single byte into this byte sink.
        ///< \param data is the single byte to be written into this byte sink.
        ///< \returns the number of bytes that were successfully
        ///< written into this byte sink.

    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size) = 0;
        ///< \brief Write the contents of the buffer into this byte sink.
        ///< \param buffer is the array of bytes to be written to this byte sink.
        ///< \param size is the number of bytes in the buffer.
        ///< \returns the number of bytes that were successfully
        ///< written into this byte sink.

    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer) = 0;
        ///< \brief Write the contents of the buffer into this byte sink.
        ///< \param buffer is the array of bytes to be written to this byte sink.
        ///< \returns the number of bytes that were successfully
        ///< written into this byte sink.

    virtual std::size_t writeBytes(const std::string& buffer) = 0;
        ///< \brief Write the contents of the buffer into this byte sink.
        ///< \param buffer is the array of bytes to be written to this byte sink.
        ///< \returns the number of bytes that were successfully
        ///< written into this byte sink.

};


class AbstractBufferedByteSource
    /// \brief Represents the abstract notion a buffered byte source.
    /// \details Unlike a AbstractByteSource, a buffered byte source is
    /// consumed as it is read.
{
public:
    virtual ~AbstractBufferedByteSource()
        ///< \brief Destroys the buffered byte source.
    {
    }

    virtual std::size_t readByte(uint8_t& data) = 0;
        ///< \brief Read a single byte from this source into the referenced variable.
        ///< \param data is referenced variable to be filled.
        ///< \returns the number of bytes that were successfully
        ///< written into the referenced data variable.  The maxium
        ///< return value is 1.

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) = 0;
        ///< \brief Read bytes from this source into a target buffer.
        ///< \param buffer is the target buffer to be filled with bytes.
        ///< \param size is the number of bytes to be written into the target buffer.
        ///< \returns the number of bytes that were successfully
        ///< written into the target buffer.

    virtual std::size_t available() const = 0;
        ///< \brief Query the number of buffered bytes.
        ///< \returns the number of bytes available to be read.
    
};


class AbstractFileFilter
    /// \brief Represents the abstract notion of a file filter.
    /// \details Subclasses implementing this interface can accept files
    /// based on a criteria defined in the accept() method.
{
public:
    virtual ~AbstractFileFilter()
        ///< \brief Destroys the file filter.
    {
    }
    
    virtual bool accept(const Poco::File& file) const = 0;
        ///< \brief Accept a file based on a defined criteria.
        ///< \returns true iff the file is accepted by the file filter.

};


class AbstractSearchPath
    /// \brief Represents the abstract notion of a search path.
{
public:
    virtual ~AbstractSearchPath()
        ///< \brief Destroys the resource.
    {
    }

    virtual bool isRecursive() const = 0;
        ///< \returns true iff this search path should be searched recursively.

    virtual Poco::Path getPath() const = 0;
        ///< \returns the base search path.
    
};


} } // namespace ofx::IO