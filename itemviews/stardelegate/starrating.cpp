#include "starrating.h"
#include <cmath>
#include <QtWidgets>

const int PaintingScaleFactor = 20;//绘制比例因子

StarRating::StarRating(int starCount, int maxStarCount)
{
    myStarCount = starCount;
    myMaxStarCount = maxStarCount;

    starPolygon << QPointF(1.0, 0.5);//基准点？
    for(int i = 1; i< 5; ++i)
    {
         starPolygon << QPointF(0.5 + 0.5 * std::cos(0.8 * i * 3.14),
                                   0.5 + 0.5 * std::sin(0.8 * i * 3.14));
    }

    diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4)
                   << QPointF(0.6, 0.5) << QPointF(0.5, 0.6)
                   << QPointF(0.4, 0.5);
}

QSize StarRating::sizeHint() const
{
    return PaintingScaleFactor * QSize(myMaxStarCount, 1); //QSize(int width, int height)
}

void StarRating::paint(QPainter *painter, const QRect &rect,
                       const QPalette &palette, EditMode mode) const
{
    painter->save();//保存当前painter状态
    //QPainter::Antialiasing  指示引擎如果可能的情况下应平滑基元边缘
    painter->setRenderHint(QPainter::Antialiasing, true);//在painter中设定给定的render线索？如果参数2为真
    painter->setPen(Qt::NoPen);
    if(mode == Editable)
    {
        painter->setBrush(palette.highlight());//highlight() 返回当前颜色组的高亮画刷
    }
    else
    {
        //返回windows text画刷，通常是前景色给当前颜色组
         painter->setBrush(palette.foreground());
    }

    int yOffset = (rect.height() - PaintingScaleFactor) / 2;
    painter->translate(rect.x(), rect.y() + yOffset); //通过给定的偏移量转换坐标系统，给定的偏移量添加至points
    painter->scale(PaintingScaleFactor, PaintingScaleFactor);//根据缩放因子缩放坐标系统
    for(int i = 0; i < myMaxStarCount; i++)
    {
        if(i < myStarCount)
        {
             painter->drawPolygon(starPolygon, Qt::WindingFill);
        }
        else if (mode == Editable)
        {
            //http://blog.csdn.net/lwbeyond/article/details/41479809
            painter->drawPolygon(diamondPolygon, Qt::WindingFill); //暂时没看懂
        }
        painter->translate(1.0, 0.0);
    }
    painter->restore();
}
