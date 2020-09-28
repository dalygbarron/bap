#include "Screen.hh"

#define STEP 17
#define SECOND_STEP 0.017

TestScreen::TestScreen(Sack const &sack, int n):
    Screen(sack),
    n(n)
{
    int width = sack.atlas->getWidth();
    int height = sack.atlas->getHeight();
    this->bullets = new Instance<Bullet>[n];
    for (int i = 0; i < n; i++) {
	this->bullets[i].alive = true;
	this->bullets[i].position.x = rand() % 768;
	this->bullets[i].position.y = rand() % 480;
	this->bullets[i].velocity.x = rand() % 20 - 10;
	this->bullets[i].velocity.y = rand() % 20 - 10;
	this->bullets[i].accelerator.x = rand() % 20 - 10;
	this->bullets[i].accelerator.y = rand() % 20 - 10;
        this->bullets[i].model = &sack.bullets.at(0);
    }
    sack.playSong("assets/apacho.it");
}
    
TestScreen::~TestScreen() {
    delete this->bullets;
}

int TestScreen::getTimestep() const {
    return STEP;
}

int TestScreen::update() {
    for (int i = 0; i < this->n; i++) {
        this->bullets[i].update(SECOND_STEP);
        this->bullets[i].position.wrap({768, 480});
    }
    return 0;
}

void TestScreen::render(SDL_Renderer &renderer) const {
    for (int i = 0; i < this->n; i++) {
        this->sack.atlas->draw(
            renderer,
            this->bullets[i].position.x,
            this->bullets[i].position.y,
            this->bullets[i].model->getSprite()
        );
    }
}
