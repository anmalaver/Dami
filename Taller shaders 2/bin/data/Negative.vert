#version 120

void main(void)
{
	vec4 vertex = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}