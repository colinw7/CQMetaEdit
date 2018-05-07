/*! \class CQPicker

    \brief Widget for graphically selecting widgets.

    This widget allows the user to select graphically objects with
    the mouse by pressing down and holding the left mousebutton on this
    widget ('Pick' mode). While moving around on the windows of the same
    application the bounding box of the widget under the cursor is shown.
    Releasing the mouse button on any widget will update the hierarchical
    name of the found widget in the \a property of the CQPicker widget.

    \property CQPicker::lastTouchedWidget
    \brief the hierarchical \b full name of the widget touched before

    This property holds the full hierarchical name of the widget
    recently touched after releasing the mouse button on it.
    while the holding the left mouse button

    Get this property's value with CQPicker::lastTouchedWidget().
*/

/*!
 *  \fn CQPicker::objectTouched(QObject* object)
 *  \param object pointer to touched object
 *
 *  This signal is emitted whenever the cursor touches a new object.
 */

/*!
 *  \fn CQPicker::widgetTouched(QWidget* widget)
 *  \param widget pointer to touched widget
 *
 *  This signal is emitted whenever the cursor touches a new widget.
 */

/*!
 *  \fn CQPicker::startPick()
 *
 *  This signal is emitted whenever the user presses the left mouse button
 *  on the CQPicker widget
 */

/*!
 *  \fn CQPicker::endPick()
 *
 *  This signal is emitted whenever the user releases the left mouse button
 *  after pressing and holding the left mouse bitton on the CQPicker widget
 */

/*!
 *  \fn CQPicker::position(int globalX, int globalY, int localX, int localY)
 *  \param globalX  x coordinate of cursor in screen coordinates
 *  \param globalY  y coordinate of cursor in screen coordinates
 *  \param localX   x coordinate of cursor in widget coordinates
 *  \param localY   y coordinate of cursor in widget coordinates
 *
 *  This signal is emitted while moving the cursor around in 'Pick' mode
 */

/*!
 *  \fn CQPicker::globalPosition(int globalX, int globalY)
 *  \param globalX  x coordinate of cursor in screen coordinates
 *  \param globalY  y coordinate of cursor in screen coordinates
 *
 *  This signal is emitted while moving the cursor around in 'Pick' mode
 */

#include <CQPicker.h>
#include <CQUtil.h>

#include <svg/picker_on_svg.h>
#include <svg/picker_off_svg.h>
#include <xbm/spy_cursor.xbm>

#include <QApplication>
#include <QPixmap>
#include <QBitmap>
#include <QRubberBand>
#include <QMouseEvent>

/*!
 * Default \c CQPicker constructor
 * \param parent pointer to parent widget
 *   If \a parent is 0, the new widget becomes a top-level window.
 *   If parent is another widget, this widget becomes a child window inside
 *   parent. The new widget is deleted when its parent is deleted.
 * \param name  Constructs an object called \a name.
 */
CQPicker::
CQPicker(QWidget* parent, const char* name) :
  QLabel(parent)
{
  setObjectName(name ? name : "picker");

  setToolTip("Drag the picker over the Qt object to pick and release");

  updatePixmap();
}

/*!
 * Destroys the widget, deleting all its child objects.
 * All signals to and from the object are automatically disconnected.
 */
CQPicker::
~CQPicker()
{
  delete rubberBand_;
}

void
CQPicker::
setSize(int s)
{
  size_ = s;

  update();
}

/*!
 * This event handler, for event e, can be reimplemented in a subclass
 * to receive mouse press events for the widget.
 *
 * By default it start finding widgets if it was not in the 'Pick' mode before.
 */
void
CQPicker::
mousePressEvent(QMouseEvent *e)
{
  if (! pressed_) {
    pressed_     = true;
    touchObject_ = 0;
    touchWidget_ = 0;

    delete rubberBand_;

    rubberBand_ = 0;

    emit startPick();

    updatePixmap();

    checkForWidget(e->globalPos());
  }

  QLabel::mousePressEvent(e);

  QBitmap bitmap = QBitmap::fromData(QSize(16,16), (uchar *) spy_cursor);

  QCursor cursor(bitmap, bitmap);

  QApplication::setOverrideCursor(cursor);
}

/*!
 * This event handler, for event e, can be reimplemented in a subclass
 * to receive mouse release events for the widget.
 *
 * By default it ends finding widgets if it was in the 'Pick' mode before.
 */
void
CQPicker::
mouseReleaseEvent(QMouseEvent *e)
{
  if (pressed_ ) {
    if (touchObject_)
      emit objectPicked(touchObject_);

    if (touchWidget_)
      emit widgetPicked(touchWidget_);

    //---

    pressed_     = false;
    touchObject_ = 0;
    touchWidget_ = 0;

    delete rubberBand_;

    rubberBand_ = 0;

    emit endPick();

    updatePixmap();
  }

  QLabel::mouseReleaseEvent(e);

  QApplication::restoreOverrideCursor();
}

/*!
 * This event handler, for event e, can be reimplemented in a subclass
 * to receive mouse move events for the widget.
 *
 * By default is checking for a widget under the cursor while moving the
 * mouse with a left pressed button if it s in the 'Pick' mode.
 */
void
CQPicker::mouseMoveEvent(QMouseEvent *e)
{
  if (pressed_)
    checkForWidget(e->globalPos());

  QLabel::mouseMoveEvent(e);
}

/*!
 *  \fn QString CQPicker::lastTouchedWidget() const
 *  \return a string with the full hierarchical name of the last touched widget
 *
 *  Returns the full hierarchical name of the last touched widget
 */
bool
CQPicker::
checkForWidget(const QPoint& globalPos)
{
  QWidget* w = QApplication::widgetAt(globalPos.x(), globalPos.y());

  bool touchChanged = (w != touchWidget_);

  touchObject_ = w;
  touchWidget_ = w;

  if (pressed_ && touchWidget_ && touchChanged) {
    // display rubber band over widget under cursor
    delete rubberBand_;

    rubberBand_ = new QRubberBand(QRubberBand::Rectangle);

    QPoint ul(0,0);
    QPoint lr(touchWidget_->width()-1,touchWidget_->height()-1);

    QPoint gul = touchWidget_->mapToGlobal(ul);
    QPoint glr = touchWidget_->mapToGlobal(lr);

    rubberBand_->setGeometry(QRect(gul, glr));

    rubberBand_->show();
  }

  if (w) {
    QPoint pos = w->mapFromGlobal(globalPos);

    emit position(globalPos.x(), globalPos.y(), pos.x(), pos.y());
  }
  else {
    emit globalPosition(globalPos.x(), globalPos.y());
  }

  if (touchChanged) {
    if (touchObject_)
      emit objectTouched(touchObject_);

    if (touchWidget_)
      emit widgetTouched(touchWidget_);
  }

  return (touchWidget_ != 0);
}

void
CQPicker::
resizeEvent(QResizeEvent *)
{
  updatePixmap();
}

void
CQPicker::
updatePixmap()
{
  if (pressed_)
    setPixmap(CQPixmapCacheInst->getSizedPixmap("PICKER_ON", sizeHint()));
  else
    setPixmap(CQPixmapCacheInst->getSizedPixmap("PICKER_OFF", sizeHint()));
}

QSize
CQPicker::
sizeHint() const
{
  return QSize(size(), size());
}
