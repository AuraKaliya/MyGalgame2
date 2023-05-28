#include "slideblock.h"

SlideBlock::SlideBlock()
{
    m_isPressed=false;
    values=0;


}

void SlideBlock::setRect(QRect rect)
{
    m_abRect=rect;
}

void SlideBlock::mousePressEvent(QMouseEvent *e)
{
    m_isPressed=true;
    m_mouseStartPos=e->pos();
    qDebug()<<m_mouseStartPos;
    m_btnStarPos=this->frameGeometry().topLeft();

}

void SlideBlock::mouseMoveEvent(QMouseEvent *e)
{
    if((m_isPressed&&(this->x()>=m_abRect.x()))&&(values==0))
    {
       QPoint distance=e->pos()-m_mouseStartPos;
        //this->move((m_btnStarPos+distance).x(),m_btnStarPos.y());
       this->move(distance.x()+this->x(),m_btnStarPos.y());
        //this->move(e->pos().x()+this->x()-e->pos().x(),m_btnStarPos.y());
    }
}

void SlideBlock::mouseReleaseEvent(QMouseEvent *e)
{
    m_isPressed=false;
    if((this->x()<m_abRect.x()+10)&&(values==0))
    {
        this->move(m_abRect.x(),m_abRect.y());
       values=1;
        emit valueMax();
    }
    else
    {

        resetPos();
        if(values==1)
        {
            emit reset();
            values=0;
        }

    }
}

void SlideBlock::initPos()
{

}

void SlideBlock::resetPos()
{
    move(fixPos);
}

void SlideBlock::setMouseStartPos(QPoint newMouseStartPos)
{
   // m_mouseStartPos = newMouseStartPos;
    //m_mouseStartPos=QPoint(0,0);
    qDebug()<<m_mouseStartPos;
}

void SlideBlock::setFixPos(QPoint newFixPos)
{
    fixPos = newFixPos;
}
