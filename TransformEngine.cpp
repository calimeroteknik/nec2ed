#include "TransformEngine.h"

#include <QDebug>
#include <math.h>

TransformEngine::TransformEngine()
{
    stackIndex = 0;
    LoadIdentity();
}

void TransformEngine::LoadIdentity()
{
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(i == j) trStack[stackIndex][i][j] = 1.0; else trStack[stackIndex][i][j] = 0.0;
}

inline void TransformEngine::clearTempMatrix()
{
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(i == j) tmpMatrix[i][j] = 1.0; else tmpMatrix[i][j] = 0.0;
}

void TransformEngine::applyTransformMatrix()
{
    double sum, m[4][4];
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            sum  = tmpMatrix[0][j] * trStack[stackIndex][i][0];
            sum += tmpMatrix[1][j] * trStack[stackIndex][i][1];
            sum += tmpMatrix[2][j] * trStack[stackIndex][i][2];
            sum += tmpMatrix[3][j] * trStack[stackIndex][i][3];
            m[i][j] = sum;
        }
    }
    for(int i=0; i<4; i++) for(int j=0; j<4; j++)  trStack[stackIndex][i][j] = m[i][j];
}

void TransformEngine::PushMatrix()
{
    if(stackIndex == TRANSFORM_STACK_SIZE-1) {
        qDebug() << "TransformEngine::PushMatrix - Transformation stack is full!";
        return;
    }

    for(int i=0; i<4; i++) for(int j=0; j<4; j++)  trStack[stackIndex+1][i][j] = trStack[stackIndex][i][j];
    stackIndex++;
}

void TransformEngine::PopMatrix()
{
    if(stackIndex == 0) {
        qDebug() << "TransformEngine::PopMatrix - Transformation stack is empty!";
        return;
    }
    stackIndex--;
}

void TransformEngine::RotateX(double angle)
{
    double sa = sin(angle*M_PI/180.0);
    double ca = cos(angle*M_PI/180.0);

    clearTempMatrix();
    tmpMatrix[1][1] =  ca;
    tmpMatrix[1][2] = -sa;
    tmpMatrix[2][1] =  sa;
    tmpMatrix[2][2] =  ca;
    applyTransformMatrix();
}

void TransformEngine::RotateY(double angle)
{
    double sa = sin(angle*M_PI/180.0);
    double ca = cos(angle*M_PI/180.0);

    clearTempMatrix();
    tmpMatrix[0][0] =  ca;
    tmpMatrix[0][2] =  sa;
    tmpMatrix[2][0] = -sa;
    tmpMatrix[2][2] =  ca;
    applyTransformMatrix();
}

void TransformEngine::RotateZ(double angle)
{
    double sa = sin(angle*M_PI/180.0);
    double ca = cos(angle*M_PI/180.0);

    clearTempMatrix();
    tmpMatrix[0][0] =  ca;
    tmpMatrix[0][1] = -sa;
    tmpMatrix[1][0] =  sa;
    tmpMatrix[1][1] =  ca;
    applyTransformMatrix();
}

void TransformEngine::Translate(double x, double y, double z)
{
    clearTempMatrix();
    tmpMatrix[0][3] = x;
    tmpMatrix[1][3] = y;
    tmpMatrix[2][3] = z;
    applyTransformMatrix();
}

void TransformEngine::Scale(double x, double y, double z)
{
    clearTempMatrix();
    tmpMatrix[0][0] = x;
    tmpMatrix[1][1] = y;
    tmpMatrix[2][2] = z;
    applyTransformMatrix();
}

void TransformEngine::TransformVector(double &x, double &y, double &z)
{
    double _x, _y, _z;

    _x = trStack[stackIndex][0][0]*x + trStack[stackIndex][0][1]*y + trStack[stackIndex][0][2]*z + trStack[stackIndex][0][3];
    _y = trStack[stackIndex][1][0]*x + trStack[stackIndex][1][1]*y + trStack[stackIndex][1][2]*z + trStack[stackIndex][1][3];
    _z = trStack[stackIndex][2][0]*x + trStack[stackIndex][2][1]*y + trStack[stackIndex][2][2]*z + trStack[stackIndex][2][3];

    x = _x; y = _y; z = _z;
}
