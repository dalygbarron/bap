#include "Gui.hh"

Gui::Gui() {}

int Gui::place(SDL_Rect bounds, SDL_Rect item) {
    this->bounds = bounds;
    this->result = -1;
}

SDL_Rect Gui::panel(SDL_Rect child...) {

}

void Gui::setResult(int result) {

}
