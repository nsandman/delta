<p align="center">
  <img alt="Delta" src="http://s18.postimg.org/xjr7aiau1/delta.png" height="80" />
</p>
<p align="center">
  <a href="https://travis-ci.org/aventuretech/delta"><img src="https://travis-ci.org/aventuretech/delta.svg?branch=master" /></a>
</p>

Delta is a lightweight x86-64 OS. It is loaded by the [Pure64](https://github.com/ReturnInfinity/Pure64) bootloader, and so is quick and efficient. 

Right now, not much is implemented, so this may change in the future.

7. Delta needs a minimum 6MB [BMFS](https://github.com/ReturnInfinity/BMFS/wiki/BareMetal-File-System) partition to boot from. This must be initialized with the default MBR, pure64.sys, and kernel.sys.
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
Building Delta is very simple. On Ubuntu, just install some prerequisites first (nasm and qemu):
``` bash
sudo apt-get install nasm qemu
```

**NOTE**: If you are on OS X, Delta will not compile with Apple's nasm. You need to install MacPorts and get all project dependencies using this command:
``` bash
sudo port install x86_64-elf-binutils autoconf automake libtool nasm qemu
```

Or, if you happen to have Homebrew as well (yeah, I know you're technically not supposed to), you can install probably more up-to-date versions of everything *except* x86_64-elf-binutils, which *must* be either built from source or installed with MacPorts. In that case, just do:
```bash
brew install autoconf automake nasm qemu
# However you're going to get binutils
```

However, on EVERY system, you need to build and install [BMFS](https://github.com/ReturnInfinity/BMFS).
```
git clone git://github.com/returninfinity/bmfs
cd bmfs
autoreconf -fi
./configure
make
sudo make install
cd ..
rm -rf bmfs
```

Then, just do:

```
autoconf
./configure
make qemu
```
To build and test in qemu. Or to just build, run `make` instead of `make qemu`. The BMFS image (that could theoretically also be a boot partition) will be in the folder `out`, and be named `delta.image`.
