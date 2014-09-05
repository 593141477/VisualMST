/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include "vertexs.h"

#include <QSet>
#include <QPointF>

class MSTGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    enum PointerMode{SelectMode, MoveMode, DrawPointMode};
    MSTGraphicsView(QWidget* parent = 0) : QGraphicsView(parent){}


    void initView();
protected:
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent * e);

    void resetView();
    void setupMatrix();

public slots:
    void zoomIn(qreal val);
    void zoomOut(qreal val);
    void setPointerMode(PointerMode mode);

private:
    //from -1 to +1
    qreal zoom;
    PointerMode mCurMode;

    MSTVertexes *vertexes;

signals:
    void newPointEvent(QPointF pt);
};

#endif
