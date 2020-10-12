class Allocator {
    char *mem;
    size_t alloc_size;
    size_t offset;
public:
    Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};