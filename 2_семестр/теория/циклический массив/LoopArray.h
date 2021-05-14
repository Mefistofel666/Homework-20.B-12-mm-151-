struct LoopArray
{
    int *data;
    size_t size;
    LoopArray(size_t size);
    ~LoopArray();
    LoopArray(const LoopArray &A);
    const LoopArray &operator=(const LoopArray &A);
    int &operator[](int i);
};
std::ostream &operator<<(std::ostream &out, const LoopArray &A);
