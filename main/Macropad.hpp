// Macropad.hpp
#pragma once

class Macropad {
public:
    void init();
    void run(); // blocking, never returns

private:
    void handleTouchpad();
};

