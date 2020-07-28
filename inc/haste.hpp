#ifndef HASTE_HASTE_HPP
#define HASTE_HASTE_HPP

#include "haste_writer.hpp"
#include <vector>

namespace haste {

class haste : public haste_writer {
public:
    haste(std::vector<char const*> paths);
#if defined(_WIN32)
    haste(std::vector<wchar_t const*> paths);
#endif

    ~haste();
};

}   // namespace haste

#endif  // HASTE_HASTE_HPP
