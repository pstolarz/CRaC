# CRaC: C-language binding

CRaC C++ template library may be bound into C-language code via C compliant
interface.

In the [`crac_c_example.c`](crac_c_example.c) three CRCs (`CRC8`, `CRC16`, `CRC32`)
are imported and used in three different calculation modes. Run `make` to build
the example.

The space-separated CRCs list which are going to be C-bound is defined by `CRC_LIST`
while running `make c_bind`. For example to bind `CRC5_ITU` and `CRC16_DARC` run
the following:

```
CRC_LIST="CRC5_ITU CRC16_DARC" make c_bind
```

Then include the `crac_c.o` object file into a project. `crac_c.h` shall be
used as C-header for the project's sources.

NOTES
* Each imported CRC is associated with set of C functions as exposed by `crac_c.h`
  auto-generated header.
* The `crac_c.cpp` is auto-generated C++ implementation file stubbing its calls
  into the CRaC library. It's compiled into `crac_c.o` object file.
* The `crac_c.h` and `crac_c.cpp` files are generated basing on `crac_c.h.tmpl`
  and `crac_c.cpp.tmpl` template files by `gen_c_bind.pl` Perl script.
* It is possible to import a custom CRC algorithm by adding its definition into
  the [`crac_c.cpp.tmpl`](crac_c.cpp.tmpl) template file.
* `crac_calc_bits_XXX()` family of functions uses `crac_in_t` (`uint32_t` by
  default) as input argument type. The type may be changed by updating
  [`crac_c.h.tmpl`](crac_c.h.tmpl) template file.