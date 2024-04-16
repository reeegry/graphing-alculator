#include <QGraphicsWidget>

#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

class GridWidget : public QGraphicsWidget
{
public:
    GridWidget(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // GRIDWIDGET_H
