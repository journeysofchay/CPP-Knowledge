#include <cstdint>

struct StdLargeInteger {
    union {
        struct {
            std::int32_t LowPart;
            std::int32_t HighPart;
        };
        std::int64_t QuadPart;
    };
};
