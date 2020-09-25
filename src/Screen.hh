#ifndef SCREEN_H
#define SCREEN_H

#include "Bullet.hh"

/**
 * Like a state that the game can be in. Screens can be stacked and return info
 * back to one another kind of like function calls.
 */
class Screen {
    public:
	/**
	 * Tells you how many milliseconds each frame of this screen is supposed to
	 * be. The way they are going to be run is that they will not be fixed
	 * at their timestep but in aggregate the right amount of them will
	 * have been run to get it up to speed.
	 * @return the amount of time each one should last for in milliseconds.
	 */
	virtual int getTimestep() const = 0;

	/**
	 * Updates the screen for one timestep's worth.
	 * @return a code meaning that the screen is finished in some way.
	 */
	virtual int update() = 0;

	/**
	 * Renders the screen.
	 * @param renderer is the renderer that does some stuff.
	 */
	virtual void render(SDL_Renderer &renderer) const = 0;
};

/**
 * A screen that does nothing except execute a script and set up other screens.
 */
class BlankScreen: public Screen {
    public:
	int getTimestep() const override;

	int update() override;

	void render(SDL_Renderer &renderer) const override;
};

/**
 * A screen which makes a bunch of stuff fly around the screen wahooo.
 */
class TestScreen: public Screen {
    public:
	const int n;

	/**
	 * Creates a nice test screen.
	 * @param n     is the number of objects to test.
	 * @param atlas is the texture containing the images.
	 */
        TestScreen(int n, SDL_Texture &atlas);

	/**
	 * Deletes the bullet array.
	 */
	~TestScreen();

	int getTimestep() const override;

	int update() override;

	void render(SDL_Renderer &renderer) const override;

    private:
	Bullet *bullets;
	SDL_Texture &atlas;
};

/**
 * A screen that contains a level that you can play around in.
 */
class LevelScreen: public Screen {
    public:
	int getTimestep() const override;

	int update() override;

	void render(SDL_Renderer &renderer) const override;
};

#endif