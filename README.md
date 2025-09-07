# aligned_errors

What do the various aligned C functions do with a size of zero?

This is in support of

https://bugs.kde.org/show_bug.cgi?id=509139

* Notes*
FreeBSD uses a fairly old jemalloc (which is no longer under active developmnet)
and it does not have free_sized_aligned.

musl doesn't have free_aligned_sized. Compile the source with -D__MUSL__
(Alpine doesn't seem to have a predefined musl macro).

I'll write a separate test for the C free functions.

GNU libc <= 2.38 'fixed' aligned_alloc.

pass means that the allocation succeeds with a size of 0

| Platform        | memalign | aligned_alloc | posix_memalign |
|-----------------|----------|---------------|----------------|
| FreeBSD         | pass     | pass          | pass           |
| Linux old glibc | pass     | pass          | pass           |
| Linux new glibc | pass     | pass          | pass           |
| macOS           | NA       | pass          | pass           |
| Solaris         | fail     | fail          | pass           |
| illumos         | fail     | fail          | pass           |
| musl            | pass     | pass          | pass           |
| tcmalloc        | pass     | pass          | pass           |
| mimalloc        | pass     | pass          | pass           |
| snmalloc        |          |               |                |
| Windows MSVC    |          |               |                |

Just for the record, the same thing with an alignment of 0

| Platform        | memalign | aligned_alloc | posix_memalign |
|-----------------|----------|---------------|----------------|
| FreeBSD         | pass     | fail          | fail           |
| Linux old glibc | pass     | pass          | fail           |
| Linux new glibc | pass     | fail          | fail           |
| macOS           | NA       | fail          | fail           |
| Solaris         | fail     | fail          | fail           |
| illumos         | fail     | fail          | fail           |
| musl            | pass     | pass          | fail           |
| tcmalloc        |          |               |                |
| mimalloc        | fail     | fail          | fail           |
| snmalloc        |          |               |                |
| Windows MSVC    |          |               |                |
