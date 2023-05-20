#include <QPushButton>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QRectF>
#include "Main_Window.h"
#include "Levels.h"

/**
 * @brief Main_Window::Main_Window Contructor que crea la ventana principal
 * @param parent Hace posible que se cre la ventana
 */
Main_Window::Main_Window(QWidget *parent)
{
    //Creation of the scene
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    //Creation and configuration of the title
    QLabel *label = new QLabel("Pac-Man");
    QGraphicsProxyWidget *proxy_label = new QGraphicsProxyWidget(); //Widget that makes posible to use a QLabel in a QGraphicsscene
    proxy_label->setWidget(label);
    QFont font("Arial", 20, QFont::Helvetica);
    label->setStyleSheet("background-color: white");
    label->setFont(font);
    scene->addItem(proxy_label);
    proxy_label->setPos(335, 20);

    //Creaction and configuration of normal mode button
    QPushButton * play_button = new QPushButton("Play!");
    play_button->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_normal = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_normal->setWidget(play_button);
    scene->addItem(proxy_normal);
    proxy_normal->setPos(300,240);

    //Configuration of the scene
    connect(play_button, &QPushButton::released, this, &Main_Window::game);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    show();
}

/**
 * @brief Main_Window::game Funcion que inicia el nivel 1
 */
void Main_Window::game()
{
    Levels *level_1 = new Levels();
    level_1->show();
    this->close();
}
