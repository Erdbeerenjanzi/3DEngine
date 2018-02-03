#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <qmath.h>
#include <algorithm>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);

        graphScene = new QGraphicsScene;
        graphScene->setSceneRect(0,0,400,400);
        ui->graphicsView->setScene(graphScene);
        frameNumber = 0;
        image = QImage(400,400, QImage::Format_RGB888);
        point = image.bits();

        VertexList.push_back(Vec4(1,0,0,1));    //Oben links
        VertexList.push_back(Vec4(0,1,0,1));    //Unten rechts
        VertexList.push_back(Vec4(0,0,0,1));    //Unten links

        VertexList.push_back(Vec4(1,1,0,1));    //Oben rechts
        VertexList.push_back(Vec4(0,1,0,1));    //Unten rechts
        VertexList.push_back(Vec4(1,0,0,1));    //Oben links


        ColorList.push_back(ColorRGB8(0,0,250));
        ColorList.push_back(ColorRGB8(0,250,0));
        ColorList.push_back(ColorRGB8(250,0,0));

        ColorList.push_back(ColorRGB8(250,0,0));
        ColorList.push_back(ColorRGB8(0,250,0));
        ColorList.push_back(ColorRGB8(0,0,250));
        /////



        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(RenderCycle()));
        timer->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RenderCycle()
{
    using namespace std;
    clock_t begin = clock();

       image.fill(Qt::GlobalColor::white);
       Wireframe = ui->checkBox_wireframe->isChecked();
      // point = image.bits();


       Mat4x4 mat0;
       Mat4x4 mat1;

        if(ui->checkBox_rotate->isChecked())
        {
          mat0  = Mat4x4::RotateYMat(0.01*(double)frameNumber);
          mat1  = Mat4x4::RotateZMat(0.01*(double)frameNumber);

        }
        else
        {
            mat0  = Mat4x4::RotateYMat(0.01);
            mat1  = Mat4x4::RotateZMat(0.05);
        }

        Mat4x4 mat2 = Mat4x4::TranslatioMat(-0.2,0,-1.5);
        Mat4x4 mat3 = Mat4x4::ProjectionMat(1.5,1.5,0.1,100);
        Mat4x4 mat4 = Mat4x4::ViewportMat(400,-400,200,200);

        Mat4x4 ges;
        ges = mat4*mat3*mat2*mat1*mat0;

        for(int i=0; i<VertexList.size(); i=i+3)
        {
            Vec4 vec1 = ges*VertexList.at(i);
            vec1.dehomogenize();
            Vec4 vec2 = ges*VertexList.at(i+1);
            vec2.dehomogenize();
            Vec4 vec3 = ges*VertexList.at(i+2);
            vec3.dehomogenize();
            if(Wireframe)
            {
                BresenhamLine(vec1.x,vec1.y,vec2.ele[0],vec2.y, ColorList.at(i), ColorList.at(i+1));
                BresenhamLine(vec2.x,vec2.y,vec3.ele[0],vec3.y, ColorList.at(i+1), ColorList.at(i+2));
                BresenhamLine(vec1.x,vec1.y,vec3.ele[0],vec3.y, ColorList.at(i), ColorList.at(i+2));
                setPixel(vec1.ele[0],vec1.y,ColorList.at(i));
            }
            else
            {
                Pineda(vec1,vec2,vec3,ColorList.at(i),ColorList.at(i+1),ColorList.at(i+2));
            }

            //BresenhamLine(60,50,10,60);

            //point[(int)(vecGes.ele[0])+400*(int)(vecGes.y)] = 0;
        }



    QGraphicsPixmapItem item( QPixmap::fromImage(image));
    graphScene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphScene);

    frameNumber++;
    ui->graphicsView->show();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000);
    std::cout << std::setprecision(12) << elapsed_secs << std::endl;

    return;

}


void MainWindow::BresenhamLine(int xstart, int ystart, int xend, int yend,   ColorRGB8 colorstart,   ColorRGB8 colorend)
{
 // int color[3] = {255,0,0};

    double lambda = 0;
    double denom;
    double startVal;
    double tempy = ystart;

  int dx =  abs(xend-xstart), sx = xstart<xend ? 1 : -1;
  int dy = -abs(yend-ystart), sy = ystart<yend ? 1 : -1;
  int err = dx+dy, e2; /* error value e_xy */

//    if(dy>=dx)
//    {
//     denom = 1.0/(yend-ystart);
//     startVal = ystart;
//    }
//    else
//    {
//      denom = 1.0/(end-xstart);
//      startVal = xstart;
//    }
  denom = 1.0/(yend-ystart);
  startVal = ystart;

  while(1){

    //Color calc
    //lambda = (ystart-startVal)/(yend-startVal);
    ColorRGB8 resCol = colorend*lambda+colorstart*(1.0-lambda);
    setPixel(xstart,ystart,resCol);
    //

    if (xstart==xend && ystart==yend) break;
    e2 = 2*err;
    if (e2 > dy) { err += dy; xstart += sx;  } /* e_xy+e_x > 0 */
    if (e2 < dx) { err += dx; ystart += sy; lambda+=denom*sy;} /* e_xy+e_y < 0 */
  }
}



void MainWindow::Pineda(Vec4& vec1, Vec4& vec2 ,Vec4& vec3, ColorRGB8 col1, ColorRGB8 col2, ColorRGB8 col3)
{
    //Für die Farben
    double lambda1 = 0;
    double lambda2 = 0;
    double lambda3 = 0;
    double lambdares = 0;

    ColorRGB8 ipolCol1;
    ColorRGB8 ipolCol2;
    ColorRGB8 ipolCol3;

    double bl_xbox;
    double bl_ybox;
    double tr_xbox;
    double tr_ybox;

    bl_xbox = std::min(vec1.x,std::min(vec2.x,vec3.x));         //Calculating the boudning box of the triangle
    bl_ybox = std::min(vec1.y,std::min(vec2.y,vec3.y));
    tr_xbox = std::max(vec1.x,std::max(vec2.x,vec3.x));
    tr_ybox = std::max(vec1.y,std::max(vec2.y,vec3.y));

    Vec4 tempvec;
    ColorRGB8 tempcol;

    //Bubble sort
    if(vec1.y > vec2.y)
    {
       tempvec = vec1;
       vec1 = vec2;
       vec2 = tempvec;

       tempcol = col1;
       col1 = col2;
       col2 = tempcol;
    }

    if(vec2.y > vec3.y)
    {
       tempvec = vec2;
       vec2 = vec3;
       vec3 = tempvec;

       tempcol = col2;
       col2 = col3;
       col3 = tempcol;
    }

    if(vec1.y > vec2.y)
    {
       tempvec = vec1;
       vec1 = vec2;
       vec2 = tempvec;

       tempcol = col1;
       col1 = col2;
       col2 = tempcol;
    }

    Vec4 vecD;
    Vec4 vecE;
    Vec4 dir1 = vec2-vec1;
    Vec4 dir2 = vec3-vec2;
    Vec4 dir3 = vec1-vec3;

    for(int k=bl_ybox; k<=(tr_ybox); k++)
    {

        lambda2 = ((double)k-vec1.y)/(vec3.y-vec1.y);   //Lambda2 von A zu C
        if(k<vec2.y)
        {
        lambda1 = ((double)k-vec1.y)/(vec2.y-vec1.y);
        vecD = Vec4((1.0-lambda1)*vec1.x+lambda1*vec2.x,k,0,0);
        vecE = Vec4((1.0-lambda2)*vec1.x+lambda2*vec3.x,k,0,0);
        }
        else
        {
        lambda1 = ((double)k-vec2.y)/(vec3.y-vec2.y);   //Lambda1 von B zu C
        vecD = Vec4((1.0-lambda1)*vec2.x+lambda1*vec3.x,k,0,0);
        vecE = Vec4((1.0-lambda2)*vec1.x+lambda2*vec3.x,k,0,0);
        }

        for(int i=bl_xbox; i<=(tr_xbox); i++)
        {

            double ed1 = EdgeFunction(dir1,Vec4((double)i-vec1.x,(double)k-vec1.y,0.0,0.0));
            double ed2 = EdgeFunction(dir2,Vec4((double)i-vec2.x,(double)k-vec2.y,0.0,0.0));
            double ed3 = EdgeFunction(dir3,Vec4((double)i-vec3.x,(double)k-vec3.y,0.0,0.0));

            if( (ed1<=0)&&(ed2<=0)&&(ed3<=0)||(ed1>=0)&&(ed2>=0)&&(ed3>=0) )
                {

                    ipolCol2 = col3*lambda2+col1*(1.0-lambda2);     //Farbe von A zu C

                    if(k<vec2.y)
                    {
                        ipolCol1 = col2*lambda1+col1*(1.0-lambda1);
                    }
                    else
                    {
                        ipolCol1 = col3*lambda1+col2*(1.0-lambda1);     //Farbe von B zu C
                    }

                    lambda3 = ((double)i-vecD.x)/(vecE.x-vecD.x);
                    ipolCol3 = ipolCol2*lambda3+ipolCol1*(1.0-lambda3);
                    setPixel(i,k, ipolCol3);

                }
        }
    }

}

double MainWindow::EdgeFunction(Vec4 vec1, Vec4 vec2)
{
  return  vec1.x*vec2.y-vec1.y*vec2.x;
}


void SimpleLine(int xstart, int ystart, int xend, int yend)
{
    int dx = xend-xstart; //Inkremente
    int dy = yend-ystart;


}


inline void MainWindow::setPixel(int x, int y, const ColorRGB8& color)
{
    QRgb colorval = qRgb((int)color.r,(int)color.g,(int)color.b);

    if((x>=400)||(x<0))
    {
        std::cout << "Error";
        return;
    }

    if((y>=400)||(y<0))
    {
        std::cout << "Error";
        return;
    }

    image.setPixel(x,y,colorval);
    image.setPixel(x-1,y,colorval);
    image.setPixel(x,y-1,colorval);
    image.setPixel(x-1,y-1,colorval);

    return;
}





