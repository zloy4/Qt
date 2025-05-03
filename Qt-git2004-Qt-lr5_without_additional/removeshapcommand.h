#ifndef REMOVESHAPECOMMAND_H
#define REMOVESHAPECOMMAND_H

#include <QUndoCommand>
#include "graphicmodel.h"
#include "shape.h"

class RemoveShapeCommand : public QUndoCommand {
public:
    RemoveShapeCommand(GraphicModel* model, Shape* shape, QUndoCommand* parent = nullptr);
    void undo() override;
    void redo() override;

private:
    GraphicModel* model;
    Shape* shape;
};

#endif // REMOVESHAPECOMMAND_H
