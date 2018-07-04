#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QDebug>
#include <iostream>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector4D>
#include <QOpenGLVertexArrayObject>
#include <vector>
#include <QFileDialog>
#include <QObject>
#include <QOpenGLWidget>
#include <QString>
#include <QFont>
#include "OpenGLCLass/input.h"
#include <QWheelEvent>
#include <QMessageBox>
#include <QElapsedTimer>
#include <Eigen/Dense>
#include <QDate>
#include <QPoint>
#include <QCursor>
#include <QPixmap>
#include <QRgb>
#include <QTimer>
#include "input.h"

//Base class
#include "BasedClass/basecontoursetting.h" //contour setting
#include "BasedClass/basecuttingplane.h"   //Cutting plane
#include "BasedClass/basescaleclass.h"     //xscale (x, y, z, deformation)
#include "BasedClass/basestepresult.h"     //minVal, maxVal
#include "BasedClass/base3dviewport.h"

using namespace std;
using namespace Eigen;

class GLWidget:public QOpenGLWidget, protected QOpenGLFunctions
{
     Q_OBJECT
public:
   //Default constructor
    GLWidget();  
    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);

    //Prepare and visual each element
    void prepareData(); //general data
    void nodeData(); //for plot nodes
    void initializeNode();
    void paintNode();

    void prismElementData();
    void initializePrismElement();
    void paintPrismElement();

    void prismLineDeformData();
    void initializePrismLineDeform();
    void paintPrismLineDeform();

    void prismLineData();
    void initializePrismLine();
    void paintPrismLine();

    void axisData();
    void initializeAxis();
    void paintAxis();

    //Supported function
    void calculateRGB_Color(double minValue, double maxValue, double inputValue); //results is float red, green, blue;
    void pauseSystem(); //for Debugging
    void forceToUpdateWiget(); //force to update OpenGL widget

public slots:
    void getShownData(Ref<MatrixXd> coordinatesScale, Ref<MatrixXd> coordinatesDeform, Ref<MatrixXd> elements, Ref<MatrixXd> results);
    void getViewportInformation(Base3DViewport viewPortSettingObject);
    void getContourSettingInformation(BaseContourSetting contourSettingObject);
    void getCuttingPlaneInformation(BaseCuttingPlane cuttingPlaneSettingObject);
    void getStepResultInformation(BaseStepResult stepResultObject);
    //Get Information from Main Window

    //view Functions
    void YpositiveToXZ(); //View from Z to XY plane
    void YnegativeToXZ(); //Z to XY plane
    void ZpositiveToXY(); //Y to XZ plane
    void ZnegativeToXY(); //Y to XZ plane
    void XpositiveToYZ();  //X to YZ plane
    void XnegativeToYZ(); //X to YZ plane

signals:
    //Send signals to MainWindow
    void sendSignalToMainWindow();
    void sendValueAtMousePosition(double mouseValue);
    void sendViewportInformation(Base3DViewport viewPortSettingObject);

    //finish PAll Paint
    void finishGL_Paint();

protected slots:
    void teardownGL();    
    void updateWidget();

protected:    
    //To handle left, right, middle mouse buttons
    //All input information are handled by class Input
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    //Function
    void updateWheel();
    void updateLeftMouse();
    void updateRightMouse();

    //Setting object, get information from mainWindow Class
    BaseContourSetting contourSettingObject;
    BaseCuttingPlane cuttingPlaneSettingObject;
    BaseScaleClass scaleSettingObject;
    BaseStepResult stepResultObject;
    Base3DViewport viewPortSettingObject;

    //Standard OpenGL vars
    //Color Buffer    
    QOpenGLBuffer ColorBuffer_Element;
    QOpenGLBuffer ColorBuffer_Axis;

    //Vertex Buffer
    QOpenGLBuffer VertexBuffer_Node;
    QOpenGLBuffer VertexBuffer_Line;
    QOpenGLBuffer VertexBuffer_LineDeform;
    QOpenGLBuffer VertexBuffer_Element;
    QOpenGLBuffer VertexBuffer_Axis;

    //Vertex Array Buffer
    QOpenGLVertexArrayObject VertexArray_Node;
    QOpenGLVertexArrayObject VertexArray_Line;
    QOpenGLVertexArrayObject VertexArray_LineDeform;
    QOpenGLVertexArrayObject VertexArray_Element;
    QOpenGLVertexArrayObject VertexArray_Axis;

    //Vertex Array shader
    QOpenGLShaderProgram *ShaderProgram_Node;
    QOpenGLShaderProgram *ShaderProgram_Line;
    QOpenGLShaderProgram *ShaderProgram_LineDeform;
    QOpenGLShaderProgram *ShaderProgram_Element;
    QOpenGLShaderProgram *ShaderProgram_Axis;

    //Uniform location (used in shader file)
    int modelToWorld_Node;
    int modelToWorld_Line;
    int modelToWorld_Element;
    int modelToWorld_Axis;

    int worldToCamera_Node;
    int worldToCamera_Line;
    int worldToCamera_Element;
    int worldToCamera_Axis;


    int cameraToView_Node;
    int cameraToView_Line;
    int cameraToView_Element;
    int cameraToView_Axis;

    int normVector_Node;
    int normVector_Line;
    int normVector_LineDeform;
    int normVector_Element;

    int normPoint_Node;
    int normPoint_Line;
    int normPoint_LineDeform;
    int normPoint_Element;

    //matrix for projection
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 cameraMatrix;
    QMatrix4x4 cameraMatrix_Initial;
    QMatrix4x4 transformMatrix;

    QMatrix4x4 camera_Axis;
    QMatrix4x4 projection_Axis;

    QVector4D normVector;
    QVector3D pointVector;

    //Data matrix
    MatrixXd coordinatesDeform, coordinatesScale;  //coordinatesScale uses for nodes, element line, element; coordinatesDeform is used for results
    MatrixXd elements;
    MatrixXd results; //Results contain data to shown
    int numberOfNode, numberOfElement;

    //Vector for OpenGL
    vector <Vector3f> Vector_Node;
    vector <Vector3f> Vector_NodeColor;

    vector <Vector3f> Vector_Line;
    vector <Vector3f> Vector_LineColor;

    vector <Vector3f> Vector_LineDeform;

    vector <Vector3f> Vector_Element;
    vector <Vector3f> Vector_ElementColor;

    vector <Vector3f> Vector_Axis;
    vector <Vector3f> Vector_AxisColor;
    vector <Vector2i> Vector_AxisIndex;

    //For display with QPainter
    QString myText;
    QFont myFont;

    //Timer, to update OpenGLWiget
    QTimer *myTimer = new QTimer;

    //General variables for general purpose
    float redColor, greenColor, blueColor;
    float wheelScrollScaleFactor=1;
    int wheelScrollDistance;
    int buttonDragDistance;
    bool updateCheck;
};

#endif // GLWIDGET_H
