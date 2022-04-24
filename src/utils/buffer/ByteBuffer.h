#pragma once

// Default number of chars to allocate in the backing buffer if no size is provided
#define BB_DEFAULT_SIZE 4096


#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>

// If defined, utility functions within the class are enabled
#define BB_UTILITY
#ifdef BB_UTILITY
#include <cstdio>
#include <iostream>
#endif

namespace DB
{
    class ByteBuffer
    {
    public:
        ByteBuffer(uint32_t size = BB_DEFAULT_SIZE);
        ByteBuffer(char * arr, uint32_t size);
        ~ByteBuffer() = default;

        uint32_t bytesRemaining(); // Number of chars from the current read position till the end of the buffer
        void clear(); // Clear our the vector and reset read and write positions
        std::unique_ptr<ByteBuffer>
        clone(); // Return a new instance of a ByteBuffer with the exact same contents and the same state (rpos, wpos)
        //ByteBuffer compact(); // TODO?
        bool equals(ByteBuffer * other); // Compare if the contents are equivalent
        void resize(uint32_t newSize);
        uint32_t size(); // Size of internal vector

        // Basic Searching (Linear)
        template <typename T>
        int32_t find(T key, uint32_t start = 0)
        {
            int32_t ret = -1;
            uint32_t len = buf.size();
            for (uint32_t i = start; i < len; i++)
            {
                T data = read<T>(i);
                // Wasn't actually found, bounds of buffer were exceeded
                if ((key != 0) && (data == 0))
                    break;

                // Key was found in array
                if (data == key)
                {
                    ret = (int32_t)i;
                    break;
                }
            }
            return ret;
        }

        // Replacement
        void replace(char key, char rep, uint32_t start = 0, bool firstOccuranceOnly = false);

        // Read

        char peek() const; // Relative peek. Reads and returns the next char in the buffer from the current position but does not increment the read position
        char get() const; // Relative get method. Reads the char at the buffers current position then increments the position
        char get(uint32_t index) const; // Absolute get method. Read char at index
        void getBytes(char * buf, uint32_t len) const; // Absolute read into array buf of length len
        char getChar() const; // Relative
        char getChar(uint32_t index) const; // Absolute
        double getDouble() const;
        double getDouble(uint32_t index) const;
        float getFloat() const;
        float getFloat(uint32_t index) const;
        uint32_t getInt() const;
        uint32_t getInt(uint32_t index) const;
        uint64_t getLong() const;
        uint64_t getLong(uint32_t index) const;
        uint16_t getShort() const;
        uint16_t getShort(uint32_t index) const;

        // Write

        void put(ByteBuffer * src); // Relative write of the entire contents of another ByteBuffer (src)
        void put(char b); // Relative write
        void put(char b, uint32_t index); // Absolute write at index
        void putBytes(const char * b, uint32_t len); // Relative write
        void putBytes(const char * b, uint32_t len, uint32_t index); // Absolute write starting at index
        void putChar(char value); // Relative
        void putChar(char value, uint32_t index); // Absolute
        void putDouble(double value);
        void putDouble(double value, uint32_t index);
        void putFloat(float value);
        void putFloat(float value, uint32_t index);
        void putInt(uint32_t value);
        void putInt(uint32_t value, uint32_t index);
        void putLong(uint64_t value);
        void putLong(uint64_t value, uint32_t index);
        void putShort(uint16_t value);
        void putShort(uint16_t value, uint32_t index);

        // Buffer Position Accessors & Mutators

        void setReadPos(uint32_t r) { rpos = r; }

        uint32_t getReadPos() const { return rpos; }

        void setWritePos(uint32_t w) { wpos = w; }

        uint32_t getWritePos() const { return wpos; }

        // Utility Functions
#ifdef BB_UTILITY
        void setName(std::string n);
        std::string getName();
        void printInfo();
        void printAH();
        void printAscii();
        void printHex();
        void printPosition();
#endif

    private:
        uint32_t wpos;
        mutable uint32_t rpos;
        std::vector<char> buf;

#ifdef BB_UTILITY
        std::string name;
#endif

        template <typename T>
        T read() const
        {
            T data = read<T>(rpos);
            rpos += sizeof(T);
            return data;
        }

        template <typename T>
        T read(uint32_t index) const
        {
            if (index + sizeof(T) <= buf.size())
                return *((T *)&buf[index]);
            return 0;
        }

        template <typename T>
        void append(T data)
        {
            uint32_t s = sizeof(data);

            if (size() < (wpos + s))
                buf.resize(wpos + s);
            memcpy(&buf[wpos], (char *)&data, s);
            //printf("writing %c to %i\n", (char)data, wpos);

            wpos += s;
        }

        template <typename T>
        void insert(T data, uint32_t index)
        {
            if ((index + sizeof(data)) > size())
                return;

            memcpy(&buf[index], (char *)&data, sizeof(data));
            wpos = index + sizeof(data);
        }
    };

}
