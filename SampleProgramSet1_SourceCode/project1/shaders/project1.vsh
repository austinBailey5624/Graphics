#version 410 core

// replace the placeholder implementation here

in vec2 MC;
uniform vec4 scaleTrans;
void main()
{
	float ldsx = scaleTrans[0]*MC[0] + scaleTrans[1];
	float ldsy = scaleTrans[2]*MC[1] + scaleTrans[3];
	gl_Position = vec4(ldsx, ldsy, 0, 1);
}
