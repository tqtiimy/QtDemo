#include "stardelegate.h"
#include "starrating.h"
#include "stareditor.h"

void StarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().canConvert<StarRating>())
    {
        StarRating starRating = qvariant_cast<StarRating>(index.data());
        if(option.state & QStyle::State_Selected)
        {
            //fillRect(rectangle, brush) 用指定画刷填充rectangle区域
            painter->fillRect(option.rect, option.palette.highlight());
        }

        starRating.paint(painter, option.rect, option.palette, StarRating::ReadOnly);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize StarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //index用于定位model中数据
    //option 用于描述参数，该参数用于在view widget中绘制item
    if(index.data().canConvert<StarRating>())
    {
        StarRating starRating = qvariant_cast<StarRating>(index.data());//返回给定的值转换成模版参数 StarRating
        return starRating.sizeHint();
    }
    else
    {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

QWidget *StarDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    if(index.data().canConvert<StarRating>())
    {
        StarEditor *editor = new StarEditor(parent);
        connect(editor, &StarEditor::editingFinished, this, &StarDelegate::commitAndCloseEditor);
        return editor;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void StarDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{//设置 数据模型item中通过editor展示和编辑的数据，该item由index指定
    if(index.data().canConvert<StarRating>())
    {
        StarRating starRating = qvariant_cast<StarRating>(index.data());
        StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
        starEditor->setStarRating(starRating);
        //QObject *obj = new QTimer;     // QTimer inherits QObject
        //QTimer *timer = qobject_cast<QTimer *>(obj);
        //T qobject_cast(QObject *object)  返回给定的对象转换成类型T
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void StarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    if(index.data().canConvert<StarRating>())
    {
        StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
        model->setData(index, QVariant::fromValue(starEditor->starRating()));//Q_DECLARE_METATYPE(StarRating)
    }
    else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void StarDelegate::commitAndCloseEditor()
{

}

