//----------------------------------------------------------------------------------------------------------------------
// Libraries
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#ifdef VULKAN
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#endif

#ifdef OPENGL
#include <SDL_opengl.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#endif

#ifdef VR
#include <openvr.h>
#endif

//----------------------------------------------------------------------------------------------------------------------
// Predefine
//----------------------------------------------------------------------------------------------------------------------
typedef const unsigned char flag;

#ifdef DEBUG
#define MSG(NAME,METHOD, MSG) std::cout << "[" << NAME << "][" << METHOD << "]:" << MSG << std::endl;
#define MAIN_MSG(MESSAGE) MSG("HeroCrusade", "main", MESSAGE)
#endif

//----------------------------------------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------------------------------------

static flag SDL_FAILED = 0x1;
static flag SDL_IMAGE_FAILED = 0x2;
static flag SDL_TTF_FAILED = 0x4;
static flag SDL_MIXER_FAILED = 0x8;

//----------------------------------------------------------------------------------------------------------------------

// Define Methods
//----------------------------------------------------------------------------------------------------------------------

/**
 * The initSDLLibraries will attempt to load the necessary libraries into
 * memory. This method should return 0 on success or a bit flag that
 * represents the libraries that fail to load.
 * --- Bit flag ---
 * 1 - SDL2
 * 2 - SDL2 Image
 * 4 - SDL2 TTF
 * 8 - SDL2 Mixer
 *
 * @return 0 or on fail a bit flag of the libraries that didn't load.
 */
int initSDLLibraries();

/**
 * The 'main' method is the entry point for Hero Crusade. This will load the necessary libraries, and will
 * create, maintain, and destroy the game instance when done.
 * @param argc The number of arguments in the string array.
 * @param args The array of arguments pass to thru the Command Line or Terminal.
 * @return The exit status
 */
int main(int argc, char* args[]);

//----------------------------------------------------------------------------------------------------------------------
// Entry Point
//----------------------------------------------------------------------------------------------------------------------

int main(int argc, char* args[]) {

#ifdef DEBUG
    MAIN_MSG("Hello welcome to Hero Crusade.")
    MAIN_MSG("Loading libraries.")
#endif

    int loadLibraryResult = initSDLLibraries();

    if(loadLibraryResult > 0){
    #ifdef DEBUG
        std::cout << "'initSDLLibraries' return a error code of " << loadLibraryResult << std::endl;
    #endif
        exit(loadLibraryResult);
    }
    return 0;
}

int initSDLLibraries() {
    int result = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
#ifdef DEBUG
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Error SDL2 couldn't be loaded!" << std::endl;
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Reason: " << SDL_GetError() << std::endl;
#endif
        result += SDL_FAILED;
    }

    if(IMG_Init(IMG_INIT_JPG) < 0) {
#ifdef DEBUG
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Error SDL2 Image couldn't be loaded!" << std::endl;
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Reason: " << IMG_GetError() << std::endl;
#endif
        result += SDL_IMAGE_FAILED;
    }

    if(TTF_Init()){
#ifdef DEBUG
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Error SDL2 TTF couldn't be loaded!" << std::endl;
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Reason: " << TTF_GetError() << std::endl;
#endif
        result += SDL_TTF_FAILED;
    }

    if(Mix_Init(MIX_INIT_MP3) < 0) {
#ifdef DEBUG
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Error SDL2 Mixer couldn't be loaded!" << std::endl;
        std::cout << "[HeroCrusade][initSDLLibraries]:" << "Reason: " << Mix_GetError() << std::endl;
#endif
        result += SDL_MIXER_FAILED;
    }

    return result;
}