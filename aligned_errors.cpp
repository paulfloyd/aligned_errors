#include <cstdlib>
#include <iostream>
#if defined(__FreeBSD__)
#include "malloc_np.h"
#endif

int main()
{
    int* mem{nullptr};
#if !defined(__APPLE__)
    // alignment of 0, for info
    mem = static_cast<int*>(memalign(0U, 16*sizeof(*mem)));
    if (mem)
    {
        free(mem);
    }
    else
    {
        std::cerr << "memalign alignment of 0 failed\n";
    }
#endif

    mem = static_cast<int*>(aligned_alloc(0U, 16*sizeof(*mem)));
    if (mem)
    {
        free(mem);
    }
    else
    {
        std::cerr << "aligned_alloc alignment of 0 failed\n";
    }

    mem = nullptr;
    int res = posix_memalign((void**)&mem, 0U, 16*sizeof(*mem));
    if (res == 0)
    {
        free(mem);
    }
    else
    {
        std::cerr << "posix_memalign alignment of 0 failed, res " << res << " mem " << mem << "\n";
    }

#if !defined(__APPLE__)
    // size of 0
    mem = static_cast<int*>(memalign(64U, 0U));
    if (mem)
    {
        free(mem);
    }
    else
    {
        std::cerr << "memalign size of 0 failed\n";
    }
#endif

    mem = static_cast<int*>(aligned_alloc(64U, 0));
    if (mem)
    {
        free(mem);
    }
    else
    {
        std::cerr << "aligned_alloc size of 0 failed\n";
    }

    mem = nullptr;
    res = posix_memalign((void**)&mem, 64U, 0);
    if (res == 0)
    {
        free(mem);
    }
    else
    {
        std::cerr << "posix_memalign size of 0 failed, res " << res << " mem " << mem << "\n";
    }
}
