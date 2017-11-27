#ifndef STARRATING_H
#define STARRATING_H

#include <QMetaType>
#include <QPointF>//使用浮点精度定义平面上的一个点
#include <QVector>
#include <QPainter>

class StarRating
{
public:
    enum EditMode{Editable, ReadOnly};
    explicit StarRating(int starCount = 1, int maxStarCount = 5);
    void paint(QPainter *painter, const QRect &rect,
               const QPalette &palette, EditMode mode) const;
    QSize sizeHint() const;

    int starCount() const {return myStarCount;}
    int maxStarCount() const { return myMaxStarCount; }
    void setStarCount(int starCount) { myStarCount = starCount; }
    void setMaxStarCount(int maxStarCount) { myMaxStarCount = maxStarCount; }

private:
    //QPolygonF == QVector<QPointF>
    QPolygonF starPolygon;
    QPolygonF diamondPolygon;
    int myStarCount;
    int myMaxStarCount;//最大星
};

//Q_DECLARE_METATYPE(Type) 该宏使type能够被元对象类型感知，需要在QVariant中使用type做为自定义的类型
Q_DECLARE_METATYPE(StarRating)

#endif // STARRATING_H
