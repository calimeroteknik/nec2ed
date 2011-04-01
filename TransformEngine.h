#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include "config.h"

class TransformEngine
{
private:
    double          trStack[TRANSFORM_STACK_SIZE][4][4];
    double          tmpMatrix[4][4];
    int             stackIndex;
    inline void     clearTempMatrix(void);
    void            applyTransformMatrix(void);
public:
    TransformEngine();

    void LoadIdentity();
    void PushMatrix();
    void PopMatrix();
    void RotateX(double angle);
    void RotateY(double angle);
    void RotateZ(double angle);
    void Translate(double x, double y, double z);
    void Scale(double x, double y, double z);
    void TransformVector(double &x, double &y, double &z);
};

#endif // TRANSFORMENGINE_H
