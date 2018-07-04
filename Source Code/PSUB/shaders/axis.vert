#version 330
layout(location = 6) in vec3 position;
layout(location = 7) in vec3 color;
out vec4 vColor;
float gl_PointSize;

uniform mat4 axis_modelToWorld;
uniform mat4 axis_worldToCamera;
uniform mat4 axis_cameraToView;

void main()
{
    gl_Position = axis_cameraToView*axis_worldToCamera * vec4(position, 1.0);
    vColor = vec4(color,1.0f);
    gl_PointSize=5;
}
