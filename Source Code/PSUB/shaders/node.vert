#version 330
layout(location = 0) in vec3 position;
out vec4 vColor;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

float gl_PointSize;
void main()
{
    gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position, 1.0);
    vColor = vec4(0.0f,0.0f,0.0f,0.5f);
    gl_PointSize=1.5;
}
