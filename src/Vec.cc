#include "Vec.hh"

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

void Vec::normal() {
    float length = this->length();
    if (length == 0) return;
    this->x /= length;
    this->y /= length;
}

float Vec::squareLength() {
    return this->x * this->x + this->y * this->y;
}

float Vec::length() {
    return sqrt(this->squareLength());
}
