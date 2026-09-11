// main.cpp
#include "Macropad.hpp"

extern "C" void app_main(void) {
    static Macropad pad; // static: lives for program lifetime, avoids stack placement
    pad.init();
    pad.run();
}