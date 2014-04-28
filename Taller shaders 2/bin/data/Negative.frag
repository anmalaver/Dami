#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;

void main(void)
{
	vec4 color = texture2DRect(tex, gl_FragCoord.xy);	
	gl_FragColor = vec4(vec3(1) - color.xyz, 1.0);
}