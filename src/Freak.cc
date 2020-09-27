#include "Freak.hh"

static std::unordered_map<std::string, Freak::Behaviour> const BEHAVIOURS = {
    {"player", Freak::Behaviour::PLAYER},
    {"static", Freak::Behaviour::STATIC}
};

Freak::Freak(
    std::string name,
    SDL_Rect sprite,
    float gravity,
    Behaviour behaviour
) {
    this->name = name;
    this->sprite = sprite;
    this->gravity = gravity;
    this->behaviour = behaviour;
}

Freak::Behaviour Freak::stringToBehaviour(std::string string) {
    if (BEHAVIOURS.count(string) > 0) return BEHAVIOURS.at(string);
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        "'%s' is not a valid behaviour name\n",
        string.c_str()
    );
    return Behaviour::STATIC;
}

