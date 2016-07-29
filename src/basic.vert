#version 430
in vec3 VertexPosition;
out vec3 Color;
void main()
{
	Color = vec3(0.0, 1.0, 0.0);
	gl_Position = vec4( VertexPosition, 1.0 );
}