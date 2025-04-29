#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

enum class ShapeType { Line, Rectangle, Ellipse, Text };

class Shape : public QGraphicsItem {
public:
    Shape(ShapeType type, const QPointF& startPos, const QColor& color, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setEndPos(const QPointF& endPos);
    void setText(const QString& text);
    void setColor(const QColor& color);
    void setEditing(bool editing);

    ShapeType getType() const;
    QColor getColor() const;
    QString getText() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    enum ResizeHandle { None, TopLeft, TopRight, BottomLeft, BottomRight };
    ResizeHandle getResizeHandle(const QPointF& pos) const;
    QRectF getHandleRect(ResizeHandle handle) const;

    ShapeType type;
    QPointF startPos;
    QPointF endPos;
    QColor color;
    QString text;
    bool isEditing;
    ResizeHandle currentHandle;
    bool isResizing;
    QPointF resizeStartPos;
    QPointF resizeStartEnd;
};

#endif // SHAPE_H
