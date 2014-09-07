#include "thumbdialog.h"
#include "views/navigationrect.h"
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QPen>
#include <QDebug>

ThumbDialog::ThumbDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    setModal(false);
    setGeometry(0, 0, 195, 120);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setWindowTitle("Navigation");

    QGridLayout *layout = new QGridLayout;
    mView = new QGraphicsView;
    mScene = new QGraphicsScene;

    mView->setScene(mScene);
    layout->addWidget(mView, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    QPen pen;
    pen.setColor(QColor(Qt::red));
//    pen.setWidthF(2);
    mMapRect = new NavigationRect(this);
    mMapRect->setPen(pen);
    mMapRect->setFlags(QGraphicsRectItem::ItemIsMovable);
    mScene->addItem(mMapRect);

    mView->setDragMode(QGraphicsView::RubberBandDrag);
    mView->setInteractive(true);
//    mView->setCursor(QCursor(Qt::OpenHandCursor));
}

void ThumbDialog::mapRectMove(bool isMoving)
{
    rectMoving = isMoving;
}


void ThumbDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    if(mOrigSceneRect.width() > 0 && mOrigSceneRect.height() > 0)
        setFullMapRect(mOrigSceneRect);
}

void ThumbDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    if(rectMoving){
        QRectF r = mMapRect->rect();
        r.translate(mMapRect->pos());

        QPointF tl = r.topLeft(), br = r.bottomRight();
        QRectF newRect = QRectF(
                    QPointF(tl.x()/mWidthFactor, tl.y()/mHeightFactor),
                    QPointF(br.x()/mWidthFactor, br.y()/mHeightFactor));
        newRect.translate(mXOffset, mYOffset);
//        qDebug() << __func__ << r << newRect;

        emit navChanged(newRect);
    }
}

void ThumbDialog::setFullMapRect(QRectF rect)
{
    int widget_w = mView->width()-3, widget_h = mView->height()-3;
    mOrigSceneRect = rect;
    mXOffset = rect.x();
    mYOffset = rect.y();
    mWidthFactor = widget_w/rect.width();
    mHeightFactor = widget_h/rect.height();
    rect.setRect(0, 0, widget_w, widget_h);
    mScene->setSceneRect(rect);
    mView->fitInView(rect, Qt::KeepAspectRatio);
    mView->ensureVisible(rect);
    mMapRect->setPos(0, 0);
}

void ThumbDialog::setCurrentMapRect(QRectF rect)
{
    if(rectMoving)
        return;
    rect.translate(-mXOffset, -mYOffset);
    QPointF tl = rect.topLeft(), br = rect.bottomRight();
    QRectF newRect = QRectF(
                QPointF(tl.x()*mWidthFactor, tl.y()*mHeightFactor),
                QPointF(br.x()*mWidthFactor, br.y()*mHeightFactor));
//    qDebug() << rect << newRect;
    mMapRect->setRect(newRect);
    mMapRect->setPos(0, 0);
}
