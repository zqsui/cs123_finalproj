#version 400

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;


in vec2 texCoord; // UV texture coordinates of the vertex

out vec2 uv; //UV texture coordinates of the vertex

out vec3 LightIntensity;

uniform vec3 La;		//Ambient light intensity

uniform vec3 Lpos;		// Diffuse light position
uniform vec3 Ld;		// Diffuse light intensity

uniform vec3 Ka;		//Ambient reflectivity
uniform vec3 Kd;		//Diffuse reflectivity


uniform mat4 M_Matrix;
uniform mat4 V_Matrix;
uniform mat4 P_Matrix;

void main()
{
        uv = texCoord;

	//Compute MVP_Matrix;
	mat4 MV_Matrix = V_Matrix * M_Matrix;
	mat3 N_Matrix = mat3( transpose( inverse( MV_Matrix ) ) );
	mat4 MVP_Matrix = P_Matrix * MV_Matrix;

	vec3 tnorm = normalize( N_Matrix * in_Normal );
	vec3 Lposcam = ( V_Matrix * vec4(Lpos, 1.0) ).xyz;
	vec4 eyeCoords = MV_Matrix * vec4( in_Position, 1.0 );
	vec3 s = normalize( Lposcam - eyeCoords.xyz );
	vec3 v = normalize( -eyeCoords.xyz );

	vec3 r = reflect( -s, tnorm );
	vec3 ambient = La * Ka;

	float sDotN = max( dot( s, tnorm), 0.0 );
	vec3 diffuse = Ld * Ka * sDotN;

	vec3 specular = vec3(0.0);
	if( sDotN > 0.0 )
	{
		specular = Ld * Ka * pow( max( dot( r, v ), 0.0 ), 16 );
	}

	//Diffuse shading equation
	LightIntensity = ambient + diffuse + specular;

	gl_Position = MVP_Matrix * vec4(in_Position,1.0);
}
