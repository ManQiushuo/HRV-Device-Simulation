#ifndef HRVTABLE_H
#define HRVTABLE_H

#include <QList>
#include <QRandomGenerator>

class HRVtable
{
public:
    HRVtable();
    int cohGetAt(int index);
    int incGetAt(int index);
    float cohScoreGetAt(int index);
    float incScoreGetAt(int index);

private:
    QList<int> cohTable;
    QList<int> incTable;
    QList<float> cohScoreTable;
    QList<float> incScoreTable;
};

#endif // HRVTABLE_H
