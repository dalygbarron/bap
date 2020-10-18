#ifndef GUI_H
#define GUI_H

/**
 * Contains nice functions for rendering gui stuff.
 */
namespace Gui {
    public:
        /**
         * Creates the gui thingy.
         */
        Gui();

        /**
         * Places a gui thingy on the screen in some place, then returns if
         * there is a user interaction result.
         * @param bounds is the bounds within which to fit the gui thingy.
         * @param item   is basically the gui item to fit.
         * @return a result from gui items or a value less than 0 if there was
         *         none.
         */
        int place(SDL_Rect bounds, SDL_Rect item);

        /**
         * Creates a panel that is containing other stuff.
         * @param child is as many children as you want the panel to have.
         */
        SDL_Rect panel(SDL_Rect child...);

        SDL_Rect button(SDL_Rect child);


    private:
        int result;

        /**
         * Tries to set a gui interaction result.
         * @param result is the result to set but if one is already set nothing
         *               happens.
         */
        void setResult(int result);
};

#endif
