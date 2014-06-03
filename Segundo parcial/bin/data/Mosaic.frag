#version 120
#extension GL_ARB_texture_rectangle : enable

uniform vec2 size;
uniform sampler2DRect tex;
uniform float scale;

void main(void)
{
	vec2 cellSize = vec2(size.x * scale, size.y * scale);
	
	//Position in cell
	float x = mod(gl_FragCoord.x, cellSize.x);
	float y = mod(gl_FragCoord.y, cellSize.y);

	gl_FragColor = texture2DRect(tex, vec2(x / cellSize.x * size.x, y / cellSize.y * size.y)) * 
				   texture2DRect(tex, vec2(int(gl_FragCoord.x / cellSize.x) * cellSize.x, int(gl_FragCoord.y / cellSize.y) * cellSize.y));
}