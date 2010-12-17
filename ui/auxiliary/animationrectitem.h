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

#ifndef APPLICATIONRECTITEM_H
#define APPLICATIONRECTITEM_H

#include <QtCore/QObject>
#include "graphicsrectobject.h"

/*!
 * \class ApplicationItem
 *
 * \brief The ApplicationItem class represents the graphics
 * items used in an scene. All application items shouls inherit
 * this class. There are properties pre-defined to be used by
 * animation framework.
 */
class AnimationRectItem : public GraphicsRectObject
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity);

public:
    AnimationRectItem(const QRectF & rect, QGraphicsItem * parent = 0) : GraphicsRectObject(rect, parent)
    {

    }
    ~AnimationRectItem()
    {

    }
};

#endif //APPLICATIONRECTITEM_H
