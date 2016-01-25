#include "draglabel.h"

DragLabel::DragLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setAutoFillBackground(true);
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Raised);
}

DragLabel::~DragLabel()
{

}

