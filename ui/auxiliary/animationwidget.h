/*
 *
 *  Copyright (c) 2010 Zagaia (INdT - Instituto Nokia de Tecnologia/
 *       FUCAPI - Fundação Centro de Análise, Pesquisa e Inovação Tecnológica)
 *
 *  This file is part of TweeGo.
 *
 *  TweeGo is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TweeGo is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TweeGo. If not, see <http://www.gnu.org/licenses/>
 *
 */

#ifndef APPLICATIONWIDGET_H
#define APPLICATIONWIDGET_H

#include <QtCore/QObject>
#include <QtGui/QGraphicsWidget>

/*!
 * \class ApplicationItem
 *
 * \brief The ApplicationItem class represents the graphics
 * items used in an scene. All application items shouls inherit
 * this class. There are properties pre-defined to be used by
 * animation framework.
 */
class AnimationWidget : public QGraphicsWidget
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos);
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity);
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)

public:
    AnimationWidget(QGraphicsWidget *parent = 0) : QGraphicsWidget(parent)
    {

    }

    ~AnimationWidget()
    {

    }

private:
    int _width;
    int _height;
};

#endif //APPLICATIONWIDGET_H
