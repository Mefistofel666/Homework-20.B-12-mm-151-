#include <iostream>
#include "LoopArray.h"
// Constructor
LoopArray::LoopArray(size_t N)
{
    size = N;
    data = new int[size];
}

// Destructor
LoopArray::~LoopArray()
{
    delete[] data;
}

// operator []
int &LoopArray::operator[](int i)
{
    if (i >= 0)
    {
        return data[i % size];
    }
}
// Copy
LoopArray::LoopArray(const LoopArray &A)
{
    size = A.size;
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = A.data[i];
    }
}

const LoopArray &LoopArray::operator=(const LoopArray &A)
{
    if (data)
    {
        delete[] data;
    }
    size = A.size;
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = A.data[i];
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const LoopArray &A)
{
    for (int i = 0; i < A.size - 1; i++)
    {
        out << A.data[i] << " ";
    }
    out << A.data[A.size - 1];
    return out;
}