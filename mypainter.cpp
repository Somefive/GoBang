#include "MyPainter.h"

MyPainter::MyPainter(QPaintDevice *_device):
    QPainter(_device)
{
    this->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    this->setPen(Qt::NoPen);
    this->setBrush(QColor(160,160,160,200));
}
