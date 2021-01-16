GNU_MIRROR="https://ftp.gnu.org/gnu"
KRN_MIRROR="https://mirrors.edge.kernel.org/pub/linux/kernel/"
GCC_VERSION="10.2.0"
BIN_VERSION="2.35"
LIB_VERSION="2.32"
KRN_VERSION="5.9.8"
RDL_VERSION="8.1"

### Build Headers ##############################################################
# download "$KRN_MIRROR/v5.x/linux-$KRN_VERSION.tar.xz"

# run "Extract Linux-$KRN_VERSION.tar.xz" tar xf linux-$KRN_VERSION.tar.xz

# cd linux-$KRN_VERSION

# # mkdir -p $PREFIX/include

# run "Install headers" make ARCH=$TARGET INSTALL_HDR_PATH=$PREFIX headers_install

# cd ..

# ### Build Binutils #############################################################
# download "$GNU_MIRROR/binutils/binutils-$BIN_VERSION.tar.xz"

# run "Extract binutils-$BIN_VERSION.tar.xz" tar xf binutils-$BIN_VERSION.tar.xz

# mkdir -p binutils-build || exit 1

# cd binutils-build

# run "Configure binutils-$BIN_VERSION-$TARGET"  ../binutils-$BIN_VERSION/configure --target=$TARGET-elf --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror

# run "Build binutils-$BIN_VERSION-$TARGET" "make && make install || exit 1"

# cd ..

# ### Build libc ###################################################################
# download "$GNU_MIRROR/libc/glibc-$LIB_VERSION.tar.xz"

# run "Extract glibc-$LIB_VERSION.tar.xz" tar xf glibc-$LIB_VERSION.tar.xz

# mkdir -p glibc-build || exit 1
# cd glibc-build

# run "Configure glibc-$LIB_VERSION-$TARGET" ../glibc-$LIB_VERSION/configure --target=$TARGET-elf --prefix=$PREFIX --with-headers=$PREFIX/include

# run "Build glibc-$LIB_VERSION-$TARGET" "make install-headers && make -j4 && make install install_root=$PREFIX || exit 1"

# cd ..

#### Build GCC ####################################################################
# download "$GNU_MIRROR/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz"

# run "Extract gcc-$GCC_VERSION.tar.xz" tar xf gcc-$GCC_VERSION.tar.xz

# mkdir -p gcc-build || exit 1
# cd gcc-build

# make distclean

# run "Configure gcc-$GCC_VERSION-$TARGET" ../gcc-$GCC_VERSION/configure 			\
# 											--target=$TARGET-elf				\
# 											--prefix=$PREFIX 					\
# 											--with-sysroot=$PREFIX				\
# 											--with-headers=$PREFIX/include 		\
# 											--enable-languages=c 				\
# 											--enable-lto 						\
# 											--disable-multilib					\
# 											--disable-werror					\
# 											--disable-nls 						\
# 											--disable-libssp 					\
# 											--disable-libstdcxx-pch 			\
# 											--disable-libunwind-exceptions		\
# 											|| exit 1
# 											#--disable-bootstrap					\
# 											#--libdir=$PREFIX/lib 				\
# 											#--libexecdir=$PREFIX/libexec 		\

# run "Build gcc-$GCC_VERSION-$TARGET" "make all-gcc && make install-gcc && make all-target-libgcc && make install-target-libgcc && echo "nice job" || exit 1"

# cd ..

### Build ARM utils ###############################################################
# cd binutils-build

# make -C ../binutils-build distclean

# run "Configure binutils-$BIN_VERSION-armv7"  ../binutils-$BIN_VERSION/configure --target=arm-tdmi-eabi --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror

# run "Build binutils-$BIN_VERSION-armv7" "make && make install || exit 1"

# cd ..

### Build readline ##################################################################
# cd $WORKSPACE

# download "$GNU_MIRROR/readline/readline-$RDL_VERSION.tar.gz"

# run "Extract readline-$RDL_VERSION.tar.gz" tar xf readline-$RDL_VERSION.tar.gz --directory $PREFIX --transform "s/readline-$RDL_VERSION/readline/"

# cd $PREFIX/readline

# run "Configure readline" ./configure

# run "Build readline" make
