#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform sampler2DRect lastTex;
uniform sampler2DRect lastOutput;
uniform float factor;
uniform float colorPhase;

void main(void)
{
	vec4 current = texture2DRect(tex, gl_FragCoord.xy);
	vec4 last = texture2DRect(lastTex, gl_FragCoord.xy);
	vec4 lastOutput = texture2DRect(lastOutput, gl_FragCoord.xy);

	float distance = mix(distance(current, last) / 1.4142, lastOutput.x, factor);

	gl_FragColor = vec4(distance, distance / 2.0, 0, 1.0) * 1.2;
}