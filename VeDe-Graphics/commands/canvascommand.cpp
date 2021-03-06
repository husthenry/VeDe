#include "canvascommand.h"

gx::CanvasCommand::CanvasCommand(gx::Canvas *canvas)
    :m_canvas(canvas)
{
}

gx::Canvas* gx::CanvasCommand::getCanvas() const
{
    return m_canvas;
}

void gx::CanvasCommand::setCanvas(Canvas* canvas)
{
    m_canvas = canvas;
}

void gx::CanvasCommand::setObjects(const QList<gx::SharedGObject> &objects)
{
    m_objects = objects;
}

const QList<gx::SharedGObject > &gx::CanvasCommand::getObjects() const
{
    return m_objects;
}

void gx::CanvasCommand::setObject(const gx::SharedGObject &object)
{
    m_objects.clear();
    m_objects.append(object);
}

int gx::CanvasCommand::execute()
{
    applyCommand(false);
}

int gx::CanvasCommand::undo()
{
    applyCommand(true);
}

int gx::CanvasCommand::applyCommand(bool reverse)
{
    QRectF redrawRect;
    int status = 0;
    foreach(auto& obj, m_objects)
    {
        status = executeOnObject(obj, redrawRect, reverse);

        if(status != 0) break;
    }

    getCanvas()->redraw(redrawRect);
    return status;
}
