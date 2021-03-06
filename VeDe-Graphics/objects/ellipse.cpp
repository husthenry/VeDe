#include "ellipse.h"
#include "converters.h"
#include "helpers.h"
#include <QPointF>
#include <QtMath>

gx::Ellipse::Ellipse()
    :Ellipse(Vertex(), Vertex())
{
}

gx::Ellipse::Ellipse(Vertex center, Vertex radius)
    :m_center(center), m_radius(radius)
{
}

gx::Vertex gx::Ellipse::center() const
{
    return m_center;
}

void gx::Ellipse::setCenter(const Vertex &center)
{
    preChange();
    m_center = center;
    changed();
}

gx::Vertex gx::Ellipse::radius() const
{
    return m_radius;
}

void gx::Ellipse::setRadius(const Vertex &radius)
{
    preChange();
    m_radius = radius;
    changed();
}

void gx::Ellipse::updateControlPoints()
{
    ControlPoint *forWidth = new ControlPoint(m_center - Vertex(m_radius.x(), 0));
    ControlPoint *forHeight = new ControlPoint(m_center - Vertex(0, m_radius.y()));

    auto updateRadius = [this](Vertex m) {
        m_radius = m_radius - m;
    };

    forWidth->onMove() += updateRadius;
    forWidth->setVertical(false);

    forHeight->onMove() += updateRadius;
    forHeight->setHorizontal(false);

    addControlPoint(forWidth);
    addControlPoint(forHeight);
}

QRectF gx::Ellipse::shapeBoundingBox() const
{
    QPointF center = Converters::toPoint(this->center());
    QPointF radii = Converters::toPoint(this->radius());
    QRectF rect(center - radii, center + radii);
    fixBoxForStrokeWidth(rect);
    return getTransform().mapRect(rect);
}

bool gx::Ellipse::shapeContainsPoint(const gx::Vertex &point) const
{
//    gx::Vertex tc = center().transformed(getTransform());
//    gx::Vertex tp = point;
//    double xCoef = qPow(tp.x() - tc.x(), 2) / qPow(radius().x(), 2);
//    double yCoef = qPow(tp.y() - tc.y(), 2) / qPow(radius().y(), 2);
//    return (xCoef + yCoef) <= 1;
    return shapeBoundingBox().contains(Converters::toPoint(point));
}
