#include "sv_area_view.h"

//#ifndef QT_NO_WHEELEVENT
//void GraphicsView::wheelEvent(QWheelEvent *e)
//{
//    if (e->modifiers() & Qt::ControlModifier)
//    {
////        if (e->delta() > 0) view->zoomIn(6);
////        else view->zoomOut(6);
//        e->accept();
//    }
//    else { QGraphicsView::wheelEvent(e);  }
//}
//#endif

//void GraphicsView::paintEvent(QPaintEvent* event)
//{
////  Q_UNUSED(event)

//  QPainter painter(this);

////  const int numHorizontalSections = 10;
////  QLine line(rect().topLeft(), rect().bottomLeft());
////  for (int i=1; i<numHorizontalSections; ++i) {
////      line.translate(rect().width()/numHorizontalSections, 0);
////      painter.drawLine(line);

////  }

//}

//void SvAreaView::drawForeground(QPainter *painter, const QRectF &r)
//void GItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
void SvScene2::drawForeground(QPainter *painter, const QRectF &r)
{
//  QRectF rect(this->scene()->sceneRect()); // ((QGraphicsRectItem*)this)->rect());
  QRectF rect(r);
  rect.adjust(5, 5, -5, -5 );
  int brdwdth = 40;

  int left = rect.left() + brdwdth;
  int right = rect.right() - brdwdth;
  int top = rect.top() + brdwdth;
  int bottom = rect.bottom() - brdwdth;

//clear();


  QColor _gridBackColor = QColor(0, 0, 0, 30);
  QColor _gridColor1 = QColor(0, 0, 5, 250);
  QColor _gridColor2 = QColor(0, 0, 5, 200);
  QColor _fontColor = QColor(0, 0, 255, 150);

  QPen pen; // = QPen( _gridColor );
  int _gridStep = *_scale / 10;

painter->setBrush(_gridBackColor);
 painter->fillRect(rect, _gridBackColor);

// return;

  /* рисуем рамку */
//  QRect border = QRect(left, top, right - left, bottom - top);
  QRect border = QRect(left, top, right, bottom);
  pen.setColor(_fontColor);
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(2);
  painter->setPen( pen );
  painter->drawRect(rect);

painter->drawText(QRect(left, top, 100, brdwdth),
                        QString("top=%1; btm=%2").arg(top).arg(bottom));

// return;

  /** рисум сетку **/
  pen.setColor(_gridColor1);
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(1);
  painter->setPen( pen );

  QPoint prevLine = QPoint(left, top);


  /* вертикальные линии */
  for (int i = 0; i < border.width(); i += _gridStep)
  {
//    if((left + i) > right)
//      continue;
  pen.setColor(i % 4 == 0 ? _gridColor2 : _gridColor1);
    painter->drawLine(QPoint(left + i, top - 2), QPointF(left + i, bottom + 2));

    if(left + i - prevLine.x() > brdwdth)
    {
//      qDebug() << prevLine.x() << prevLine.y();

      QTextOption opt = QTextOption(Qt::AlignBottom | Qt::AlignHCenter);
      painter->drawText(QRect(left + i - brdwdth / 2, top - brdwdth, brdwdth, brdwdth - 2),
                        QString::number(/*left + */i), opt);

      prevLine.setX(left + i);
    }
  }

  /* горизонтальные линии */
  for(int i = 0; i < border.height(); i += _gridStep)
  {
/*    if ((top + i) % _gridStep)
      continue*/;

    painter->drawLine(QPoint(left - 2, top + i), QPointF(right + 2, top + i));

//    qDebug() << "bottom + i = " << bottom + i << prevLine.y();
    if(top + i - prevLine.y() > brdwdth / 2)
    {

      QTextOption opt = QTextOption(Qt::AlignRight | Qt::AlignCenter);
      painter->drawText(QRect(left - brdwdth, top + i - brdwdth / 2, brdwdth - 2, brdwdth),
                        QString::number(/*top + */i), opt);

      prevLine.setY(top + i);
    }


  }
}

SvAreaView::SvAreaView(QWidget *parent) :
  QGraphicsView(parent)/*,
  scene(new SvScene)*/
{
    this->setParent(parent);
//    this->resize(800, 600);
    this->setGeometry(0, 0, 800, 600);

//    scene = new QGraphicsScene(QRectF(this->rect())/*, this*/); // SvScene(&_scale);
  scene = new SvScene2(&_scale);
  scene->setSceneRect(0, 0, this->width() - 4, this->height() - 4);
//  scene->setSceneRect(this->rect());


//scene->setParent(parent);

    this->setRenderHint(QPainter::Antialiasing, false);
    this->setDragMode(QGraphicsView::NoDrag); //ScrollHandDrag NoDrag); //RubberBandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
//    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
//    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//  view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//  view->resize(
this->setScene(scene);

//    QScrollArea* scrollarea = new QScrollArea(this);
//    scrollarea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//  scrollarea->setWidget(view);

//QVBoxLayout* vlay = new QVBoxLayout(this);
//  vlay->setSpacing(0);
//  vlay->setObjectName(QStringLiteral("vlay"));

//  vlay->addWidget(view);


//  vlay->addWidget(view2);

//  mesh = new GItem(&_scale);
//  this->mesh->setRect(0, 0, this->width() - 4, this->height() - 4);
//  mesh->setRect(this->sceneRect());
//  mesh->setZValue(-3000);
//  mesh->setVisible(true);
//  scene->addItem(mesh);

ell = new QGraphicsEllipseItem(QRect(1,2,50,50));

ell->setVisible(true);
scene->addItem(ell);
scene->addRect(0, 0, 200, 200);


this->setVisible(true);


}

SvAreaView::~SvAreaView()
{
  deleteLater();
}

void SvAreaView::scaleInc()
{
  if(_scale > 1000)
    return;

  _scale += step;

  int w = this->width() + step; // * 1.1;
  int h = this->height() + step; // * 1.1;
  this->resize(w, h);
//  this->mesh->setRect(this->sceneRect());
//  qDebug() << this->rect();
//  this->mesh->setRect(0, 0, w - 4, h - 4);
  this->scene->setSceneRect(0, 0, w - 4, h - 4);
}

void SvAreaView::scaleDec()
{
  if(_scale < 110)
    return;

  _scale -= step;
  int w = this->width() - step; // / 1.1;
  int h = this->height() - step; // / 1.1;
  this->resize(w, h);
//  this->mesh->setRect(0, 0, w - 4, h - 4);
  this->scene->setSceneRect(0, 0, w - 4, h - 4);

}

void SvAreaView::moveVertical(int val)
{
  this->setGeometry(x(), val, width(), height());
}

void SvAreaView::moveHorizontal(int val)
{
  this->setGeometry(-val, y(), width(), height());
}

void SvAreaView::mousePressEvent(QMouseEvent * event)
{
  qDebug() << event->modifiers();

  if(event->modifiers() /*&& Qt::ShiftModifier*/ != Qt::ShiftModifier)
    return;

  m_down = true;
  mousePos = event->pos();
}

void SvAreaView::mouseReleaseEvent(QMouseEvent * event)
{
  m_down = false;
}

void SvAreaView::mouseMoveEvent(QMouseEvent * event)
{
  if(!m_down) return;

  moveVertical(this->y() + event->pos().y() - mousePos.y());
  moveHorizontal(-(this->x() + event->pos().x() - mousePos.x()));
}
