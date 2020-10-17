#ifndef GUI_H
#define GUI_H

#include <vector>

/**
 * An element of the gui.
 */
class GuiElement {
    public:
        std::vector<GuiElement> children;
};

/**
 * Stores gui shiet.
 */
class Gui {
    public:
        Gui();


    private:
        std::vector<GuiElement> items
};

#endif
