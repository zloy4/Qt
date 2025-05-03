#include "removeshapcommand.h"

RemoveShapeCommand::RemoveShapeCommand(GraphicModel* model, Shape* shape, QUndoCommand* parent)
    : QUndoCommand(parent), model(model), shape(shape) {}

void RemoveShapeCommand::undo() {
    model->addShape(shape->getType(), shape->boundingRect().topLeft(), shape->getColor());  // При отмене добавляем фигуру обратно
}

void RemoveShapeCommand::redo() {
    model->removeShape(shape);  // При повторе удаляем фигуру
}
