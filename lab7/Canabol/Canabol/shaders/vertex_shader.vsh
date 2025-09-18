vec4 blueColor = vec4(0.0, 0.0, 1.0, 1.0); 
vec4 greenColor = vec4(0.0, 1.0, 0.0, 1.0);

float getCanabolaCoef(float x)
{
	return (1 + sin(x)) * (1 + 0.9 * cos(8 * x)) * (1 + 0.1 * cos(24 * x)) * (0,5 + 0.3 * cos(140 * x));
}
//задать цвет от синего к зеленому
void main()
{
	vec4 position = gl_Vertex;
	float canabolaCoef = getCanabolaCoef(position.x);
	
	vec4 color = mix(blueColor, greenColor, canabolaCoef * 0.05);
	
	position.y = canabolaCoef * sin(position.x);
	position.x = canabolaCoef * cos(position.x);
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * position;
	gl_FrontColor = color;
}
