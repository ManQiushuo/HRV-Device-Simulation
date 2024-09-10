#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QVector>

class Menu {

public:
    explicit Menu(QString, QStringList, Menu*);
    ~Menu();

    QString getName();
    QStringList getMenuItems();
    QStringList& getMenuItemsDynamic();
    Menu* getParent();
    int getPos();
    Menu* get(int);
    void addChildMenu(Menu*);

private:
    QString name;
    QStringList menuItems;
    int position;
    QVector<Menu*> subMenus;
    Menu* parent;

};


#endif // MENU_H
