//
// Created by Solomon on 12/23/2023.
//

#include "GWindow.h"

HC::GWindow::GWindow(const HC::WindowDetails &details) {
    #ifdef DEBUG
    #define INFO(MESSAGE) MSG("GWindow", "Constructor", "INFO", MESSAGE)
    #endif

    #ifdef DEBUG
        INFO("Creating a new GWindow") END
        INFO("Validating the WindowDetails - ") << &details END
    #endif

    validateWindowDetails(details);

    #ifdef DEBUG
    INFO("All good your configuration is correct.") << std::endl;
    #endif


    #ifdef DEBUG
    #undef INFO
    #endif
}

void HC::GWindow::validateWindowDetails(HC::WindowDetails detailsValid) const {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);

    #ifdef DEBUG
    #define INFO(MESSAGE) MSG("GWindow", "validateWindowDetails", "INFO", MESSAGE)
    #define ERR(MESSAGE) MSG("GWindow", "validateWindowDetails", "ERROR", MESSAGE)
    #endif

    if(details.width < 0){
    #ifdef DEBUG
        ERR("Error the GWindow width can't be less than 0") END
    #endif

    exit(1);
    }

    if(details.width > mode.w){
    #ifdef DEBUG
        ERR("Error the GWindow width can't be greater than the monitor width of ") << mode.w END;
    #endif

        exit(1);
    }

    if(details.height < 0){
    #ifdef DEBUG
        ERR("Error the GWindow height can't be less than 0") END
    #endif

        exit(1);
    }

    if(details.height > mode.h){
    #ifdef DEBUG
        ERR("Error the GWindow width can't be greater than the monitor height of ") << mode.h END;
    #endif

        exit(1);
    }

    if(details.xPos < 0){
    #ifdef DEBUG
        ERR("Error the GWindow x cord can't be less than 0") END
    #endif

        exit(1);
    }

    if(details.xPos > mode.w && (details.xPos & SDL_WINDOWPOS_CENTERED) != SDL_WINDOWPOS_CENTERED){
    #ifdef DEBUG
        ERR("Error the GWindow x cord can't be greater than the monitor width of ") << mode.w END;
    #endif

        exit(1);
    }

    if(details.yPos < 0){
    #ifdef DEBUG
        ERR("Error the GWindow y cord can't be less than 0") END
    #endif

        exit(1);
    }

    if(details.yPos > mode.h && (details.yPos & SDL_WINDOWPOS_CENTERED) != SDL_WINDOWPOS_CENTERED){
    #ifdef DEBUG
        ERR("Error the GWindow y cord can't be greater than the monitor height of ") << mode.h END;
    #endif

        exit(1);
    }

}
