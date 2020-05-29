#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

uniform bool useDiffuseMap;
uniform bool useSpecularMap;

void main()
{
	vec3 objectColor = (!useDiffuseMap) ? vec3(0.5f, 0.5f, 0.5f) : vec3(texture(diffuseMap, TexCoord));
	
	float dist = distance(FragPos, lightPos);

	//Ambient Light
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	//Diffused Light
	vec3 norm = normalize(Normal);
	vec3 lightdir = normalize(lightPos-FragPos);
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = diff * lightColor / (dist*0.2);

	//Specular Light
	float specularStrength = 0.5;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightdir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specular = specularStrength * spec * lightColor;  
	if(useSpecularMap)
		specular *= vec3(texture(specularMap, TexCoord));

	vec3 result = (ambient + diffuse + specular) * objectColor;

	color = vec4(result, 1.0f);
};