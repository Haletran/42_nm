# 42_nm

## What does `nm` print ?

The `nm` UNIX command lists symbols from object files. For example:

> nm ft_nmn

will print : 

```bash
000000000040037c r __abi_tag
0000000000405070 B __bss_start
0000000000401ca0 T check_del
0000000000401480 T checkElfHeader
0000000000401cf0 T check_identifier
0000000000401cc0 T check_specifier
                 U close@GLIBC_2.2.5
0000000000405070 b completed.0
0000000000405060 D __data_start
0000000000405060 W data_start
0000000000401100 t deregister_tm_clones
00000000004010f0 T _dl_relocate_static_pie
0000000000401170 t __do_global_dtors_aux
0000000000404e08 d __do_global_dtors_aux_fini_array_entry
0000000000405068 D __dso_handle
0000000000404e10 d _DYNAMIC
0000000000405070 D _edata
0000000000405078 B _end
00000000004013c0 T execute
0000000000402674 T _fini
00000000004011a0 t frame_dummy
0000000000404e00 d __frame_dummy_init_array_entry
00000000004035e8 r __FRAME_END__
                 U free@GLIBC_2.2.5
00000000004011b0 T free_params
```

To understand the symbols, `r` `B` etc... 
Read the man of `nm` :
> man nm

Here is those that we need to handle :

- SHN_UNDEF (usually 0) means symbol is undefined (not defined in this file) → U
- SHF_EXECINSTR means section is executable → T or t
- SHF_WRITE means section is writable (data) → D or d
- SHT_NOBITS means uninitialized data (bss) → B
- SHF_ALLOC means section is allocated in memory (like .rodata) → r (if local, read-only)
- STB_WEAK is symbol binding for weak symbols → w

## USEFUL LINKS 

- https://gist.github.com/x0nu11byt3/bcb35c3de461e5fb66173071a2379779
- https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
- https://linux.die.net/man/2/fstat
