# aligned_errors

What do the various aligned C functions do with a size of zero?

This is in support of

https://bugs.kde.org/show_bug.cgi?id=509139

Presumably free_aligned_sized with an alignment of zero depends on aligned_alloc
with a size of 0 succeeding (otherwise free_sized_aligned ought to fail due
to alignment mismatch).

* Notes*
FreeBSD uses a fairly old jemalloc (which is no longer under active developmnet)
and it does not have free_sized_aligned.

musl doesn't have free_[aligned_]sized. Compile the source with -D__MUSL__
(Alpine doesn't seem to have a predefined musl macro).

I need to figure out which glibc version 'fixed' memalign/aligned_alloc.

pass means that the allocation succeeds.

| Platform        | memalign | aligned_alloc | posix_memalign | free_aligned_sized |
|-----------------|----------|---------------|----------------|--------------------|
| FreeBSD         | pass     | pass          | pass           | NA                 |
| Linux old glibc |          |               |                |                    |
| Linux new glibc |          |               |                |                    |
| macOS           |          |               |                |                    |
| illumos         |          |               |                |                    |
| musl            | pass     | pass          | pass           | NA                 |
| tcmalloc        |          |               |                |                    |
| mimalloc        |          |               |                |                    |
| snmalloc        |          |               |                |                    |
| Windows MSVC    |          |               |                |                    |
