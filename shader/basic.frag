  #version 440

  layout(location = 0) out vec4 outputColor;
  
  uniform float time;

  void main()
  {
     outputColor = vec4(mod(time,1.0), mod(time+0.333,1.0), mod(time+0.666,1.0), 1.0f);
  }