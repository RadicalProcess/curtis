attribute vec3 position;
uniform float yTranslate;
uniform float yScale;

void main()
{
    vec3 translated = vec3(position.x, position.y * yScale + yTranslate, position.z);
    gl_Position = vec4(translated, 1.0);
}
