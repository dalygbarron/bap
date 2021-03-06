#include "Vec.hh"
#include <cmath>

Vec::Vec() {
    this->x = 0;
    this->y = 0;
}

Vec::Vec(float value) {
    this->x = value;
    this->y = value;
}

Vec::Vec(float x, float y) {
    this->x = x;
    this->y = y;
}

int Vec::iX() const {
    return static_cast<int>(this->x);
}

int Vec::iY() const {
    return static_cast<int>(this->y);
}


void Vec::add(Vec other) {
    this->x += other.x;
    this->y += other.y;
}

void Vec::sub(Vec other) {
    this->x -= other.x;
    this->y -= other.y;
}

void Vec::mult(Vec other) {
    this->x *= other.x;
    this->y *= other.y;
}

void Vec::div(Vec other) {
    this->x /= other.x;
    this->y /= other.y;
}

void Vec::wrap(Vec other) {
    if (this->x >= other.x) this->x -= other.x;
    else if (this->x < 0) this->x += other.x;
    if (this->y >= other.y) this->y -= other.y;
    else if (this->y < 0) this->y += other.y;
}

void Vec::normal() {
    float length = this->length();
    if (length == 0) return;
    this->x /= length;
    this->y /= length;
}

float Vec::squareLength() const {
    return this->x * this->x + this->y * this->y;
}

float Vec::length() const {
    return sqrt(this->squareLength());
}
