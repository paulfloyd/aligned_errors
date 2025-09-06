#include <cstdlib>
#include <iostream>
#if defined(__FreeBSD__)
#include "malloc_np.h"
#endif

int main()
{
    // alignment of 0, for info
    int* mem = static_cast<int*>(memalign(0U, 16*sizeof(*mem)));
    if (mem)
    {
        free(mem);
    }
    else
    {
        std::cerr << "memalign alignment of 0 failed\n";
    }

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

    // free aligned with alignment of zero
#if !defined(__FreeBSD__)
    mem = static_cast<int*>(memalign(0U, 16*sizeof(*mem)));
    // how to detect failure?
    free_aligned_sized(mem, 0, 16*sizeof(*mem));
#endif

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

    // free sized with size of 0

#if !defined(__FreeBSD__)
    mem = static_cast<int*>(memalign(60U, 0U);
    // how to detect failure?
    free_aligned_sized(mem, 64U, 0U);

    // is this OK?
    mem = static_cast<int*>(malloc(0U);
    // how to detect failure?
    free_sized(mem, 0U);

#endif



}
