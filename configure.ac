#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Delta], [v1])
AC_CONFIG_SRCDIR([include/screen.h])

# Check for NASM assembler
AC_CHECK_PROG(HAVE_NASM, nasm, yes, no)
if test "$HAVE_NASM" = "no"; then
	AC_MSG_ERROR([Delta must be compiled with nasm. Get it from http://nasm.us.])
fi

# Check for bmfs utility
AC_CHECK_PROG(HAVE_BMFS, bmfs, yes, no)
if test "$HAVE_BMFS" = "no"; then
	AC_MSG_ERROR([Please install "bmfs" from git://github.com/returninfinity/bmfs.git!])
fi

TOOLPREFIX=""

# Check for C compiler and binutils
PLATFORM=`uname`
if test "$PLATFORM" = "Linux"; then
	AC_PROG_CC([gcc clang])
	AC_CHECK_PROG(HAVE_BINUTILS, ld, yes, no)
	if test "$HAVE_BINUTILS" = "no"; then
		AC_MSG_ERROR([It appears that your system does not have functioning GNU binutils.])
	fi
elif test "$PLATFORM" = "Darwin"; then
	AC_CHECK_PROG(HAVE_BINUTILS, x86_64-elf-ld, yes, no)
	if test "$HAVE_BINUTILS" = "no"; then
		AC_MSG_ERROR([You need to install x86_64-elf-binutils (and probably x86_64-elf-gcc) from Macports!])
	fi
	AC_PROG_CC([x86_64-elf-gcc])
	TOOLPREFIX="x86_64-elf-"
else
	AC_MSG_ERROR([Your operating system is not supported!])
fi

echo "TOOLPREFIX=$TOOLPREFIX" > config.local

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
