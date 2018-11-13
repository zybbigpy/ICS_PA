struct Cacheline {
    struct bitAndFlag {
        uint32_t validBit:1;
        uint32_t flag:19;
    };

}