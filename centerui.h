#ifndef CENTERUI_H
#define CENTERUI_H

#include <QWidget>
#include <QLabel>
#include <QPicture>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
class CenterUI : public QWidget
{
    Q_OBJECT
public:
    explicit CenterUI(QWidget *parent = nullptr);
    QLabel *songname;
    QLabel *songimage;
    QPixmap pix;
signals:

public slots:
};

#endif // CENTERUI_H
