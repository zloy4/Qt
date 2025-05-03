#include "addshapcommand.h"

AddShapeCommand::AddShapeCommand(GraphicModel* model, Shape* shape, QUndoCommand* parent)
    : QUndoCommand(parent), model(model), shape(shape) {}

void AddShapeCommand::undo() {
    model->removeShape(shape);  // При отмене удаляем фигуру
}

void AddShapeCommand::redo() {
    model->addShape(shape->getType(), shape->boundingRect().topLeft(), shape->getColor());  // Повторное добавление
}
