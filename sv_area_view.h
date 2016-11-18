#ifndef SVAREAVIEW_H
#define SVAREAVIEW_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QGraphicsEllipseItem>
#include <QScrollArea>
#include <QScrollBar>

//class SvArea;
//class GraphSimbolDevice;

//class GraphicsView : public QGraphicsView
//{
//    Q_OBJECT
//public:
//    GraphicsView(SvArea *v, int* scale) : QGraphicsView(), view(v) { _scale = scale; }

//  int* _scale;

//private:
////  void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
////  void drawBackground(QPainter *painter, const QRectF &r);

//protected:
//#ifndef QT_NO_WHEELEVENT
//    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;


//#endif

//  private:
//    void drawForeground(QPainter *painter, const QRectF &r);

//  private:
//      SvArea *view;
//};


//class SvSceneView: public QGraphicsScene
//{
//  Q_OBJECT


//  public:
//    explicit SvSceneView(int* scale) { _scale = scale; }

//    int* _scale;


//  private:
//    void drawForeground(QPainter *painter, const QRectF &r);

//};

class GItem;

class SvScene2: public QGraphicsScene
{
  Q_OBJECT

  public:
    explicit SvScene2(int* scale) { _scale = scale; }

    int* _scale;

  private:
    void drawForeground(QPainter *painter, const QRectF &r);
};

class SvAreaView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SvAreaView(QWidget *parent = 0);
    ~SvAreaView();

    QGraphicsScene* scene;
//    SvScene2* scene;
//    GraphicsView* view;
//    GraphicsView* view2;

QGraphicsEllipseItem* ell;
GItem* mesh;

private:
  void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

  bool m_down = false;
  QPoint mousePos;


public:
//    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
  int _scale = 100;

  private:
//    void drawForeground(QPainter *painter, const QRectF &r);
//    void paintEvent(QPaintEvent * event);
  int step = 10;

signals:

public slots:
  void scaleInc();
  void scaleDec();
  void moveHorizontal(int val);
  void moveVertical(int val);

};

class GItem : public QGraphicsRectItem /*, public QObject*/
{
//    Q_OBJECT

  public:
    explicit GItem(int* scale) { _scale = scale; }

//  ~GItem() { }

  int* _scale;

//    int type() const { return gtNode; }

  private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//    int x;
//    int y;
//    QColor brushColor;
//    QColor penColor;

//  protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
////    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);
};


#endif // SVAREAVIEW_H
