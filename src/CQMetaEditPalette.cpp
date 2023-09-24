#include <CQMetaEditPalette.h>
#include <CQMetaEdit.h>

#include <QApplication>
#include <QPainter>

CQMetaEditPalette::
CQMetaEditPalette(CQMetaEdit *edit) :
 QFrame(edit), edit_(edit)
{
  setObjectName("palette");
}

void
CQMetaEditPalette::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  QFontMetrics fm(font());

  QStringList roleNames = QStringList() <<
   "Window" << "WindowText" << "Base" << "AlternateBase" <<
   "ToolTipBase" << "ToolTipText" << "Text" << "Button" <<
   "ButtonText" << "BrightText" << "Light" << "Midlight" <<
   "Dark" << "Mid" << "Shadow" << "Highlight" <<
   "HighlightedText" << "Link" << "LinkVisited" <<
   "LinkText" << "LinkVisitedText";

  QPalette::ColorRole roles[] = {
   QPalette::Window, QPalette::WindowText, QPalette::Base, QPalette::AlternateBase,
   QPalette::ToolTipBase, QPalette::ToolTipText, QPalette::Text, QPalette::Button,
   QPalette::ButtonText, QPalette::BrightText, QPalette::Light, QPalette::Midlight,
   QPalette::Dark, QPalette::Mid, QPalette::Shadow, QPalette::Highlight,
   QPalette::HighlightedText, QPalette::Link, QPalette::LinkVisited,
   QPalette::Window, QPalette::Window
  };

  QPalette::ColorRole textRoles[] = {
   QPalette::WindowText, QPalette::Window, QPalette::Text, QPalette::WindowText,
   QPalette::ToolTipText, QPalette::ToolTipBase, QPalette::Base, QPalette::ButtonText,
   QPalette::Button, QPalette::Dark, QPalette::Dark, QPalette::Dark,
   QPalette::BrightText, QPalette::Text, QPalette::Text, QPalette::HighlightedText,
   QPalette::Highlight, QPalette::Text, QPalette::Text,
   QPalette::Link, QPalette::LinkVisited
  };

  QStringList groupNames = QStringList() <<
   "Active" << "Inactive" << "Disabled";

  QPalette::ColorGroup groups[] = {
    QPalette::Active, QPalette::Inactive, QPalette::Disabled
  };

  int columnWidths[4];

  columnWidths[0] = 0;

  for (int r = 0; r < roleNames.length(); ++r)
    columnWidths[0] = std::max(columnWidths[0], fm.horizontalAdvance(roleNames[r]));

  for (int c = 1; c < 4; ++c)
    columnWidths[c] = fm.horizontalAdvance(groupNames[c - 1]);

  int maxColumnWidth = std::max(std::max(columnWidths[1], columnWidths[2]), columnWidths[3]);

  maxColumnWidth = std::max(maxColumnWidth, fm.horizontalAdvance("#FFFFFF"));

  //---

  auto pal = (edit_->widget() ? edit_->widget()->palette() : qApp->palette());

  auto textColor = pal.color(QPalette::Active, QPalette::Text);
  auto lineColor = pal.color(QPalette::Active, QPalette::Dark);

  painter.setPen(textColor);

  //---

  int ym = 5;
  int xm = 7;

  int y = 1;

  for (int r = 0; r <= roleNames.length(); ++r) {
    int x = xm;

    for (int c = 0; c < 4; ++c) {
      int dx = 0;

      if (c > 0)
        dx = (maxColumnWidth + xm - columnWidths[c])/2;

      if (r == 0) {
        if (c > 0) {
          painter.setPen(textColor);

          painter.drawText(x + dx, y + fm.ascent() + 1, groupNames[c - 1]);
        }
      }
      else {
        if (c == 0) {
          painter.setPen(textColor);

          painter.drawText(x + dx, y + fm.ascent() + 1, roleNames[r - 1]);
        }
        else {
          QColor color = pal.color(groups[c - 1], roles[r - 1]);

          QRect rect(x - 1, y, maxColumnWidth + xm - 1, fm.height() + 4);

          painter.fillRect(rect, color);

          //int gray = qGray(color.red(), color.green(), color.blue());
          //painter.setPen(gray > 128 ? Qt::black : Qt::white);

          QColor colorTextColor = pal.color(groups[c - 1], textRoles[r - 1]);

          painter.setPen(colorTextColor);

          int w = fm.horizontalAdvance(color.name());

          int dx1 = (maxColumnWidth + xm - w)/2;

          painter.drawText(x + dx1, y + fm.ascent() + 1, color.name());
        }
      }

      if (c > 0)
        x += maxColumnWidth + xm;
      else
        x += columnWidths[0] + xm;
    }

    y += fm.height() + ym;
  }

  //---

  painter.setPen(lineColor);

  //---

  int x = xm;

  for (int c = 0; c < 4; ++c) {
    if (c > 0)
      painter.drawLine(x - 2, 0, x - 2, height() - 1);

    if (c > 0)
      x += maxColumnWidth + xm;
    else
      x += columnWidths[0] + xm;
  }

  //---

  y = 1;

  for (int r = 0; r <= roleNames.length(); ++r) {
    if (r > 0)
      painter.drawLine(0, y - 1, width() - 1, y - 1);

    y += fm.height() + ym;
  }
}
