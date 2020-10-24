#ifndef SCREEN_H
#define SCREEN_H

#include "Bullet.hh"
#include "Renderer.hh"
#include "janet.h"
#include <vector>

#define MILL_TO_SEC(X) ((float)X / 1000)

/**
 * Like a state that the game can be in. Screens can be stacked and return info
 * back to one another kind of like function calls.
 */
class Screen {
    public:
        /**
         * Represents a deferred drawing operation.
         */
        class DrawOperation {
            public:
                enum {
                    BORDER,
                    RECT,
                    TEXT
                } type;
                SDL_Rect sprite;
                SDL_Rect bounds;
                int width;
                char const *text;
        };

        /**
         * Represents transferring from one screen to another in some way.
         */
        class TransferOperation {
            public:
                enum {
                    POP,
                    PUSH,
                    REPLACE,
                    NONE
                } type;
                Screen *next;
        };

        /**
         * Deletes all the screen's shiet.
         */
        virtual ~Screen();

        /**
         * Sets this screens transfer to be pushing a new screen on top of it.
         * @param screen is the screen to push on top.
         */
        void push(Screen *screen);

        /**
         * Sets this screens transfer to be it being removed from the screen
         * stack.
         */
        void pop();

        /**
         * Sets this screens transfer to be replacing it with a different
         * screen.
         * @param screen is the replacement.
         */
        void replace(Screen *screen);

        /**
         * Generic updating logic.
         * @return response code thing.
         */
        TransferOperation update();

	/**
	 * Renders the screen.
	 * @param renderer is the renderer that does some stuff.
	 */
	void render(Renderer const &renderer);

	/**
	 * Updates the screen for one timestep's worth.
	 * @return a code meaning that the screen is finished in some way.
	 */
	virtual void customUpdate();

        /**
         * Renders the stuff that you actually want to render in the given
         * screen.
         * @param renderer is used for rendering stuff.
         */
        virtual void customRender(Renderer const &renderer) const;

	/**
	 * Tells you how many milliseconds each frame of this screen is
         * supposed to be. The way they are going to be run is that they will
         * not be fixed at their timestep but in aggregate the right amount of
         * them will have been run to get it up to speed.
	 * @return the amount of time each one should last for in milliseconds.
	 */
	virtual int getTimestep() const = 0;

        /**
         * Queues the current top screen to remove itself from the screen
         * stack.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet pushTrans(int32_t argc, Janet *argv);

        /**
         * Queues the current top screen to remove itself from the screen
         * stack.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet popTrans(int32_t argc, Janet *argv);

        /**
         * Queues the current top screen to remove itself from the screen
         * stack.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet replaceTrans(int32_t argc, Janet *argv);

        /**
         * Creates a blank screen with an arbitrary number of string arguments
         * and returns a pointer to it.
         * @param argc is the number of arguments.
         * @param argv is the arguments.
         * @return a pointer to the new blank screen.
         */
        static Janet newBlank(int32_t argc, Janet *argv);

        /**
         * Adds a border to draw to the screen's draw queue from janet.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet drawBorder(int32_t argc, Janet *argv);

        /**
         * Adds a rect to draw to the screen's draw queue from janet.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet drawRect(int32_t argc, Janet *argv);
        
        /**
         * Adds a Text draw to the screen draw queue from janet.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet drawText(int32_t argc, Janet *argv);

        /**
         * Gives you a sprite by it's name.
         * @param argc is the number of arguments it is called with.
         * @param argv is the list of argumnets given.
         * @return the stuff to send back to janet.
         */
        static Janet getSprite(int32_t argc, Janet *argv);

        /**
         * Tells you the dimensions of the logical screen.
         * @param argc is the number of arguments.
         * @param argv is the list of arguments.
         * @return the stuff to send back to janet.
         */
        static Janet getScreenDimensions(int32_t argc, Janet *argv);

        /**
         * Adds all of the screen janet script functions to the screen module
         * of janet.
         */
        static void initScripting();

    protected:
        /**
         * Loads a script that contains a function that takes a pointer to this
         * screen as an argument.
         * @param file is the path to the file containing the script.
         * @param argc is the number of extra arguments to the script.
         * @param argv is the values of the extra arguments to the script.
         * @return the fiber unless you really fuck up in which case it returns
         *         null.
         */
        JanetFiber *loadFiber(char const *file, int argc, char const **argv);

    private:
        std::vector<DrawOperation> drawQueue;
        TransferOperation transfer;
};

/**
 * A screen that does nothing except execute a script and set up other screens.
 */
class BlankScreen: public Screen {
    public:
        /**
         * Creates the blank screen by providing the script it will run.
         * @param script is the path to the script it will run.
         * @param argc   is the number of arguments to the script to add.
         * @param argv   is the list of arguments to the script.
         */
        BlankScreen(
            char const *script,
            int argc,
            char const **argv
        );

        /**
         * Deletes stuff.
         */
        virtual ~BlankScreen();

	int getTimestep() const override;

	void customUpdate() override;

    private:
        JanetFiber *script;
};

/**
 * A screen that contains a platform level that you can play around in.
 */
class PlatformScreen: public Screen {
    public:
	int getTimestep() const override;

	void customUpdate() override;

	void customRender(Renderer const &renderer) const override;
};

/**
 * A screen which makes a bunch of stuff fly around the screen wahooo.
 */
class TestScreen: public Screen {
    public:
	const int n;

	/**
	 * Creates a nice test screen.
	 * @param n    is the number of objects to test.
	 */
        TestScreen(int n);

	/**
	 * Deletes the bullet array.
	 */
	virtual ~TestScreen();

	int getTimestep() const override;

	void customUpdate() override;

	void customRender(Renderer const &renderer) const override;

    private:
        Instance<Bullet> *bullets;
};

#endif
