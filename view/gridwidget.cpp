#include "gridwidget.h"
#include <QPen>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>

GridWidget::GridWidget(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    setMinimumSize(300, 300);
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void GridWidget::paint(QPainter* painter,  const QStyleOptionGraphicsItem* option, QWidget* widget) {
    // Отрисовка координатной сетки

    QGraphicsWidget::paint(painter, option, widget);
    int gridSize = 50;
    QPen pen(Qt::gray);
    painter->setPen(pen);

    // Вертикальные линии
    for (int x = 0; x <= 300; x += gridSize) {
        painter->drawLine(x, 0, x, 300);
    }

    // Горизонтальные линии
    for (int y = 0; y <= 300; y += gridSize) {
        painter->drawLine(0, y, 300, y);
    }
}

