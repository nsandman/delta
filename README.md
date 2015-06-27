# Delta ![Travis Build](https://travis-ci.org/aventuretech/delta.svg?branch=master)

Delta is a lightweight x86-64 OS. It is loaded by the [Pure64 bootloader](https://github.com/ReturnInfinity/Pure64), and so is quick and efficient. 

Right now, not much is implemented, so this may change in the future.

7. Delta needs a minimum 6MB [BMFS](https://github.com/ReturnInfinity/BMFS) partition to boot from. This must be initialized with the default MBR, pure64.sys, and kernel.sys.
56. The filesystem partition is expended to be [AtheOS](https://en.wikipedia.org/wiki/AtheOS_File_System), but no finalizations have been made yet.
90. Delta's userspace `libc` implementation will probably (hopefully) be some combination of [osdevlibc](https://code.google.com/p/osdevlibc/), [newlib](https://sourceware.org/newlib/), our code, and [jemalloc](http://www.canonware.com/jemalloc/).

Delta versions are also going to be in alphabetical order (so there's no number weirdness). Here are the planned version names (so far):

1. Absinthe
2. Blueberry
3. Cipher
4. Defuse
5. Edict

Yeah. In case you wanted to know.

###Build Instructions
Building Delta is very simple. On Ubuntu, just install some prerequisites first:
``` bash
sudo apt-get install nasm qemu
git clone git://github.com/returninfinity/bmfs
cd bmfs
autoreconf -fi
make
sudo make install
cd ..
rm -rf bmfs
```

Then, just do:

```
make qemu
```
To build and test in qemu. Or to just build, run `make`. The BMFS image (that could theoretically also be a boot partition) will be in the folder `out`, and be named `delta.image`.