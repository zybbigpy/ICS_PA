struct Cacheline {
    struct bitAndFlag {
        //valid bit
        uint32_t validBit:1;
        //flag
        uint32_t flag:19;
    };
    // 64byte for content
    uint32_t content[16];
};