#ifndef FREAK_H
#define FREAK_H

/**
 * A character that can move around in the level.
 */
class Freak {
    public:
        enum class Behaviour {
            PLAYER,
            STATIC
        };

        /**
         * Creates a freak and sets all it's stuff.
         * @param name      is the name which might get used somewhere like the
         *                  editor.
         * @param sprite    is the sprite of the freak.
         * @param gravity   is a multiplier for the effect of gravity.
         * @param behaviour is how this freak behaves.
         */
        Freak(std::string name, SDL_Rect sprite, float gravity, Behaviour behaviour);

        /**
         * Takes a string and converts it to it's corresponding behaviour.
         * @param string is the string to convert.
         * @return the corresponding behaviour.
         */
        static Behaviour stringToBehaviour(std::string string);

    private:
        std::string name;
        SDL_Rect sprite;
        float gravity;
        Behaviour behaviour;


};

#endif
