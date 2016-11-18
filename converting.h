#ifndef CONVERTING_H
#define CONVERTING_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <math.h>
#include <QDateTime>
#include <qmath.h>

#define MINOR_LINE_INTERVAL 10
#define MAJOR_LINE_INTERVAL 50

class GEO 
{
public:
  explicit GEO(qreal lon, qreal lat, QDateTime time)  {
    this->lon = lon; this->lat = lat; this->time = time;
  }
  
  qreal lat;
  qreal lon;
  QDateTime time;
  
  bool operator !=(const GEO &other) const { return time != other.time; }
  bool operator ==(const GEO &other) const { return time == other.time; }
  bool operator >(const GEO &other) const  { return time >  other.time; }
  bool operator <(const GEO &other) const  { return time <  other.time; }
  bool operator <=(const GEO &other) const { return time <= other.time; }
  bool operator >=(const GEO &other) const { return time >= other.time; }
};

struct GEO_BOUNDS {
  qreal min_lat;
  qreal min_lon;
  qreal max_lat; 
  qreal max_lon;
};

struct KOEFF {
  qreal lat;
  qreal lon;
};


struct AREA_DATA
{
  GEO_BOUNDS geo_bounds;
  qreal scale;
  KOEFF koeff;
  QSize area_base_size;
  QSize area_curr_size;
  QString area_name;
  
  QMap<quint64, QPair<qreal, qreal>> NODES;
  QMap<quint64, QList<QPair<qreal, qreal>>> WAYS;
//  QMap<quint64, COORD> NODES;
//  QMap<quint64, QList<COORD> WAYS;
  
  qreal gridCellStep = MINOR_LINE_INTERVAL;
  quint64 gridCellDistance;
  
};


qreal geo1_geo2_distance(qreal lon1, qreal lat1, qreal lon2, qreal lat2);

/* расстояние в километрах между двумя широтами/долготами */
qreal lon1_lon2_distance(qreal min_lon, qreal max_lon, qreal lat);
qreal lat1_lat2_distance(qreal min_lat, qreal max_lat, qreal lon);

void getGridStep(AREA_DATA* area_data);

#endif // CONVERTING_H
