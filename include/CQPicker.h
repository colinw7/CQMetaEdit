#ifndef CQPicker_H
#define CQPicker_H

#include <QLabel>
#include <QString>

class QPainter;
class QMouseEvent;
class QRubberBand;

class CQPicker : public QLabel {
  Q_OBJECT

  Q_PROPERTY(int size READ size WRITE setSize)

 public:
  CQPicker(QWidget* parent = 0, const char* name = 0);
 ~CQPicker();

  int size() const { return size_; }
  void setSize(int i);

  QSize sizeHint() const override;

 signals:
  void objectTouched(QObject *pObject);
  void widgetTouched(QWidget *pWidget);

  void startPick();
  void endPick();

  void position(int globalX, int globalY, int localX, int localY);

  void globalPosition(int globalX, int globalY);

  void objectPicked(QObject *pObject);
  void widgetPicked(QWidget *pWidget);

 protected:
  void mousePressEvent  (QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void mouseMoveEvent   (QMouseEvent *e) override;

  void resizeEvent(QResizeEvent *) override;

  void updatePixmap();

 private:
  bool checkForWidget(const QPoint& pos);
  void drawWidgetRect();

 private:
  int          size_        { 32 };
  bool         pressed_     { false };
  QObject*     touchObject_ { nullptr };
  QWidget*     touchWidget_ { nullptr };
  QRubberBand* rubberBand_  { nullptr };
};

#endif
