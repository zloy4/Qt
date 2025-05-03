#include "graphiccontroller.h"
#include <QInputDialog>
#include <QUndoCommand>  // Для создания команд
#include "addshapcommand.h"   // Добавьте эти заголовки
#include "removeshapcommand.h"

GraphicController::GraphicController(GraphicModel* model, QObject* parent)
    : QObject(parent), model(model), currentMode(EditorMode::Select),
      currentColor(Qt::black), currentShape(nullptr), isDrawing(false),
      isMoving(false), selectedShape(nullptr) {}
    undoStack = new QUndoStack(this);  // Создание стека для undo
    redoStack = new QUndoStack(this); 

void GraphicController::setEditorMode(EditorMode mode) {
    currentMode = mode;
}

void GraphicController::setCurrentColor(const QColor& color) {
    currentColor = color;
}
void GraphicController::undo() {
    undoStack->undo();  // Отменить последнюю команду
}

void GraphicController::redo() {
    redoStack->redo();  // Повторить последнюю отмененную команду
}

void GraphicController::setCurrentText(const QString& text) {
    currentText = text;
}

QColor GraphicController::getCurrentColor() const {
    return currentColor;
}

void GraphicController::changeSelectedItemsColor(const QColor& color) {
    for (Shape* shape : model->getShapes()) {
        if (shape->isSelected()) {
            shape->setColor(color);
        }
    }
}

void GraphicController::mousePressed(const QPointF& pos) {
    if (currentMode == EditorMode::Select) {
        // Логика для выбора фигуры
    } else {
        Shape* newShape = nullptr;

        switch (currentMode) {
        case EditorMode::CreateLine:
            newShape = new Shape(ShapeType::Line, pos, currentColor);
            break;
        case EditorMode::CreateRect:
            newShape = new Shape(ShapeType::Rectangle, pos, currentColor);
            break;
        case EditorMode::CreateEllipse:
            newShape = new Shape(ShapeType::Ellipse, pos, currentColor);
            break;
        case EditorMode::CreateText: {
            bool ok;
            QString text = QInputDialog::getText(nullptr, "Enter Text", "Text:", QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty()) {
                newShape = new Shape(ShapeType::Text, pos, currentColor);
                newShape->setText(text);
            }
            break;
        }
        case EditorMode::CreateTrapezoid:
            newShape = new Shape(ShapeType::Trapezoid, pos, currentColor);
            break;
        default:
            return;
        }

        // Добавление команды в стек
        AddShapeCommand* command = new AddShapeCommand(model, newShape);
        undoStack->push(command);  // Добавляем команду в undoStack
        currentShape = newShape;  // Поддерживаем текущую фигуру
    }
}


void GraphicController::mouseMoved(const QPointF& pos) {
    if (isMoving && selectedShape) {
        selectedShape->setPos(pos - selectedShape->boundingRect().center());
    }
    else if (isDrawing && currentShape) {
        currentShape->setEndPos(pos);
    }
}

void GraphicController::mouseReleased() {
    isDrawing = false;
    isMoving = false;
    currentShape = nullptr;
    selectedShape = nullptr;
}

void GraphicController::deleteSelectedItems() {
    QList<Shape*> toRemove;
    for (Shape* shape : model->getShapes()) {
        if (shape->isSelected()) {
            toRemove.append(shape);
        }
    }

    for (Shape* shape : toRemove) {
        model->removeShape(shape);
    }
}

void GraphicController::clearAll() {
    model->clear();
}
