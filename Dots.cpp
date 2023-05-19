#include "Dots.h"
#include <QPixmap>

/**
 * @brief Dot::Dot COntructor que crea una pastilla en el laberinto
 */
Dot::Dot()
{
    setPixmap(QPixmap(":/Images/Dot.png"));
}

