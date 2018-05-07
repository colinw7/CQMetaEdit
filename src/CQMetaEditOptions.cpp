#include <CQMetaEditOptions.h>
#include <CQMetaEdit.h>
#include <QCheckBox>
#include <QVBoxLayout>

CQMetaEditOptions::
CQMetaEditOptions(CQMetaEdit *edit) :
 QFrame(edit), edit_(edit)
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(0); layout->setSpacing(0);

  inheritedCheck_ = new QCheckBox("Inherited");

  inheritedCheck_->setChecked(edit_->inherited());

  connect(inheritedCheck_, SIGNAL(toggled(bool)), edit_, SLOT(setInherited(bool)));

  layout->addWidget(inheritedCheck_);

  layout->addStretch(1);
}
