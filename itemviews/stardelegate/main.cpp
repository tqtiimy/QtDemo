#include <QtWidgets>
#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"

void populateTableWidget(QTableWidget *tableWidget)
{
    static const struct
    {
        const char *title;
        const char *genre;//type
        const char *artist;
        int rating;
    }staticData[] =
    {
//        {"aaaa", "aaaa", "aaaa", 5},
//        {"bbbb", "bbbb", "bbbb", 4},
//        {"cccc", "cccc", "cccc", 3},
//        {"dddd", "dddd", "dddd", 5},
//        {"dddd", "dddd", "dddd", 5},

    { "Mass in B-Minor", "Baroque", "J.S. Bach", 5 },
    { "Three More Foxes", "Jazz", "Maynard Ferguson", 4 },
    { "Sex Bomb", "Pop", "Tom Jones", 3 },
    { "Barbie Girl", "Pop", "Aqua", 5 },
    {0, 0, 0, 0}

    };

    for(int row = 0; staticData[row].title != 0; ++row)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].title);
        QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].genre);
        QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].artist);
        QTableWidgetItem *item3 = new QTableWidgetItem;

        item3->setData(0, QVariant::fromValue(StarRating(staticData[row].rating)));

        tableWidget->setItem(row, 0, item0);
        tableWidget->setItem(row, 1, item1);
        tableWidget->setItem(row, 2, item2);
        tableWidget->setItem(row, 3, item3);
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTableWidget tableWidget(4, 4);\

    //set delegate and property
    tableWidget.setItemDelegate(new StarDelegate);
    tableWidget.setEditTriggers(QAbstractItemView::DoubleClicked //当一个Item被双击后开始编辑
                                | QAbstractItemView::SelectedClicked);//当点击一个已经选中的item后开始编辑
    tableWidget.setSelectionBehavior(QAbstractItemView::SelectRows);//设置为仅行选中0

    //set header
    QStringList headerLabels;
    headerLabels<<"Title"<<"Genre"<<"Artist"<<"Rating";
    tableWidget.setHorizontalHeaderLabels(headerLabels);

    populateTableWidget(&tableWidget);

    tableWidget.resizeColumnsToContents();
    tableWidget.resize(500, 300);
    tableWidget.show();

    return app.exec();
}
