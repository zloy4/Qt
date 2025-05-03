#ifndef GRAPHICCONTROLLER_H
#define GRAPHICCONTROLLER_H

#include <QObject>
#include <QColor>
#include "graphicmodel.h"
#include "shape.h"
#include <QUndoStack>  // Для работы с undo/redo


enum class EditorMode { Select, CreateLine, CreateRect, CreateEllipse, CreateText, CreateTrapezoid };

class GraphicController : public QObject {
    Q_OBJECT
public:
    explicit GraphicController(GraphicModel* model, QObject* parent = nullptr);

    void setEditorMode(EditorMode mode);
    void setCurrentColor(const QColor& color);
    void setCurrentText(const QString& text);
    QColor getCurrentColor() const;
    void changeSelectedItemsColor(const QColor& color);

    void mousePressed(const QPointF& pos);
    void mouseMoved(const QPointF& pos);
    void mouseReleased();

    void deleteSelectedItems();
    void clearAll();
    void undo();
    void redo();

private:
    GraphicModel* model;
    EditorMode currentMode;
    QColor currentColor;
    QString currentText;
    Shape* currentShape;
    bool isDrawing;
    bool isMoving;
    Shape* selectedShape;
    QUndoStack* undoStack;
    QUndoStack* redoStack;
};

#endif // GRAPHICCONTROLLER_H
