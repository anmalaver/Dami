#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform float rWeight;
uniform float gWeight;
uniform float bWeight;
uniform float power;

void main(void)
{
	vec4 color = texture2DRect(tex, gl_FragCoord.xy);
	float mean = (color.r * rWeight + color.g * gWeight + color.b * bWeight) / (rWeight + gWeight + bWeight);
	mean = pow(mean, power);
	gl_FragColor = vec4(mean, mean, mean, 1.0);
}