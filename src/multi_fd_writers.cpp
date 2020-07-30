#include "multi_fd_writers.hpp"

#include <system_error>
#include <cassert>
#include <limits>   // numeric_limits

#if defined(__unix__)
#include <sys/stat.h>   // open
#include <sys/types.h>  // open, lseek
#include <fcntl.h>      // open
#include <errno.h>      // errno
#include <unistd.h>     // lseek, close

#elif defined(_WIN32)

#define NOMINMAX
#include <Windows.h>

#endif

#if defined(__unix__)
namespace {
std::vector<int> open_file(std::vector<char const*> paths)
{
    auto full_access =
        S_IRUSR | S_IWUSR |
        S_IRGRP | S_IWGRP |
        S_IROTH | S_IWOTH;
    std::vector<int> fd;
    for (size_t i=0; i < paths.size(); i++)
    {
        fd[i] = open(paths[i], O_WRONLY | O_CREAT | O_APPEND, full_access);
        if(fd[i] == -1)
            throw std::system_error(errno, std::system_category());
    }
    return fd;
}

}

haste::haste::haste(std::vector<char const*> paths) : 
    haste_writer(open_file(paths))
{
}

haste::haste::~haste()
{
    for(size_t i=0; i<fd_.size(); i++)
    {
        if(fd_[i] != -1) {
            while(-1 == close(fd_[i])) {
                if(errno != EINTR)
                    break;
            }
        }
    }
}

#elif defined(_WIN32)
namespace {
    template <class F, typename T>
    HANDLE createfile_generic(F CreateFileX, std::vector<T const*> paths)
    {
        // From NtCreateFile documentation:
        // (https://msdn.microsoft.com/en-us/library/bb432380.aspx)
        // If only the FILE_APPEND_DATA and SYNCHRONIZE flags are set, the caller
        // can write only to the end of the file, and any offset information on
        // writes to the file is ignored. However, the file is automatically
        // extended as necessary for this type of write operation.
        // TODO what happens if the user deletes the file while we are writing?
        std::vector<HANDLE> h;
        for (size_t i=0; i<h.size(); i++)
        {
            h[i] = CreateFileX(paths[i],
                FILE_APPEND_DATA | SYNCHRONIZE,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL,
                OPEN_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
            if(h[i] == INVALID_HANDLE_VALUE)
                throw std::system_error(GetLastError(), std::system_category());
        }
        return h;
    }
}
reckless::haste::haste(std::vector<char const*> paths) :
    haste_writer(createfile_generic(CreateFileA, paths))
{
}

reckless::haste::haste(std::vector<wchar_t const*> paths) :
    haste_writer(createfile_generic(CreateFileW, paths))
{
}

reckless::file_writer::~file_writer()
{
    for (int i=0; i<handle_.size(); i++)
    {
        CloseHandle(handle_[i]);
    }
}

#endif
