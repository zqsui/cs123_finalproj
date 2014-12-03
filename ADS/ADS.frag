#version 400

in vec2 uv;
in vec3 LightIntensity;

uniform sampler2D textureSampler;

layout ( location = 0) out vec4 FragColor;

void main()
{
    vec4 texColor = texture2D(textureSampler, uv);

    FragColor = texColor;
    //FragColor = vec4(LightIntensity, 1.0);
}
