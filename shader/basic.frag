#version 440

layout(location = 0) out vec4 outputColor;

uniform float time;

void main()
{
  float red = mod( (time + (gl_FragCoord.x / 1024.0)), 1.0); 
  float green = mod( (time + (gl_FragCoord.y / 800.0)), 1.0);

  outputColor = vec4( red , green, 0.0, 1.0);
}