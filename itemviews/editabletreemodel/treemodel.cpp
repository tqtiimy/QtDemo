#include "treemodel.h"
#include "treeitem.h"

TreeModel::TreeModel(const QStringList &headers, const QString &data, QObject *parent)
        : QAbstractItemModel(parent)
{
    //foreach(variable, container)  variable是变量名或变量定义，container为Qt容器
    QVector<QVariant> rootData;
    foreach (QString header, headers)
    {
        rootData <<header;
    }

    rootItem = new TreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    //flags基类默认实现返回结合体 ItemIsEnabled(使能) ItemIsSelectable(item项可被选择)
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{//在orientation指定的header中返回由给定role和section确定的数据
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{//返回由给定row,column和parent index指定的模型项的index
    if(parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);

    if(childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }

}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if(!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if(parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{//即返回一个根节点下子节点的数目
    TreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return rootItem->columCount();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations; //凹陷，即树节点子节点的层级
    parents << parent; //parent为树的根节点
    indentations << 0;

    int number = 0;

    while (number < lines.count())
    {//遍历所有字符串
        int position;
        //计算每个字符串所处的层级位置，以字符串开头空格数为基准
        while (position)
        {
            if(lines[number].at(position) != ' ')
                break;
            ++position;
        }
        //mid(int pos, int n = -1) 返回包含n个字符的字符串，从指定位置pos处开始--
        //如果pos超出，返回null,默认则返回从pos开始的全部字符
        //trimmed()返回移除了开头和结尾空格的字符串，保留内部空格
        QString lineData = lines[number].mid(position).trimmed();
        if(!lineData.isEmpty())
        {
            //read the column data frome the lineData,以"\t"为分隔符
            QStringList columnString = lineData.split("\t", QString::SkipEmptyParts);//SkipEmptyParts 略过空内容
            QVector<QVariant> columnData;
            for(int column = 0; column < columnString.count(); ++column)
            {
                columnData << columnString[column];
            }

            if(position > indentations.last())
            {//当前父亲的最后一个孩子节点是现在的新父亲，除非当前的父亲没有子节点
                if(parents.last()->childCount() > 0)
                {
                    //当前父节点的最后一个子节点作为新父亲
                    parents << parents.last()->child(parents.last()->childCount() - 1);//-1 索引从0开始
                    indentations << position;
                }
            }
            else
            {
                while(position < indentations.last() && parents.count() > 0)
                {
                    parents.pop_back();//equivalent  removeLast()
                    indentations.pop_back();
                }
            }

            //附加新项到当前父亲的子列表
            TreeItem *parent = parents.last();//返回根节点
            parent->insertChildren(parent->childCount(), 1, rootItem->columCount());//在子结点最后一个位置插入
            for(int column = 0; column < columnData.size(); ++column)
            {//为子节点每一列设置值
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
            }
        }
        ++number;
    }
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        //internalPointer 返回一个void*指针供model使用去关联index与内部数据类型
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if(item)
        {
            return item;
        }
    }
    return rootItem;
}
