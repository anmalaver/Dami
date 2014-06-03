#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform sampler2DRect lastTex;
uniform float factor;

void main(void)
{
	vec4 current = texture2DRect(tex, gl_FragCoord.xy);
	vec4 last = texture2DRect(lastTex, gl_FragCoord.xy);

	vec4 result = mix(current, last, factor);
	result.a = 1.0;

	gl_FragColor = result;
}