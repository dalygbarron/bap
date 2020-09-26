#ifndef VEC_H
#define VEC_H

class Vec {
    public:
        float x;
        float y;

        /**
         * Makes an origin vector.
         */
        Vec();

        /**
         * Creates a vector where both axes are the same.
         * @param value is the value to give to both.
         */
        Vec(float value);

        /**
         * Creates a vector with a different value on each axis.
         * @param x is the x axis.
         * @param y is the y axis.
         */
        Vec(float x, float y);

        /**
         * Adds another vector to this vector.
         * @param other is the vector to add.
         */
        void add(Vec other);

        /**
         * Subtracts a vector from this vector.
         * @param other is the vector subtract.
         */
        void sub(Vec other);

        /**
         * Multiplies this vector by another vector.
         * @param other is the vector to multiply.
         */
        void mult(Vec other);

        /**
         * Divides this vector by another.
         * @param other is the one to divide this one by.
         */
        void div(Vec other);

        /**
         * Makes this vector be wrapped between another vector and the origin
         * point.
         * @param bounds is the vector to be wrapped in.
         */
        void wrap(Vec bounds);

        /**
         * Normalises this vector so that it's length is 1.
         */
        void normal();

        /**
         * Gives you the length squared of the vector which is faster to
         * calculate.
         * @return the length of the vector squared.
         */
        float squareLength();

        /**
         * Tells you the length of this vector which is the distance from the
         * origin point to the point at the end of this vector.
         * @return the length of the vector.
         */
        float length();
};

#endif
