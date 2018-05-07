#include <CQLinkLabel.h>

#include <QPainter>
#include <QStylePainter>
#include <QPaintEvent>
#include <QTextLayout>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

//---------

namespace CQLinkLabelUtil {
  // draw html text on widget in specified rectangle
  void drawText(QWidget *w, QPainter *painter, const QString &text,
                const QPalette &palette, const QRect &rect, bool active) {
    painter->save();

    QFontMetrics fm(painter->font());

    int dy = (rect.height() - fm.height());

    // draw html text using QAbstractTextDocument classes
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QTextDocument td;

    td.setHtml(text);

    // translate painter origin so it matches lower left of destination rect
    QRect trect = rect.translated(-rect.x(), -rect.y() + dy);

    painter->translate(rect.x(), rect.y() - dy);

    painter->setClipRect(trect);

    // set text color
    QAbstractTextDocumentLayout::PaintContext ctx;

    if (active)
      ctx.palette.setColor(QPalette::Text, palette.highlightedText().color());
    else
      ctx.palette.setColor(QPalette::Text, palette.text().color());

    // draw text using QAbstractTextDocumentLayout
    QAbstractTextDocumentLayout *layout = td.documentLayout();

    layout->setPaintDevice(w);

    layout->draw(painter, ctx);

    // reset painter translation
    painter->translate(-rect.x(), -rect.y() + dy);

    painter->restore();
  }

  // generate a color for disabled link
  QColor disabledColor(const QColor &c) {
    //return c.lighter();

    double h, s, v;

    c.getHsvF(&h, &s, &v);

    QColor c1;

    c1.setHsvF(h, s*0.5, v);

    return c1;
  }
}

//---------

CQLinkLabel::
CQLinkLabel(QWidget *parent, const QString &text) :
 QWidget(parent), text_(text)
{
  init();
}

CQLinkLabel::
CQLinkLabel(const QString &text) :
 QWidget(nullptr), text_(text)
{
  init();
}

void
CQLinkLabel::
init()
{
  // set link color from palette
  linkColor_ = palette().color(QPalette::Link);

  // disable vertical resize
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

// update text
void
CQLinkLabel::
setText(const QString &text)
{
  text_ = text;

  updateGeometry();

  update();
}

// set color
void
CQLinkLabel::
setLinkColor(const QColor &c)
{
  linkColor_ = c;

  update();
}

// set enabled
void
CQLinkLabel::
setEnabled(bool enabled)
{
  enabled_ = enabled;

  update();
}

// set linked
void
CQLinkLabel::
setLinked(bool linked)
{
  linked_ = linked;

  update();
}

QSize
CQLinkLabel::
sizeHint() const
{
  // size hint is size of text label with border
  QFontMetrics fm(font());

  return QSize(fm.width(text()) + 4, fm.height() + 4);
}

QSize
CQLinkLabel::
minimumSizeHint() const
{
  // minimum size hint is size of text label with no border
  QFontMetrics fm(font());

  return QSize(fm.width(text()), fm.height());
}

void
CQLinkLabel::
enterEvent(QEvent *)
{
  // update active and redraw on enter
  active_ = true;

  update();
}

void
CQLinkLabel::
leaveEvent(QEvent *)
{
  // clear active and redraw on leave
  active_ = false;

  update();
}

void
CQLinkLabel::
paintEvent(QPaintEvent *)
{
  QStylePainter painter(this);

  painter.setPen(palette().color(QPalette::Text));

  QRect r = rect();

  if (linked()) {
    // get link color
    QColor linkColor = (enabled_ ? linkColor_ : CQLinkLabelUtil::disabledColor(linkColor_));

    // draw text in link color and underline (if active)
    QString htmlText;

    if (active_ && enabled_)
      htmlText += "<u>";

    htmlText += "<font color=\"" + linkColor.name() + "\">" + encodeText(text()) + "</font>";

    if (active_ && enabled_)
      htmlText += "</u>";

    CQLinkLabelUtil::drawText(this, &painter, htmlText, palette(), r, false);
  }
  else {
    //QColor textColor = palette().color(QPalette::WindowText);

    painter.drawText(rect(), text());
  }
}

void
CQLinkLabel::
mousePressEvent(QMouseEvent *)
{
  if (linked()) {
    // register press down and redraw
    pressed_ = true;

    update();
  }
}

void
CQLinkLabel::
mouseReleaseEvent(QMouseEvent *)
{
  if (linked()) {
    // press up after press down signals clicked
    if (! pressed_)
      return;

    click();

    pressed_ = false;

    update();
  }
}

void
CQLinkLabel::
mouseDoubleClickEvent(QMouseEvent *)
{
  if (linked()) {
    // double click is same as press down/up
    click();
  }
}

void
CQLinkLabel::
click()
{
  if (enabled() && linked())
    emit clicked();
}

QString
CQLinkLabel::
encodeText(const QString &text) const
{
  QString text1;

  for (int i = 0; i < text.length(); ++i) {
    if      (text[i] == '<')
      text1 += "&lt;";
    else if (text[i] == '>')
      text1 += "&gt;";
    else
      text1 += text[i];
  }

  return text1;
}
