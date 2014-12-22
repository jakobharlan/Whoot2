#version 440

layout(location = 0) in vec3 in_position;

out vec3 out_position;

void  main()
{
	out_position = in_position + vec3(0.01, 0.0, 0.0);
}
