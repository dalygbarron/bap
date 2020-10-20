#ifndef SCREEN_H
#define SCREEN_H

#include "Sack.hh"
#include "Bullet.hh"
#include "Renderer.hh"
#include "janet.h"
#include <queue>

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
                    PANEL,
                    TEXT
                } type;
                SDL_Rect sprite;
                SDL_Rect bounds;
                int width;
                char const *text;
        };

        /**
         * Makes all screens have access to the sprite atlas thing.
         * @param sack contains all the dependencies.
         */
        Screen(Sack const &sack);

	/**
	 * Renders the screen.
	 * @param renderer is the renderer that does some stuff.
	 */
	void render(Renderer const &renderer);

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
	 * Updates the screen for one timestep's worth.
	 * @return a code meaning that the screen is finished in some way.
	 */
	virtual int update() = 0;

    protected:
        Sack const &sack;
        std::queue<DrawOperation> drawQueue;

        /**
         * Loads a script that contains a function that takes a pointer to this
         * screen as an argument.
         * @param file is the path to the file containing the script.
         * @return the fiber unless you really fuck up in which case it returns
         *         null.
         */
        JanetFiber *loadFiber(char const *file);
};

/**
 * A screen that does nothing except execute a script and set up other screens.
 */
class BlankScreen: public Screen {
    public:
        /**
         * Creates the blank screen by providing the script it will run.
         * @param sack   contains shiet.
         * @param script is the path to the script it will run.
         */
        BlankScreen(Sack const &sack, std::string script);

	int getTimestep() const override;

	int update() override;

    private:
        JanetFiber *script;
};

/**
 * A screen that contains a platform level that you can play around in.
 */
class PlatformScreen: public Screen {
    public:
	int getTimestep() const override;

	int update() override;

	void customRender(Renderer const &renderer) const override;
};

/**
 * A screen where you design a platform level.
 */
class DesignScreen: public Screen {
    public:
        /**
         * Creates the screen and a default level to edit.
         * @param sack is the sack.
         */
        DesignScreen(Sack const &sack);

	int getTimestep() const override;

	int update() override;

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
         * @param sack contains all the dependencies.
	 * @param n    is the number of objects to test.
	 */
        TestScreen(Sack const &sack, int n);

	/**
	 * Deletes the bullet array.
	 */
	~TestScreen();

	int getTimestep() const override;

	int update() override;

	void customRender(Renderer const &renderer) const override;

    private:
        Instance<Bullet> *bullets;
};

#endif
