#version 410 core

// Replace the placeholder implementation here...

uniform vec3 color;

out vec4 fragmentColor;

void main()
{
	//fragmentColor = vec4(0.0, 0.5, 0.0, 1.0);
	fragmentColor = vec4(color,1.0);
}
