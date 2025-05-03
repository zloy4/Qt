#ifndef ADDSHAPECOMMAND_H
#define ADDSHAPECOMMAND_H

#include <QUndoCommand>
#include "graphicmodel.h"
#include "shape.h"

class AddShapeCommand : public QUndoCommand {
public:
    AddShapeCommand(GraphicModel* model, Shape* shape, QUndoCommand* parent = nullptr);
    void undo() override;
    void redo() override;

private:
    GraphicModel* model;
    Shape* shape;
};

#endif // ADDSHAPECOMMAND_H
