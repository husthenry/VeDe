#ifndef IPAINTER_H
#define IPAINTER_H

#include "vertex.h"

namespace gx
{
class CustomPainter
{
public:
    virtual void drawLine(float x1, float y1, float x2, float y2) = 0;
    void drawLine(Vertex start, Vertex end);

    virtual void drawEllipse(float cX, float cY, float rX, float rY) = 0;
    void drawEllipse(Vertex center, Vertex radius);
};
}

#endif // IPAINTER_H
