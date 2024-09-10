#ifndef WAVEITEM_H
#define WAVEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

class WaveItem : public QGraphicsItem
{
public:
    WaveItem(const QList<int>& amplitudes, int width, int height, QGraphicsItem* parent = nullptr)
        : QGraphicsItem(parent),  m_width(width), m_height(height), m_amplitudes(amplitudes)
    {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int m_width;
    int m_height;
    QList<int> m_amplitudes;
};

#endif // WAVEITEM_H
