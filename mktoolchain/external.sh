
LIB_SDL_VERSION="2.0.12"
LIB_SDL_ENDPOINT="http://www.libsdl.org/release/SDL2-$LIB_SDL_VERSION.tar.gz"

LIB_SDL_TTF_VERSION="2.0.15"
LIB_SDL_TTF_ENDPOINT="https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-$LIB_SDL_TTF_VERSION.tar.gz"

LIB_SDL_IMAGE_VERSION="2.0.5"
LIB_SDL_IMAGE_ENDPOINT="https://www.libsdl.org/projects/SDL_image/release/SDL2_image-$LIB_SDL_IMAGE_VERSION.tar.gz"

function install_sdl()
{
    local build=$1
    local base=$(echo "${build,,}" | cut -d \- -f 1)
    local endpoint=$2

    cd $PREFIX

    download $endpoint

    run "Extract $build" tar xzf $build.tar.gz && rm -f $build.tar.gz
    mv $build $base

    cd $base

    run "Configure $build" ./configure
    run "Build $build" make all
}

function install_capstone()
{
    run "Download capstone" git clone https://github.com/aquynh/capstone.git $PREFIX/capstone

    cd $PREFIX/capstone

    run "Build capstone" ./make.sh
}