struct A
{
    int a:5;
    int b:3;
};
struct Cacheline {
    struct validbit {
        uint32_t sign:1;
    };

}