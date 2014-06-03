#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;

uniform int cellSize;
uniform int radius;

void main(void)
{
	vec2 cellCenter = vec2(cellSize / 2, cellSize / 2) + vec2(int(gl_FragCoord.x / cellSize) * cellSize, int(gl_FragCoord.y / cellSize) * cellSize);

	float dist = distance(gl_FragCoord.xy, cellCenter);
	if(dist <= radius){
		if(abs(dist - radius) <= 1.5){
			gl_FragColor = mix(vec4(0.0, 0.5, 1, 1), texture2DRect(tex, cellCenter), 0.8);
			//gl_FragColor = vec4(1);
		} else {
			gl_FragColor = texture2DRect(tex, cellCenter) * 1.5;
		}
	} else {		
		gl_FragColor = vec4(0, 0, 0, 1);
	}
}