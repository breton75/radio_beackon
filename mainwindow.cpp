#include "mainwindow.h"
#include "ui_mainwindow.h"

extern SvSQLITE *SQLITE;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  AppParams::WindowParams p;
  p = AppParams::readWindowParams(this);
  this->resize(p.size);
  this->move(p.position);
  this->setWindowState(p.state);
  
  QString mapFileName = AppParams::readParam(this, "General", "xml", "").toString();
  QString dbFileName = AppParams::readParam(this, "General", "db", "").toString();
  bool drawMap = AppParams::readParam(this, "General", "drawMap", "").toBool();
  
  
  /* создаем координатную сетку */
  area = new SvArea(ui->centralWidget);
  ui->vlayMain->addWidget(area);
  if(!area->readBounds(mapFileName))
  {
    QMessageBox::warning(this, tr("Ошибка в файле XML"),
                         tr("Неверные границы области (bounds)"));
    delete area;
    return;
  }
  
  area->readMap(mapFileName);
  
  area->setUp("area_1");

  /* добавляем на карту самолетик */
  airplane = new SvMapObjectAirplane(area, 30.0258, 59.9588654);
  airplane->setBrush(QColor(30, 130, 230, 255), QColor(30, 130, 230, 255));
  airplane->setPen(QColor(30, 130, 230, 255).dark());
//  airplane->setGeo(30.0258, 59.9588654);
  area->scene->addMapObject(airplane);
  airplane->setVisible(true);
  airplane->setZValue(1);
  /* добавляем на карту радиус */
  radius = new SvMapObjectRadius(area, 30.0258, 59.9588654);
  area->scene->addMapObject(radius);
  
  
  /* читаем БД (план полета) */
  SQLITE = new SvSQLITE(this, dbFileName);
  QSqlError err = SQLITE->connectToDB();
  
  if(err.type() != QSqlError::NoError) {
    qDebug() << err.databaseText();
    return;
  }
  
  QSqlQuery* q = new QSqlQuery(SQLITE->db);
  if(QSqlError::NoError != SQLITE->execSQL(QString("select * from plan"), q).type())
  {
    qDebug() << q->lastError().databaseText();
    q->finish();
    return;
  }
  
  while(q->next())
  {
    qreal lon = q->value("lon").toDouble();
    qreal lat = q->value("lat").toDouble();
    int id = q->value("id").toInt();
    QString uid = q->value("uid").toString();
  
    SvMapObjectBeaconPlanned* beacon = new SvMapObjectBeaconPlanned(area);
    beacon->setGeo(lon, lat);
    beacon->setId(id);
    beacon->setUid(uid);
    beacon->setBrush(QColor(255, 50, 100, 255), QColor(255, 50, 100, 255));
    beacon->setPen(QColor(255, 50, 100, 255).dark());
    area->scene->addMapObject(beacon);   
    
  }
  q->finish();
  
  if(QSqlError::NoError != SQLITE->execSQL(QString("select * from implementation"), q).type())
  {
    qDebug() << q->lastError().databaseText();
    q->finish();
    return;
  }
  
  while(q->next())
  {
    qreal lon = q->value("lon").toDouble();
    qreal lat = q->value("lat").toDouble();
    int id = q->value("id").toInt();
    int number = q->value("number").toInt();

    SvMapObjectBeaconActive* beacon = new SvMapObjectBeaconActive(area, id);
    beacon->setGeo(lon, lat);
    beacon->setId(id);
    beacon->setNumber(number);
    beacon->setCovereged(id%3);
    area->scene->addMapObject(beacon);   
  
  }
  
  q->finish();
//  SQLITE->~SvSQLITE();

  
  
  area->setScale(1);
//  area->
  
  
//  connect(ui->bnMoveLeft, SIGNAL(clicked()),  area, SLOT(moveHorizontal(int)));
//  connect(ui->bnMoveRight, SIGNAL(clicked()), area, SLOT(moveVertical(int)));

//  area->addItem(gtBeackon, QPointF(110, 50), 1, "Буй 1");
//  area->addItem(gtBeackon, QPointF(158.2, 125.1), 2, "Буй 2");
//  area->addItem(gtBeackon, QPointF(256.4, 170.3), 3, "Буй 3");
  
}

MainWindow::~MainWindow()
{
  // закрываем дочерние окна с сохранением параметров
//  foreach (QObject* wnd, ui->mdiArea->children())
//  {
//    if(wnd->metaObject()->className() == "SvArea")
//    {
////      SvArea* areaWindow = static_cast<SvArea*>(wnd);
////      areaWindow->~SvArea();
      
//      static_cast<SvArea*>(wnd)->~SvArea();
//    }
//  }

  AppParams::saveWindowParams(this, this->size(), this->pos(), this->windowState());
  AppParams::saveParam(this, "GENERAL", "xml", "d:/map_coast.xml");
  
  delete ui;
}
