#ifndef HASTE_WRITER_HPP
#define HASTE_WRITER_HPP

#include <reckless/writer.hpp>

namespace haste {

class haste_writer : public writer {
public:
#if defined(__unix__)
    haste_writer(int fd, bool stderr_fd) : fd_(fd), stderr_(stderr_fd) {}
#elif defined(_WIN32)
    haste_writer(void* handle, bool stderr_fd) : handle_(handle), stderr_(stderr_fd) {}
#endif

    std::size_t write(void const* pbuffer, std::size_t count, std::error_code& ec) noexcept override;

#if defined(__unix__)
    int fd_;
    int stderr_;
#elif defined(_WIN32)
    void* handle_;
    void* stderr_;
#endif

private:
    std::size_t write_to_file(void const* pbuffer, std::size_t count, std::error_code& ec) noexcept override;
    std::size_t write_to_stderr(void const* pbuffer, std::size_t count, std::error_code& ec) noexcept override;

};

}   // namespace haste

#endif  // HASTE_WRITER_HPP
