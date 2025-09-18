uniform float phase;
vec4 pinkColor = vec4(0.99, 0.07, 0.58, 1.0);
vec4 purpleColor = vec4(0.27, 0.41, 0.86, 1.0);

void main()
{
    vec4 position = gl_Vertex;
    float x = position.x;
    float y = position.y;
    float z1 = x * x / 3.0 + y * y / 2.0;
    float z2 = x * x / 3.0 - y * y / 2.0;

    vec4 color = mix(pinkColor, purpleColor, phase);
    gl_FrontColor = color;
    position.z = mix(z1, z2, phase);

    gl_Position = gl_ModelViewProjectionMatrix * position;
}
