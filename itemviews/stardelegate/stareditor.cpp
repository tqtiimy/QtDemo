#include "stareditor.h"
#include <QMouseEvent>

StarEditor::StarEditor(QWidget *parent)
    :QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}

QSize StarEditor::sizeHint() const
{
    return myStarRating.sizeHint();
}

void StarEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    myStarRating.paint(&painter, rect(), this->palette(), StarRating::Editable);
}

void StarEditor::mouseMoveEvent(QMouseEvent *event)
{
    int star = starAtPosition(event->x());
    if(star != myStarRating.starCount() && star != -1)
    {
        myStarRating.setStarCount(star);
        update();
    }
}

void StarEditor::mouseReleaseEvent(QMouseEvent *)
{
    emit editingFinished();
}

int StarEditor::starAtPosition(int x)
{
    int star = (x / (myStarRating.sizeHint().width() / myStarRating.maxStarCount()/* 单个星的宽度*/)) + 1;
    if(star <= 0 || star > myStarRating.maxStarCount())
    {
        return -1;
    }

    return star;
}
