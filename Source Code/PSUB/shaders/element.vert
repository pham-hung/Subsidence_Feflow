#version 330
layout(location = 4) in vec3 position;
layout(location = 5) in vec3 color;
out vec4 vColor;
out lowp float dotProd;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
uniform vec4 normVector;
uniform vec3 pointVector;

float aCoeff;
float bCoeff;
float cCoeff;
float dCoeff;

void main()
{
  gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position, 1.0);
  vColor = vec4(color,1.0f);

  aCoeff=normVector.x;
  bCoeff=normVector.y;
  cCoeff=normVector.z;

  float dCoeff=-aCoeff*pointVector.x-bCoeff*pointVector.y-cCoeff*pointVector.z;
  dotProd=dot(vec3(position.x,position.y,position.z),vec3(aCoeff,bCoeff,cCoeff))+dCoeff;
}
