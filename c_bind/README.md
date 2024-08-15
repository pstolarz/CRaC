# CRaC: C-language binding

CRaC C++ template library may be bound into C-language code via C compliant
interface.

In the [`crac_c_example.c`](crac_c_example.c) three CRCs (CRC-8, CRC-16, CRC-32)
are imported and used in three different calculation modes. The CRC list may
be changed by defining `CRC_LIST` while launching `make` build:

```
CRC_LIST=... make
```

NOTES
* Each imported CRC is associated with set of C functions as exposed by `crac_c.h`
  auto-generated header.
* The `crac_c.cpp` is auto-generated C++ implementation file stubbing the calls
  into the CRaC library.
* The `crac_c.h` and `crac_c.cpp` files are generated basing on `crac_c.h.tmpl`
  and `crac_c.cpp.tmpl` template files by `gen_c_bind.pl` Perl script.
* It is possible to import a custom CRC algorithm by adding its definition into
  the [`crac_c.cpp.tmpl`](crac_c.cpp.tmpl) template file.
* `crac_calc_bits_XXX()` family of functions uses `crac_in_t` (`uint32_t` by
  default) as input argument type. The type may be changed by updating
  [`crac_c.h.tmpl`](crac_c.h.tmpl) template file.
