#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWindow>
#include <QScrollBar>
#include <QtXml>
#include <QMessageBox>
#include <QPair>
#include <QMap>

#include "sv_area.h"
#include "sv_settings.h"
#include "sv_beackonsymbol.h"
#include "sv_mapobjects.h"
#include "../../../Common/sv_sqlite.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SvArea* area;
//    SvAreaView* area_v;
    
    SvMapObjectAirplane* airplane;
    SvMapObjectRadius* radius;
    
    QWidget* wdg;
    
    GEO_BOUNDS geoBounds;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
