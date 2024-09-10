#include "waveitem.h"

QRectF WaveItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void WaveItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Set up pen and brush for drawing
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    if(m_amplitudes.size()<=12){ //display the on-time HRV graph
        // Calculate the x step for each pixel in the waveform
        float xStep = (float)m_width / 13.0;
        if(m_amplitudes.size()>1){
            // iterate through each amplitude and draw line between each pair of peaks
            for(int i=1; i<m_amplitudes.size(); i++){
                int currentY = m_amplitudes[i] * m_height / 120;
                int prevY = m_amplitudes[i-1] * m_height / 120;
                float currentX = 15 + (float)i * xStep + (m_width - 12*xStep)/2;
                float prevX = 15 + (float)(i-1) * xStep + (m_width - 12*xStep)/2;

                QPointF prev(prevX, m_height-prevY);
                QPointF current(currentX, m_height-currentY);

                painter->drawLine(current, prev);
            }
        }
    }else{ //display the summery HRV graph
        float xStep = (float)m_width / (m_amplitudes.size()*13/12);
        if(m_amplitudes.size()>1){
            // iterate through each amplitude and draw line between each pair of peaks
            for(int i=1; i<m_amplitudes.size(); i++){
                int currentY = m_amplitudes[i] * m_height / 120;
                int prevY = m_amplitudes[i-1] * m_height / 120;
                float currentX = (float)i * xStep + (m_width - m_amplitudes.size()*xStep)/2;
                float prevX = (float)(i-1) * xStep + (m_width - m_amplitudes.size()*xStep)/2;

                QPointF prev(prevX, m_height-prevY);
                QPointF current(currentX, m_height-currentY);

                painter->drawLine(current, prev);
            }
        }
    }
}
