# date_wrapper
Wrapper for a subset of the excellent [Howard Hinnant's date library](https://github.com/HowardHinnant/date) that provides some functions and additional types.

Created to shield agains API changes when Howard Hinnant's library was in active development, **date_wrapper** will soon be obsolete as underlying library will be a part of upcoming C++20. After wide adoption of C++20 a release will be made that will use standard library implementation instead of reference implementation and this wrapper will probably be around while older projects will need it. After that, **date_wrapper** will no longer be supported, although, some parts of **date_wrapper** will be probably reused in a separate date utils library, if it will make sense.

