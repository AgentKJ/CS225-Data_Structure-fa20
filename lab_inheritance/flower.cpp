/**
 * @file flower.cpp
 * Implementation of the Flower class.
 */

#include "flower.h"

#include <cmath>
#include <cstdio>

#include "circle.h"
#include "color.h"
#include "rectangle.h"
#include "triangle.h"

using cs225::PNG;
using cs225::HSLAPixel;

const int STEM_HEIGHT = 32;
const int STEM_WIDTH = 2;
const HSLAPixel STEM_COLOR = color::GREEN;

const int LEAF_WIDTH = 16;
const int LEAF_HEIGHT = 16;
const HSLAPixel LEAF_COLOR = color::GREEN;

const int PISTIL_RADIUS = 12;
const HSLAPixel PISTIL_COLOR = color::YELLOW;

const int PETAL_RADIUS = 2;
const HSLAPixel PETAL_COLOR = color::RED;

Flower::Flower(const Vector2& center)
      :stem(Vector2(center.x(), center.y() + STEM_HEIGHT / 2), STEM_COLOR, STEM_WIDTH, STEM_HEIGHT),
      pistil(Vector2(center.x(), center.y() - PISTIL_RADIUS / 2), PISTIL_COLOR, PISTIL_RADIUS),
      leaf(LEAF_COLOR,
               Vector2(center.x()-STEM_WIDTH/2+1, center.y()+STEM_HEIGHT/2+STEM_HEIGHT/4 - STEM_HEIGHT / 4),
               Vector2(center.x()-STEM_WIDTH/2+1 - LEAF_WIDTH, center.y()+STEM_HEIGHT/2+STEM_HEIGHT/4 - LEAF_HEIGHT),
               Vector2(center.x()-STEM_WIDTH/2+1 - LEAF_WIDTH / 2, center.y()+STEM_HEIGHT/2+STEM_HEIGHT/4))
{
}


void Flower::drawPetals(PNG* canvas, const Vector2& center, int x, int y) const
{
    Circle petal(center, PETAL_COLOR, PETAL_RADIUS);
    petal.set_center(Vector2(center.x() + x, center.y() + y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + x, center.y() - y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - x, center.y() + y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - x, center.y() - y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + y, center.y() + x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + y, center.y() - x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - y, center.y() + x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - y, center.y() - x));
    petal.draw(canvas);
}

void Flower::draw(PNG* canvas) const
{
    stem.draw(canvas);
    pistil.draw(canvas);
    leaf.draw(canvas);
    for (int x = 0; x < PISTIL_RADIUS; x++) {
        const double radius2 = PISTIL_RADIUS * PISTIL_RADIUS;
        const int y = static_cast<int>(sqrt(radius2 - (x * x)));
        drawPetals(canvas, pistil.center(), x, y);
    }
}
