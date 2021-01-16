
LIB_SDL_VERSION="2.0.12"
LIB_SDL_ENDPOINT="http://www.libsdl.org/release/SDL2-$LIB_SDL_VERSION.tar.gz"

function install_sdl()
{
    local build=$1
    local endpoint=$2

    cd $PREFIX

    download $endpoint

    run "Extract $build" tar xzf $build.tar.gz && rm -f $build.tar.gz
    mv $build sdl2

    cd sdl2

    run "Configure $build" ./configure
    run "Build $build" make all
}

### Build capstone ##################################################################
run "Download capstone" git clone https://github.com/aquynh/capstone.git $PREFIX/capstone

cd $PREFIX/capstone

run "Build capstone" ./make.sh

### Build SL2      ##################################################################
install_sdl "SDL2-$LIB_SDL_VERSION" $LIB_SDL_ENDPOINT
