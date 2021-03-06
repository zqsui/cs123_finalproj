#version 400

in vec2 uv;
in vec3 LightIntensity;
in vec3 Ld_out;
in vec3 Ka_out;
in vec3 s_out;
in vec3 diffuse_out;

uniform sampler2D textureSampler;
uniform sampler2D normalSampler;

uniform int isBumpMapping;


layout ( location = 0) out vec4 FragColor;

void main()
{
    vec4 texColor = texture2D(textureSampler, uv);

    //texture2D(normalSampler, uv);

 //   if(isBumpMapping)
    vec3 tnorm = normalize(texture2D(normalSampler, uv).rgb * 2.0 - 1.0);
    float sDotN = max( dot( s_out, tnorm), 0.0 );
    vec3 diffuse;

    if(isBumpMapping == 1)
        diffuse = Ld_out * Ka_out * sDotN;
    else
        diffuse = diffuse_out;

    //FragColor = texColor;
    float blend = 0.5;
    vec4 blend_diffuse = (1 - blend) * texColor + vec4(diffuse, 1.0) * blend;
    FragColor = vec4(LightIntensity, 1.0) + blend_diffuse; //vec4(diffuse, 1.0);

    //FragColor = vec4(LightIntensity, 1.0);//* blend + (1 - blend) * texColor;
    //FragColor = texColor;
}
