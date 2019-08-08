# For What

this project for ELF file parser

# Env

need cmake

- ubuntu

```sh
# install cmake version 3.5.1 in ubuntu 16.04
$ sudo apt install cmake
```

# build

```sh
$ mkdir build && cd build
$ cmake ..
$ make
# right out will build elf exec file elf_file_parser
```

# use

```sh
# when build success in build/elf_file_parser
$ ./build/elf_file_parser [elf file]
```
