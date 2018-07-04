#version 330
in highp vec4 vColor;
out highp vec4 fColor;
in lowp float dotProd;
uniform vec4 normVector;

void main()
{
   fColor = vColor;
   if(dotProd<0&&normVector.w>0){discard;}
}
