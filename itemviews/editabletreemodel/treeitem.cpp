#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
{
    itemData = data;
    parentItem = parent;
}

TreeItem::~TreeItem()
{
    //使用C++ delete操作符删除container里面所有项，基项类型必须为指针
    //note:该函数不会从container中移除项，只是做了delete操作，需要调用clear()在容器中移除所有项
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

int TreeItem::childCount() const
{
    return childItems.size();
}

int TreeItem::columnCount() const
{
    return itemData.count();//同size()
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if(position < 0 || position > childItems.size())
        return false;

    for(int row = 0; row < count; ++row)
    {
        QVector<QVariant> data(columns);//QVector(int size)
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);//给定pos处插入子Item
    }

    return true;
}

QVariant TreeItem::data(int volumn) const
{
    return itemData.value(volumn);
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if(column < 0 || column >= itemData.size())
    {
        return false;
    }

    itemData[column] = value;
    return true;
}

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

bool TreeItem::insertCloumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for(int colunm = 0; colunm < columns; ++colunm)
    {
        itemData.insert(position, QVariant());
    }

    foreach (TreeItem *child, childItems)//遍历子节点
        child->insertCloumns(position, columns);

    return true;
}

bool TreeItem::removeColumns(int position, int columns)
{
    if(position < 0 || position + columns > itemData.size())
        return false;

    for(int colunm = 0; colunm < columns; colunm++)
    {
        itemData.remove(position);
    }

    foreach (TreeItem *child, childItems) {
        child->removeColumns(position, columns);
    }

    return true;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for(int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
