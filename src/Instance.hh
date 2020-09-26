#ifndef INSTANCE_H
#define INSTANCE_H

/**
 * Instance of something that exists in 2d space. Basically it's like that
 * flyweight pattern and this is the fly, it can be for either bullets or
 * freaks. Also, since these are often going to be pooled, it cannot have any
 * constant fields.
 */
template <class T> class Instance {
    public:
        bool alive;
        Vec position;
        Vec velocity;
        T const *model;
};

#endif
