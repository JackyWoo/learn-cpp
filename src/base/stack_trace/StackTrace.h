//
// Created by wujianchao5 on 2022/8/22.
//

#ifndef LEARN_CPP_STACKTRACE_H
#define LEARN_CPP_STACKTRACE_H

#include <array>
#include <optional>
#include <string>
#include <sstream>

class StackTrace
{
public:
    struct Frame
    {
        const void * virtual_addr = nullptr;
        void * physical_addr = nullptr;
        std::optional<std::string> symbol;
        std::optional<std::string> object;
        std::optional<std::string> file;
        std::optional<uint64_t> line;
    };

    using FramePtr = void *;
    using FramePtrs = std::array<FramePtr, 100>;

    StackTrace()
    {

    }

    std::string translate(Frame * frame)
    {
        std::stringstream ss;
        ss.exceptions(std::ios::failbit);
        ss << 0 << ". " << frame << std::endl;
        return ss.str();
    }

private:
    FramePtrs frame_ptrs;
};


#endif //LEARN_CPP_STACKTRACE_H
