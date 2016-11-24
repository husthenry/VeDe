#ifndef CANVAS_H
#define CANVAS_H

#include "gobject.h"
#include "layer.h"
#include "commands/command.h"
#include <memory>
#include <QVector>
#include <QEvent>

namespace gx
{
//Forward decl.
class Tool;

class Canvas
{
public:
    Canvas();
    Canvas(std::unique_ptr<GObject> *root);
    virtual ~Canvas();

    /**
     * @brief Gets the root object of the canvas
     * @return The root GObject
     */
    std::unique_ptr<GObject> const& root();

    /**
     * @brief Get the mouse cursor positon relative to the canvas
     * @return A vertex containing the relative position
     */
    virtual Vertex getCursor() const = 0;

    int executeCommand(Command* command);
    int undoCommand();
    void handleEvent(QEvent const &event);
    virtual void redraw() = 0;
    void addToCurrLayer(std::shared_ptr<GObject> object);

private:
    void initCommon();

private:
    std::unique_ptr<GObject> m_root;
    QVector<Command*> m_commandHistory;
    unsigned int m_currCommand;
    Tool* m_currTool;
    Layer* m_currLayer;
};
}

#endif // CANVAS_H