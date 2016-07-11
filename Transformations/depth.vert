#version 330

in vec3 in_Position;
in vec3 in_Normal;

//out vec3 position;

void main()
{
	gl_Position = vec4(in_Position,1);

	vec3 position = vec3(0.0, 0.0, 0.0);
}