#include "glwidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <math.h>
#include <QElapsedTimer>
#define PI 3.14159265

GLWidget::GLWidget()
{

}

void GLWidget::initializeGL()
{
    emit sendSignalToMainWindow(); //Start getting information
    initializeOpenGLFunctions();
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(updateWidget()));
    myTimer->start(10);
    glClearColor(1.0f,1.0f,1.0f,1.0f); //set white background color

    prepareData();
    initializeNode();
    initializePrismLine();
    initializePrismLineDeform();
    initializePrismElement();
    initializeAxis();
}

void GLWidget::paintGL()
{    
    //OpenGL native function
    //-------------------------------------------------------------------------------------0
    QPainter painter(this);
    painter.beginNativePainting();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear color
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(0.3f);
    glViewport(0,0,this->width(),this->height());

    if(coordinatesScale.rows()>1)
    {
        if(contourSettingObject.nodeVisible==true){paintNode();}
        if(contourSettingObject.meshVisible==true){paintPrismLine();}
        if(contourSettingObject.deformedMeshVisible==true){paintPrismLineDeform();}
        if(contourSettingObject.resultVisible==true){ paintPrismElement();}
    }

    glDisable(GL_DEPTH_TEST);
    glLineWidth(5.0f);
    paintAxis();
    painter.endNativePainting();
    //-------------------------------------------------------------------------------------
    int noc=contourSettingObject.noc;
    MatrixXd contour=MatrixXd::Zero(noc+1,1);
    for (int i=0;i<(noc+1);i++)
    {
        contour(i,0)=stepResultObject.minValue+(stepResultObject.maxValue-stepResultObject.minValue)*i/(noc);
    }

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",contourSettingObject.fontSize));
    QString maxString, minString, dateString, titleString, tempString;
    dateString=QDate::currentDate().toString("dd.MM.yyyy");

    int numType=contourSettingObject.numericType;
    if(numType==0)
    {
    maxString="Max Value (Blue Color): "+QString::number(stepResultObject.maxValue,'f',3);
    minString="Min Value (Red Color): "+QString::number(stepResultObject.minValue,'f',3);
    }
    else if(numType==1)
    {
        maxString="Max Value (Blue Color): "+QString::number(stepResultObject.maxValue,'f',0);
        minString="Min Value (Red Color): "+QString::number(stepResultObject.minValue,'f',0);
    }
    else if(numType==2)
    {
        maxString="Max Value (Blue Color): "+QString::number(stepResultObject.maxValue,'e',3);
        minString="Min Value (Red Color): "+QString::number(stepResultObject.minValue,'e',3);
    }

    int maxY=2*contourSettingObject.fontSize;
    if(contourSettingObject.titleVisible==true)
    {
        painter.drawText(0,maxY,contourSettingObject.title);
        maxY=maxY+2*contourSettingObject.fontSize;
    }

    if(contourSettingObject.dateVisible==true)
    {
        painter.drawText(0,maxY,dateString);
        maxY=maxY+2*contourSettingObject.fontSize;
    }

    if(contourSettingObject.maxVisible==true)
    {
        painter.drawText(0,maxY,maxString);
        maxY=maxY+2*contourSettingObject.fontSize;
        painter.drawText(0,maxY,minString);
        maxY=maxY+2*contourSettingObject.fontSize;
    }

    int widthSize=this->width();
    int heightSize=this->height();
    int GradientH=heightSize-maxY-contourSettingObject.fontSize;
    int GradientW=widthSize-200;
    QLinearGradient m_gradient(QPoint(0,maxY),QPoint(0,maxY+GradientH));

    //from min to max
    m_gradient.setColorAt(0.0,Qt::red);
    m_gradient.setColorAt(0.5,Qt::green);
    m_gradient.setColorAt(1.0,Qt::blue);

    if(contourSettingObject.contourPosition==0){painter.fillRect(QRect(QPoint(10,maxY),QSize(20,GradientH)),m_gradient);}
    else if(contourSettingObject.contourPosition==1)
    {
        maxY=20;
        GradientH=heightSize-maxY-contourSettingObject.fontSize;
        QLinearGradient m_gradient(QPoint(0,maxY),QPoint(0,maxY+GradientH));
        m_gradient.setColorAt(0.0,Qt::red);
        m_gradient.setColorAt(0.5,Qt::green);
        m_gradient.setColorAt(1.0,Qt::blue);
        painter.fillRect(QRect(QPoint(widthSize-100,maxY),QSize(20,GradientH)),m_gradient);
    }
    else if(contourSettingObject.contourPosition==2)
    {
        //m_gradient.sets(QPoint(0,100),QPoint(0,600));
        QLinearGradient m_gradient(QPoint(100,0),QPoint(GradientW,0));
        m_gradient.setColorAt(0.0,Qt::red);
        m_gradient.setColorAt(0.5,Qt::green);
        m_gradient.setColorAt(1.0,Qt::blue);
        painter.fillRect(QRect(QPoint(100,heightSize-40-2*contourSettingObject.fontSize),QSize(GradientW,20)),m_gradient);
    }

    for (int i=0;i<(noc+1);i++)
    {
        if(numType==0){tempString=QString::number(contour(i,0),'f',3);}
        else if(numType==1){tempString=QString::number(contour(i,0),'f',0);}
        else if(numType==2){tempString=QString::number(contour(i,0),'e',3);}
        if(contourSettingObject.contourPosition==0){painter.drawText(30+0.5*contourSettingObject.fontSize,maxY+0.5*contourSettingObject.fontSize+i*GradientH/(noc),tempString);}
        else if(contourSettingObject.contourPosition==1)
        {
            maxY=20;
            GradientH=heightSize-maxY-contourSettingObject.fontSize;
            painter.drawText(widthSize-78,maxY+0.5*contourSettingObject.fontSize+i*GradientH/(noc),tempString);
        }
        else if(contourSettingObject.contourPosition==2)
        {
            painter.drawText(100+0.5*contourSettingObject.fontSize+i*GradientW/(noc),heightSize-20+0.5*contourSettingObject.fontSize,tempString);
        }
    }
    //-------------------------------------------------------------------------------------

}

void GLWidget::resizeGL(int w, int h)
{
    float aspect;
    aspect=(float)w/h;
    viewPortSettingObject.xRight=viewPortSettingObject.xLeft+(viewPortSettingObject.yTop-viewPortSettingObject.yBot)*aspect;
    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(viewPortSettingObject.xLeft,viewPortSettingObject.xRight,viewPortSettingObject.yBot,viewPortSettingObject.yTop,-500000,500000);
}

void GLWidget::prepareData()
{
    viewPortSettingObject.xMax=coordinatesScale.col(1).maxCoeff();
    viewPortSettingObject.xMin=coordinatesScale.col(1).minCoeff();

    viewPortSettingObject.yMax=coordinatesScale.col(2).maxCoeff();
    viewPortSettingObject.yMin=coordinatesScale.col(2).minCoeff();

    viewPortSettingObject.zMax=coordinatesScale.col(3).maxCoeff();
    viewPortSettingObject.zMin=coordinatesScale.col(3).minCoeff();

    viewPortSettingObject.xCenter=0.5*(viewPortSettingObject.xMax+viewPortSettingObject.xMin);
    viewPortSettingObject.yCenter=0.5*(viewPortSettingObject.yMax+viewPortSettingObject.yMin);
    viewPortSettingObject.zCenter=0.5*(viewPortSettingObject.zMax+viewPortSettingObject.zMin);

    wheelScrollDistance=0;
    transformMatrix.setToIdentity();
    transformMatrix.translate(0.0f,0.0f,0.0f);
    cameraMatrix.setToIdentity();
    projectionMatrix.setToIdentity();

    //if lockview or replot, the viewport settting is similar to last step
    if(viewPortSettingObject.lockView==false)
    {
        viewPortSettingObject.xLeft0=viewPortSettingObject.xMin;
        viewPortSettingObject.xRight0=viewPortSettingObject.xMax;
        viewPortSettingObject.yBot0=viewPortSettingObject.yMin;
        viewPortSettingObject.yTop0=viewPortSettingObject.yMax;
        viewPortSettingObject.cameraMatrix.setToIdentity();
    }

    wheelScrollScaleFactor=1;
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;
    cameraMatrix=viewPortSettingObject.cameraMatrix;

    updateCheck=true;
    if(coordinatesDeform.rows()>1)
    {
        nodeData();
        prismLineData();
        prismLineDeformData();
        prismElementData();
    }
    axisData();
}

void GLWidget::nodeData()
{
    Vector_Node.resize(numberOfNode);
    Vector_NodeColor.resize(numberOfNode);
    //Data for Node
    for (int i=0;i<numberOfNode;i++)
    {
        Vector_Node[i]=Vector3f(coordinatesScale(i,1),coordinatesScale(i,2),coordinatesScale(i,3));;
    }
    for (int i=0;i<numberOfNode;i++)
    {
        Vector_NodeColor[i]=Vector3f(1.0f,0.0f,0.5f);//Red color, should be changed if some special effects are needed
    }
}

void GLWidget::initializeNode()
{
    //OpenGL Shader Program
    ShaderProgram_Node=new QOpenGLShaderProgram();
    ShaderProgram_Node->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/node.vert");
    ShaderProgram_Node->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/node.frag");
    ShaderProgram_Node->link();
    ShaderProgram_Node->bind();

    //Uniform Location in GPU memory
    modelToWorld_Node=ShaderProgram_Node->uniformLocation("modelToWorld");
    worldToCamera_Node = ShaderProgram_Node->uniformLocation("worldToCamera");
    cameraToView_Node = ShaderProgram_Node->uniformLocation("cameraToView");

    //Buffer Object
    VertexBuffer_Node.create();
    VertexBuffer_Node.bind();
    VertexBuffer_Node.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VertexBuffer_Node.allocate(&Vector_Node[0],numberOfNode*sizeof(Vector_Node[0])); //Allowcate memory, link to Vecto_node;

    //Vertex Array
    VertexArray_Node.create();
    VertexArray_Node.bind();
    ShaderProgram_Node->enableAttributeArray(0); //Location 0, node coordinates
    ShaderProgram_Node->setAttributeBuffer(0,GL_FLOAT,0,3,12); //0 offset, 3 tuplesize, 12 bytes per vector node

    //Release Phase
    VertexArray_Node.release();
    VertexBuffer_Node.release();
    ShaderProgram_Node->release();
}

void GLWidget::paintNode()
{
    ShaderProgram_Node->bind();
    ShaderProgram_Node->setUniformValue(worldToCamera_Node,cameraMatrix);
    ShaderProgram_Node->setUniformValue(cameraToView_Node, projectionMatrix);
    ShaderProgram_Node->setUniformValue(modelToWorld_Node, transformMatrix);

    {
        VertexArray_Node.bind();
        glDrawArrays(GL_POINTS,0,numberOfNode); //Draw nodes
        VertexArray_Node.release();
    }
    ShaderProgram_Node->release();
}

void GLWidget::prismElementData()
{
    //Using deformation coordinates
    Vector_Element.resize(0);
    Vector_ElementColor.resize(0);
    Vector_Element.reserve(8*numberOfElement); //8-faces
    Vector_ElementColor.reserve(8*numberOfElement);

    double nodeValue;
    MatrixXd nodeColor=MatrixXd::Zero(6,3); //6-nodes
    MatrixXd nodeIndex=MatrixXd::Zero(6,1); //6-nodes
    MatrixXd faceIndex=MatrixXd::Zero(8,3); //node 1, 2, 3
    unsigned nodeA, nodeB, nodeC;
    float redA, redB, redC;
    float blueA, blueB, blueC;
    float greenA, greenB, greenC;
    double minimumValue=stepResultObject.minValue;
    double maximumValue=stepResultObject.maxValue;

    for (int i=0;i<numberOfElement;i++)
    {
        for (int j=0;j<6;j++)
        {
            nodeIndex(j,0)=elements(i,j+1)-1;
            nodeValue=results(nodeIndex(j,0),0);
            calculateRGB_Color(minimumValue,maximumValue,nodeValue);
            nodeColor(j,0)=redColor;
            nodeColor(j,1)=greenColor;
            nodeColor(j,2)=blueColor;
        }
        faceIndex<<1,2,3,
                4,5,6,
                1,3,4,
                4,3,6,
                2,5,3,
                3,5,6,
                1,2,4,
                4,2,5;
        for (int j=0;j<8;j++)
        {
            nodeA=nodeIndex(faceIndex(j,0)-1,0);
            nodeB=nodeIndex(faceIndex(j,1)-1,0);
            nodeC=nodeIndex(faceIndex(j,2)-1,0);

            redA=nodeColor(faceIndex(j,0)-1,0);
            redB=nodeColor(faceIndex(j,1)-1,0);
            redC=nodeColor(faceIndex(j,2)-1,0);

            blueA=nodeColor(faceIndex(j,0)-1,1);
            blueB=nodeColor(faceIndex(j,1)-1,1);
            blueC=nodeColor(faceIndex(j,2)-1,1);

            greenA=nodeColor(faceIndex(j,0)-1,2);
            greenB=nodeColor(faceIndex(j,1)-1,2);
            greenC=nodeColor(faceIndex(j,2)-1,2);

            Vector_Element.push_back(Vector3f(coordinatesDeform(nodeA,1),coordinatesDeform(nodeA,2),coordinatesDeform(nodeA,3)));
            Vector_Element.push_back(Vector3f(coordinatesDeform(nodeB,1),coordinatesDeform(nodeB,2),coordinatesDeform(nodeB,3)));
            Vector_Element.push_back(Vector3f(coordinatesDeform(nodeC,1),coordinatesDeform(nodeC,2),coordinatesDeform(nodeC,3)));

            Vector_ElementColor.push_back(Vector3f(redA,blueA,greenA));
            Vector_ElementColor.push_back(Vector3f(redB,blueB,greenB));
            Vector_ElementColor.push_back(Vector3f(redC,blueC,greenC));
        }
    }
}

void GLWidget::initializePrismElement()
{
    //Shaders (Vertex + Color)
    ShaderProgram_Element=new QOpenGLShaderProgram();
    ShaderProgram_Element->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/element.vert");
    ShaderProgram_Element->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/element.frag");
    ShaderProgram_Element->link();
    ShaderProgram_Element->bind();
    VertexArray_Element.create();
    VertexArray_Element.bind();

    // Cache Uniform Locations
    modelToWorld_Element = ShaderProgram_Element->uniformLocation("modelToWorld");
    worldToCamera_Element = ShaderProgram_Element->uniformLocation("worldToCamera");
    cameraToView_Element = ShaderProgram_Element->uniformLocation("cameraToView");
    normVector_Element=ShaderProgram_Element->uniformLocation("normVector");
    normPoint_Element=ShaderProgram_Element->uniformLocation("pointVector");

    VertexBuffer_Element.create();
    VertexBuffer_Element.bind();
    VertexBuffer_Element.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VertexBuffer_Element.allocate(&Vector_Element[0],Vector_Element.size()*sizeof(Vector_Element[0]));
    ShaderProgram_Element->enableAttributeArray(4); //Location 0, node coordinates
    ShaderProgram_Element->setAttributeBuffer(4,GL_FLOAT,0,3,12); //0 offset, 3 tuplesize, 12 bytes per vector node
    VertexBuffer_Element.release();

    ColorBuffer_Element.create();
    ColorBuffer_Element.bind();
    ColorBuffer_Element.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ColorBuffer_Element.allocate(&Vector_ElementColor[0],Vector_ElementColor.size()*sizeof(Vector_ElementColor[0]));
    ShaderProgram_Element->enableAttributeArray(5);
    ShaderProgram_Element->setAttributeBuffer(5,GL_FLOAT,0,3,12);
    ColorBuffer_Element.release();

    VertexArray_Element.release();
    ShaderProgram_Element->release();
}

void GLWidget::paintPrismElement()
{
    ShaderProgram_Element->bind();
    ShaderProgram_Element->setUniformValue(worldToCamera_Element,cameraMatrix);
    ShaderProgram_Element->setUniformValue(cameraToView_Element, projectionMatrix);
    ShaderProgram_Element->setUniformValue(modelToWorld_Element, transformMatrix);
    ShaderProgram_Element->setUniformValue(normVector_Element,cuttingPlaneSettingObject.normVector);
    ShaderProgram_Element->setUniformValue(normPoint_Element,cuttingPlaneSettingObject.pointVector);

    {
        VertexArray_Element.bind();
        glDrawArrays(GL_TRIANGLES,0,Vector_Element.size());
        VertexArray_Element.release();
    }
    ShaderProgram_Element->release();
}

void GLWidget::prismLineDeformData()
{
    Vector_LineDeform.resize(0);
    Vector_LineDeform.reserve(9*3*numberOfElement);
    unsigned int nodeA, nodeB;
    MatrixXd nodeIndex=MatrixXd::Zero(6,1);
    for (int i=0;i<numberOfElement;i++)
    {
        nodeIndex(0,0)=elements(i,1)-1; //index start with 1
        nodeIndex(1,0)=elements(i,2)-1;
        nodeIndex(2,0)=elements(i,3)-1;
        nodeIndex(3,0)=elements(i,4)-1;
        nodeIndex(4,0)=elements(i,5)-1;
        nodeIndex(5,0)=elements(i,6)-1;
        MatrixXd lineIndex=MatrixXd::Zero(9,2);
        lineIndex<<1,2,2,3,3,1,4,5,5,6,6,4,1,4,2,5,3,6;
        for (int j=0;j<lineIndex.rows();j++)
        {
            nodeA=nodeIndex(lineIndex(j,0)-1,0);
            nodeB=nodeIndex(lineIndex(j,1)-1,0);
            Vector_LineDeform.push_back(Vector3f(coordinatesDeform(nodeA,1),coordinatesDeform(nodeA,2),coordinatesDeform(nodeA,3)));
            Vector_LineDeform.push_back(Vector3f(coordinatesDeform(nodeB,1),coordinatesDeform(nodeB,2),coordinatesDeform(nodeB,3)));
        }
    }
}

void GLWidget::initializePrismLineDeform()
{
    ShaderProgram_LineDeform=new QOpenGLShaderProgram();
    ShaderProgram_LineDeform->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/lineDeform.vert");
    ShaderProgram_LineDeform->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/lineDeform.frag");
    ShaderProgram_LineDeform->link();
    ShaderProgram_LineDeform->bind();

    // Cache Uniform Locations
    modelToWorld_Line = ShaderProgram_LineDeform->uniformLocation("modelToWorld");
    worldToCamera_Line = ShaderProgram_LineDeform->uniformLocation("worldToCamera");
    cameraToView_Line = ShaderProgram_LineDeform->uniformLocation("cameraToView");
    normVector_Line=ShaderProgram_LineDeform->uniformLocation("normVector");
    normPoint_Line=ShaderProgram_LineDeform->uniformLocation("pointVector");

    VertexArray_LineDeform.create();
    VertexArray_LineDeform.bind();

    VertexBuffer_LineDeform.create();
    VertexBuffer_LineDeform.bind();

    VertexBuffer_LineDeform.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VertexBuffer_LineDeform.allocate(&Vector_LineDeform[0],Vector_LineDeform.size()*sizeof(Vector_LineDeform[0]));

    ShaderProgram_LineDeform->enableAttributeArray(8);
    ShaderProgram_LineDeform->setAttributeBuffer(8,GL_FLOAT,0,3,12); //0 offset, 3 tuplesize, 12 bytes per vector node

    VertexArray_LineDeform.release();
    VertexBuffer_LineDeform.release();
    ShaderProgram_LineDeform->release();
}

void GLWidget::paintPrismLineDeform()
{
    ShaderProgram_LineDeform->bind();
    ShaderProgram_LineDeform->setUniformValue(worldToCamera_Line,cameraMatrix);
    ShaderProgram_LineDeform->setUniformValue(cameraToView_Line, projectionMatrix);
    ShaderProgram_LineDeform->setUniformValue(modelToWorld_Line, transformMatrix);
    ShaderProgram_LineDeform->setUniformValue(normVector_Line,cuttingPlaneSettingObject.normVector);
    ShaderProgram_LineDeform->setUniformValue(normPoint_Line,cuttingPlaneSettingObject.pointVector);

    {
        VertexArray_LineDeform.bind();
        glDrawArrays(GL_LINES,0,Vector_LineDeform.size());
        VertexArray_LineDeform.release();
    }
    ShaderProgram_LineDeform->release();
}

void GLWidget::prismLineData()
{
    Vector_Line.resize(0);
    Vector_Line.reserve(9*3*numberOfElement);
    unsigned int nodeA, nodeB;
    MatrixXd nodeIndex=MatrixXd::Zero(6,1);
    for (int i=0;i<numberOfElement;i++)
    {
        nodeIndex(0,0)=elements(i,1)-1; //index start with 1
        nodeIndex(1,0)=elements(i,2)-1;
        nodeIndex(2,0)=elements(i,3)-1;
        nodeIndex(3,0)=elements(i,4)-1;
        nodeIndex(4,0)=elements(i,5)-1;
        nodeIndex(5,0)=elements(i,6)-1;
        MatrixXd lineIndex=MatrixXd::Zero(9,2);
        lineIndex<<1,2,2,3,3,1,4,5,5,6,6,4,1,4,2,5,3,6;
        for (int j=0;j<lineIndex.rows();j++)
        {
            nodeA=nodeIndex(lineIndex(j,0)-1,0);
            nodeB=nodeIndex(lineIndex(j,1)-1,0);
            Vector_Line.push_back(Vector3f(coordinatesScale(nodeA,1),coordinatesScale(nodeA,2),coordinatesScale(nodeA,3)));
            Vector_Line.push_back(Vector3f(coordinatesScale(nodeB,1),coordinatesScale(nodeB,2),coordinatesScale(nodeB,3)));
        }
    }
}

void GLWidget::initializePrismLine()
{
    ShaderProgram_Line=new QOpenGLShaderProgram();
    ShaderProgram_Line->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/line.vert");
    ShaderProgram_Line->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/line.frag");
    ShaderProgram_Line->link();
    ShaderProgram_Line->bind();

    // Cache Uniform Locations
    modelToWorld_Line = ShaderProgram_Line->uniformLocation("modelToWorld");
    worldToCamera_Line = ShaderProgram_Line->uniformLocation("worldToCamera");
    cameraToView_Line = ShaderProgram_Line->uniformLocation("cameraToView");
    normVector_Line=ShaderProgram_Line->uniformLocation("normVector");
    normPoint_Line=ShaderProgram_Line->uniformLocation("pointVector");

    VertexArray_Line.create();
    VertexArray_Line.bind();

    VertexBuffer_Line.create();
    VertexBuffer_Line.bind();

    VertexBuffer_Line.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VertexBuffer_Line.allocate(&Vector_Line[0],Vector_Line.size()*sizeof(Vector_Line[0]));

    ShaderProgram_Line->enableAttributeArray(2);
    ShaderProgram_Line->setAttributeBuffer(2,GL_FLOAT,0,3,12); //0 offset, 3 tuplesize, 12 bytes per vector node

    VertexArray_Line.release();
    VertexBuffer_Line.release();
    ShaderProgram_Line->release();

}

void GLWidget::paintPrismLine()
{
    ShaderProgram_Line->bind();
    ShaderProgram_Line->setUniformValue(worldToCamera_Line,cameraMatrix);
    ShaderProgram_Line->setUniformValue(cameraToView_Line, projectionMatrix);
    ShaderProgram_Line->setUniformValue(modelToWorld_Line, transformMatrix);
    ShaderProgram_Line->setUniformValue(normVector_Line,cuttingPlaneSettingObject.normVector);
    ShaderProgram_Line->setUniformValue(normPoint_Line,cuttingPlaneSettingObject.pointVector);

    {
        VertexArray_Line.bind();
        glDrawArrays(GL_LINES,0,Vector_Line.size());
        VertexArray_Line.release();
    }
    ShaderProgram_Line->release();
}

void GLWidget::axisData()
{
    Vector_Axis.resize(6);
    Vector_Axis[0]=Vector3f(0.8f,-0.9f,0.0f); //Point 0,0,0
    Vector_Axis[1]=Vector3f(0.9f,-0.9f,0.0f); //Point 1,0,0 X-direction

    Vector_Axis[2]=Vector3f(0.8f,-0.9f,0.0f); //Point 0,0,0
    Vector_Axis[3]=Vector3f(0.8f,-0.8f,0.0f); //Point 0,1,0 Y-direction

    Vector_Axis[4]=Vector3f(0.8f,-0.9f,0.0f); //Point 0,0,0
    Vector_Axis[5]=Vector3f(0.8f,-0.9f,0.1f); //Point 0,0,1: Z direction

    //color for axis
    Vector_AxisColor.resize(6);
    Vector_AxisColor[0]=Vector3f(1.0f,0.0f,0.0f); //red
    Vector_AxisColor[1]=Vector3f(1.0f,0.0f,0.0f); //red

    Vector_AxisColor[2]=Vector3f(0.0f,1.0f,0.0f); //green
    Vector_AxisColor[3]=Vector3f(0.0f,1.0f,0.0f); //green

    Vector_AxisColor[4]=Vector3f(0.0f,0.0f,1.0f); //blue
    Vector_AxisColor[5]=Vector3f(0.0f,0.0f,1.0f); //blue

    Vector_AxisIndex.resize(3);
    Vector_AxisIndex[0]=Vector2i(0,1);
    Vector_AxisIndex[1]=Vector2i(2,3);
    Vector_AxisIndex[2]=Vector2i(4,5);
}

void GLWidget::initializeAxis()
{
    //Shader
    ShaderProgram_Axis=new QOpenGLShaderProgram();
    ShaderProgram_Axis->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/axis.vert");
    ShaderProgram_Axis->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/axis.frag");
    ShaderProgram_Axis->link();
    ShaderProgram_Axis->bind();

    // Cache Uniform Locations
    modelToWorld_Axis = ShaderProgram_Axis->uniformLocation("axis_modelToWorld");
    worldToCamera_Axis = ShaderProgram_Axis->uniformLocation("axis_worldToCamera");
    cameraToView_Axis = ShaderProgram_Axis->uniformLocation("axis_cameraToView");

    VertexBuffer_Axis.create();
    VertexBuffer_Axis.bind();
    VertexBuffer_Axis.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VertexBuffer_Axis.allocate(&Vector_Axis[0],6*sizeof(Vector_Axis[0]));

    VertexArray_Axis.create();
    VertexArray_Axis.bind();
    ShaderProgram_Axis->enableAttributeArray(6); //Location 0, node coordinates
    ShaderProgram_Axis->setAttributeBuffer(6,GL_FLOAT,0,3,12); //0 offset, 3 tuplesize, 12 bytes per vector node

    ColorBuffer_Axis.create();
    ColorBuffer_Axis.bind();
    ColorBuffer_Axis.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ColorBuffer_Axis.allocate(&Vector_AxisColor[0],6*sizeof(Vector_AxisColor[0]));

    ShaderProgram_Axis->enableAttributeArray(7);
    ShaderProgram_Axis->setAttributeBuffer(7,GL_FLOAT,0,3,12);

    VertexArray_Axis.release();
    ColorBuffer_Axis.release();
    ColorBuffer_Axis.release();
    ShaderProgram_Axis->release();
}

void GLWidget::paintAxis()
{
    ShaderProgram_Axis->bind();
    ShaderProgram_Axis->setUniformValue(worldToCamera_Axis,camera_Axis);
    ShaderProgram_Axis->setUniformValue(cameraToView_Axis, projection_Axis);
    {
        VertexArray_Axis.bind();
        // S_axis->setUniformValue(axis_modelToWorld, m_transform_modelToWorld);
        glDrawElements(GL_LINES,2,GL_UNSIGNED_INT,&Vector_AxisIndex[0]);
        glDrawElements(GL_LINES,2,GL_UNSIGNED_INT,&Vector_AxisIndex[1]);
        glDrawElements(GL_LINES,2,GL_UNSIGNED_INT,&Vector_AxisIndex[2]);
        VertexArray_Axis.release();
    }
    ShaderProgram_Axis->release();
}

void GLWidget::calculateRGB_Color(double minValue, double maxValue, double inputValue)
{
    double midValue=0.5*(maxValue+minValue);
    redColor=0.0f;
    greenColor=0.0f;
    blueColor=0.0f;

    if(maxValue==midValue)
    {
        redColor=1.0f;
        greenColor=0.0f;
        blueColor=0.0f;
        contourSettingObject.noc=2;
    }
    else{
        if (inputValue>maxValue || inputValue< minValue)
        {
            redColor=0.5f;
            greenColor=0.5f;
            blueColor=0.5f;
        }
        else if(inputValue>=minValue && inputValue<=midValue)
        {
            blueColor=0.0f;
            redColor=float((inputValue-midValue)/(minValue-midValue));
            greenColor=float((minValue-inputValue)/(minValue-midValue));

        }
        else if(inputValue<=maxValue && inputValue>midValue)
        {
            redColor=0.0f;
            greenColor=float((inputValue-maxValue)/(midValue-maxValue));
            blueColor=float((midValue-inputValue)/(midValue-maxValue));

        }
        else
        {
            QMessageBox::critical(this,"ERROR","OUT OF RANGE COLOR");
        }
    }
}

void GLWidget::pauseSystem()
{
    do {
        cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');
}

void GLWidget::forceToUpdateWiget()
{
    QOpenGLWidget::update();
}

void GLWidget::getShownData(Ref<MatrixXd> coordinatesScale, Ref<MatrixXd> coordinatesDeform, Ref<MatrixXd> elements, Ref<MatrixXd> results)
{
    this->coordinatesScale=coordinatesScale;
    this->coordinatesDeform=coordinatesDeform;
    this->elements=elements;
    this->results=results;
    numberOfElement=elements.rows();
    numberOfNode=coordinatesScale.rows();
}

void GLWidget::getViewportInformation(Base3DViewport viewPortSettingObject)
{
    this->viewPortSettingObject=viewPortSettingObject;
}

void GLWidget::getContourSettingInformation(BaseContourSetting contourSettingObject)
{
    this->contourSettingObject=contourSettingObject;
}

void GLWidget::getCuttingPlaneInformation(BaseCuttingPlane cuttingPlaneSettingObject)
{
    this->cuttingPlaneSettingObject=cuttingPlaneSettingObject;
}

void GLWidget::getStepResultInformation(BaseStepResult stepResultObject)
{
    this->stepResultObject=stepResultObject;

    if(this->stepResultObject.autoChangeMaxMin==true)
    {
        this->stepResultObject.maxValue=results.maxCoeff();
        this->stepResultObject.minValue=results.minCoeff();
    }
}

void GLWidget::YpositiveToXZ()
{
    Input::reset();
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;

    camera_Axis.setToIdentity();
    cameraMatrix.setToIdentity();

    cameraMatrix.translate(viewPortSettingObject.xCenter,viewPortSettingObject.yCenter,viewPortSettingObject.zCenter);
    cameraMatrix.rotate(90,QVector3D(1.0f,0.0f,0.0f)); //rotate about X directino
    cameraMatrix.translate(-viewPortSettingObject.xCenter,-viewPortSettingObject.yCenter,-viewPortSettingObject.zCenter);

    camera_Axis.translate(0.8f,-0.9f,0.0f);
    camera_Axis.rotate(90,QVector3D(1.0f,0.0f,0.0f));
    camera_Axis.translate(-0.8f,0.9f,0.0f);
    QOpenGLWidget::update();

}

void GLWidget::YnegativeToXZ()
{

    Input::reset();
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;

    camera_Axis.setToIdentity();
    cameraMatrix.setToIdentity();

    cameraMatrix.translate(viewPortSettingObject.xCenter,viewPortSettingObject.yCenter,viewPortSettingObject.zCenter);
    cameraMatrix.rotate(-90,QVector3D(1.0f,0.0f,0.0f));
    cameraMatrix.translate(-viewPortSettingObject.xCenter,-viewPortSettingObject.yCenter,-viewPortSettingObject.zCenter);

    camera_Axis.translate(0.8f,-0.9f,0.0f);
    camera_Axis.rotate(-90,QVector3D(1.0f,0.0f,0.0f));
    camera_Axis.translate(-0.8f,0.9f,0.0f);
    QOpenGLWidget::update();
}

void GLWidget::ZpositiveToXY()
{
    Input::reset();
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;
    camera_Axis.setToIdentity();
    cameraMatrix.setToIdentity();
    QOpenGLWidget::update();

}

void GLWidget::ZnegativeToXY()
{
    Input::reset();
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;
    camera_Axis.setToIdentity();
    cameraMatrix.setToIdentity();

    cameraMatrix.translate(viewPortSettingObject.xCenter,viewPortSettingObject.yCenter,viewPortSettingObject.zCenter);
    cameraMatrix.rotate(180,QVector3D(0.0f,1.0f,0.0f));
    cameraMatrix.translate(-viewPortSettingObject.xCenter,-viewPortSettingObject.yCenter,-viewPortSettingObject.zCenter);

    camera_Axis.translate(0.8f,-0.9f,0.0f);
    camera_Axis.rotate(180,QVector3D(0.0f,1.0f,0.0f));
    camera_Axis.translate(-0.8f,0.9f,0.0f);

    QOpenGLWidget::update();
}

void GLWidget::XpositiveToYZ()
{
    Input::reset();
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;
    camera_Axis.setToIdentity();
    cameraMatrix.setToIdentity();

    cameraMatrix.translate(viewPortSettingObject.xCenter,viewPortSettingObject.yCenter,viewPortSettingObject.zCenter);
    cameraMatrix.rotate(90,QVector3D(0.0f,1.0f,0.0f));
    cameraMatrix.translate(-viewPortSettingObject.xCenter,-viewPortSettingObject.yCenter,-viewPortSettingObject.zCenter);

    camera_Axis.translate(0.8f,-0.9f,0.0f);
    camera_Axis.rotate(90,QVector3D(0.0f,1.0f,0.0f));
    camera_Axis.translate(-0.8f,0.9f,0.0f);

    QOpenGLWidget::update();

}

void GLWidget::XnegativeToYZ()
{
    Input::reset();
    viewPortSettingObject.xLeft=viewPortSettingObject.xLeft0;
    viewPortSettingObject.xRight=viewPortSettingObject.xRight0;
    viewPortSettingObject.yBot=viewPortSettingObject.yBot0;
    viewPortSettingObject.yTop=viewPortSettingObject.yTop0;
    camera_Axis.setToIdentity();
    cameraMatrix.setToIdentity();

    cameraMatrix.translate(viewPortSettingObject.xCenter,viewPortSettingObject.yCenter,viewPortSettingObject.zCenter);
    cameraMatrix.rotate(-90,QVector3D(0.0f,1.0f,0.0f));
    cameraMatrix.translate(-viewPortSettingObject.xCenter,-viewPortSettingObject.yCenter,-viewPortSettingObject.zCenter);

    camera_Axis.translate(0.8f,-0.9f,0.0f);
    camera_Axis.rotate(-90,QVector3D(0.0f,1.0f,0.0f));
    camera_Axis.translate(-0.8f,0.9f,0.0f);

    QOpenGLWidget::update();

}

void GLWidget::teardownGL()
{

}

void GLWidget::updateWidget()
{
    Input::update();
    updateWheel();
    updateLeftMouse();
    updateRightMouse();

    if(updateCheck==true)
    {
        float aspect;
        aspect=(float)(this->width()/this->height());
        viewPortSettingObject.xRight=viewPortSettingObject.xRight+(viewPortSettingObject.yTop-viewPortSettingObject.yBot)*aspect;
        projectionMatrix.setToIdentity();
        projectionMatrix.ortho(viewPortSettingObject.xLeft,viewPortSettingObject.xRight,viewPortSettingObject.yBot,viewPortSettingObject.yTop,0,0);
        resizeGL(this->width(),this->height());
        QOpenGLWidget::update();
        updateCheck=false;

        viewPortSettingObject.cameraMatrix=cameraMatrix;
        viewPortSettingObject.xLeft0=viewPortSettingObject.xLeft;
        viewPortSettingObject.xRight0=viewPortSettingObject.xRight;
        viewPortSettingObject.yBot0=viewPortSettingObject.yBot;
        viewPortSettingObject.yTop0=viewPortSettingObject.yTop;
        emit sendViewportInformation(viewPortSettingObject);
    }

    if(stepResultObject.animationFlag==true)
    {
        float aspect;
        aspect=(float)(this->width()/this->height());
        viewPortSettingObject.xRight=viewPortSettingObject.xRight+(viewPortSettingObject.yTop-viewPortSettingObject.yBot)*aspect;
        projectionMatrix.setToIdentity();
        projectionMatrix.ortho(viewPortSettingObject.xLeft,viewPortSettingObject.xRight,viewPortSettingObject.yBot,viewPortSettingObject.yTop,0,0);
        resizeGL(this->width(),this->height());
        QOpenGLWidget::update();
    }
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        Input::registerKeyPress(event->key());
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        Input::registerKeyRelease(event->key());
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    Input::registerMousePress(event->button());
    if(event->button()==1)
    {
        QPoint mousePoint=QCursor::pos();
        mousePoint=this->mapFromGlobal(mousePoint);
        QImage image = this->grabFramebuffer();
        QRgb rgb=image.pixel(mousePoint.x(),mousePoint.y());
        redColor=qRed(rgb);
        greenColor=qGreen(rgb);
        blueColor=qBlue(rgb);

        double midValue,inValue;
        midValue=0.5*(stepResultObject.maxValue+stepResultObject.minValue);

        if ((redColor==255 && greenColor==255) && blueColor==255)
        {
            inValue=9999999;
        }
        else if (redColor==0)
        {
            midValue=midValue-(blueColor*(midValue-stepResultObject.maxValue)/255);

        }
        else
        {
            inValue=(redColor*(stepResultObject.minValue-midValue)/255)+midValue;
        }
        emit sendValueAtMousePosition(midValue);
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Input::registerMouseRelease(event->button());
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    wheelScrollDistance=event->delta();
}

void GLWidget::updateWheel()
{
    if(wheelScrollDistance!=0)
    {
        updateCheck=true;
        double sensitive=1.05;
        wheelScrollScaleFactor=wheelScrollDistance/120;

        double length_x=0.5*(-viewPortSettingObject.xLeft+viewPortSettingObject.xRight);
        double length_y=0.5*(-viewPortSettingObject.yBot+viewPortSettingObject.yTop);
        float center_point_x=0.5*(viewPortSettingObject.xLeft+viewPortSettingObject.xRight);
        float center_point_y=0.5*(viewPortSettingObject.yBot+viewPortSettingObject.yTop);

        if(wheelScrollDistance>0){
            wheelScrollScaleFactor=sensitive*wheelScrollDistance/120;
            viewPortSettingObject.xLeft=center_point_x-length_x*wheelScrollScaleFactor;
            viewPortSettingObject.xRight=center_point_x+length_x*wheelScrollScaleFactor;
            viewPortSettingObject.yBot=center_point_y-length_y*wheelScrollScaleFactor;
            viewPortSettingObject.yTop=center_point_y+length_y*wheelScrollScaleFactor;
        }
        else
        {
            wheelScrollScaleFactor=-1/(sensitive*wheelScrollDistance/120);
            viewPortSettingObject.xLeft=center_point_x-length_x*wheelScrollScaleFactor;
            viewPortSettingObject.xRight=center_point_x+length_x*wheelScrollScaleFactor;
            viewPortSettingObject.yBot=center_point_y-length_y*wheelScrollScaleFactor;
            viewPortSettingObject.yTop=center_point_y+length_y*wheelScrollScaleFactor;

        }
    }
    wheelScrollDistance=0;
    wheelScrollScaleFactor=1;
}

void GLWidget::updateLeftMouse()
{
    if (Input::buttonPressed(Qt::LeftButton))
    {
        updateCheck=true;
        float dx=viewPortSettingObject.xRight-viewPortSettingObject.xLeft;
        float dy=viewPortSettingObject.yTop-viewPortSettingObject.yBot;
        float dd=max(dy,dx);
        static const float transSpeed = 0.002*dd; //set transpeed is 5% of dimension

        viewPortSettingObject.xLeft=viewPortSettingObject.xLeft-transSpeed * Input::mouseDelta().x();
        viewPortSettingObject.xRight=viewPortSettingObject.xRight-transSpeed * Input::mouseDelta().x();
        viewPortSettingObject.yBot=viewPortSettingObject.yBot+transSpeed * Input::mouseDelta().y();
        viewPortSettingObject.yTop=viewPortSettingObject.yTop+transSpeed * Input::mouseDelta().y();
    }
}

void GLWidget::updateRightMouse()
{
    if (Input::buttonPressed(Qt::RightButton))
    {
        updateCheck=true;
        static const float rotSpeed   = 0.5f;
        camera_Axis.translate(0.8f,-0.9f,0.0f);
        // Handle rotations

        cameraMatrix.translate(viewPortSettingObject.xCenter,viewPortSettingObject.yCenter,viewPortSettingObject.zCenter);
        cameraMatrix.rotate(rotSpeed * Input::mouseDelta().x(), QVector3D(0.0f,1.0f,0.0f));
        cameraMatrix.rotate(rotSpeed * Input::mouseDelta().y(), QVector3D(1.0f,0.0f,0.0f));

        camera_Axis.rotate(rotSpeed * Input::mouseDelta().x(), QVector3D(0.0f,1.0f,0.0f));
        camera_Axis.rotate(rotSpeed * Input::mouseDelta().y(), QVector3D(1.0f,0.0f,0.0f));

        cameraMatrix.translate(-viewPortSettingObject.xCenter,-viewPortSettingObject.yCenter,-viewPortSettingObject.zCenter);
        camera_Axis.translate(-0.8f,0.9f,0.0f);
    }
}

