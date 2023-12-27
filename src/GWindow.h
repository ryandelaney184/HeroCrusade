//
// Created by Solomon on 12/23/2023.
//

#ifndef HC_GWINDOW_H
#define HC_GWINDOW_H

//----------------------------------------------------------------------------------------------------------------------
// Library
//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <cstdio>
#include <SDL.h>

#ifdef OPENGL
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#ifdef VULKAN
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#endif

#ifdef VR
#include <openvr.h>
#endif

namespace HC {

    //--------------------------------------------------------------------------------------------------------------
    // Predefine
    //--------------------------------------------------------------------------------------------------------------
#ifdef DEBUG
#define MSG(CLASS,LOC,TYPE, MESSAGE) std::cout << "[" << CLASS << "][" <<LOC << "][" << TYPE <<"]: " << MESSAGE
#define END << std::endl;
#endif

    /**
     * The @code WindowDetails stores the desired configuration for the Window. The @code WindowDetails
     * can be used to create a @code GWindow, or store the current configuration of a @code GWindow.
     */
    struct WindowDetails {
         const char* title;
         int width, height;
         int xPos, yPos;
         int windowFlag;
    };

    /**
     * The @code GWindow class contains everything that is needed to render a game. This will provide
     * the @code SDL_Window. and a SDL_Renderer, and either a OpenGL context, or a Vulkan instance, and
     * a OpenVR instance.
     */
    class GWindow {
    private:
        //--------------------------------------------------------------------------------------------------------------
        // Attributes
        //--------------------------------------------------------------------------------------------------------------
        WindowDetails details;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

        #ifdef VULKAN
        VkInstanceCreateInfo createInfo;
        VkInstance *instance = nullptr;
        #endif

        #ifdef OPENGL
        GLuint vertexBuffer;
        #endif

        #ifdef VR
        vr::IVRSystem *vr = nullptr;
        #endif

        //--------------------------------------------------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------------------------------------------------

    public:

        /**
         * The GWindow constructor will use the data in the @code WindowDetails to configure
         * a GWindow. Please make sure all of your values are correct before you pass it to
         * the constructor. Like make sure your width, and height are not less than 0 or
         * greater than the size of your monitor.
         */
        explicit GWindow(const WindowDetails& details);

        /**
         * Made the copy constructor protected so that the only the @code GWindow can
         * make a copy of itself. This is to prevent unnecessary copying of a @code
         * GWindow instance.
         * @param original the variable that shouldn't be copied.
         */
        GWindow(const GWindow& original) = delete;

    private:

        void validateWindowDetails(WindowDetails detailsValid) const;
    };

}

#endif //HC_GWINDOW_H
