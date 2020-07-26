#ifndef HASTE_WRITER_HPP
#define HASTE_WRITER_HPP

#include <reckless/writer.hpp>
#include <vector>

namespace haste {

class haste_writer : public reckless::writer {
public:
#if defined(__unix__)
    haste_writer(std::vector<int> fd) : fd_(fd) {}
#elif defined(_WIN32)
    haste_writer(std::vector<void*> handle) : handle_(handle) {}
#endif

    std::size_t write(void const* pbuffer, std::size_t count, std::error_code& ec) noexcept override;
    std::size_t write_to_idx(void const* pbuffer, std::size_t count, std::error_code& ec, uint32_t idx) noexcept;

#if defined(__unix__)
    std::vector<int> fd_;
#elif defined(_WIN32)
    std::vector<void*> handle_;
#endif

};

}   // namespace haste

#endif  // HASTE_WRITER_HPP
