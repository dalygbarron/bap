#include "Screen.hh"

#define STEP 17
#define SECOND_STEP 0.017

TestScreen::TestScreen(Sack const &sack, int n):
    Screen(sack),
    n(n)
{
    int width = sack.atlas->getWidth();
    int height = sack.atlas->getHeight();
    this->bullets = new Bullet[n];
    for (int i = 0; i < n; i++) {
	this->bullets[i].alive = true;
	this->bullets[i].x = rand() % 768;
	this->bullets[i].y = rand() % 480;
	this->bullets[i].vX = rand() % 20 - 10;
	this->bullets[i].vY = rand() % 20 - 10;
	this->bullets[i].gX = rand() % 20 - 10;
	this->bullets[i].gY = rand() % 20 - 10;
	this->bullets[i].sprite.w = rand() % width / 7;
	this->bullets[i].sprite.h = rand() % height / 7;
	this->bullets[i].sprite.x = rand() % (width - this->bullets[i].sprite.w);
	this->bullets[i].sprite.y = rand() % (height - this->bullets[i].sprite.h);
    }
}
    
TestScreen::~TestScreen() {
    delete this->bullets;
}

int TestScreen::getTimestep() const {
    return STEP;
}

int TestScreen::update() {
    for (int i = 0; i < this->n; i++) {
	this->bullets[i].x += this->bullets[i].vX * SECOND_STEP;
	this->bullets[i].y += this->bullets[i].vY * SECOND_STEP;
	this->bullets[i].vX += this->bullets[i].gX * SECOND_STEP;
	this->bullets[i].vY += this->bullets[i].gY * SECOND_STEP;
	if (this->bullets[i].x >= 768) this->bullets[i].x -= 768;
	if (this->bullets[i].y >= 480) this->bullets[i].y -= 480;
	if (this->bullets[i].x < 0) this->bullets[i].x += 768;
	if (this->bullets[i].y < 0) this->bullets[i].y += 480;
    }
    return 0;
}

void TestScreen::render(SDL_Renderer &renderer) const {
    SDL_Rect placement;
    for (int i = 0; i < this->n; i++) {
        this->sack.atlas->draw(
            renderer,
            this->bullets[i].x,
            this->bullets[i].y,
            this->bullets[i].sprite
        );
    }
}
