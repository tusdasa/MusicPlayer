#include "centerui.h"

CenterUI::CenterUI(QWidget *parent) : QWidget(parent)
{
    songname = new QLabel;
    songimage = new QLabel;
    QVBoxLayout * layout = new QVBoxLayout(this);
    pix.load(":/img/fm.png");
    QPixmap pix1 = pix.scaled(128,128,Qt::KeepAspectRatio);
    songimage->setPixmap(pix1);
    songname->setText(":)");
    songimage->setFixedSize(129,129);
    layout->addWidget(songimage);
    layout->addWidget(songname);

}
