#version 330 core

in vec3 Normal;
in vec3 fragPos;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 passColor;
		
void main()
{
   float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * lightColor;

   vec3 normalVector = normalize(Normal);
   vec3 lightDir = normalize(lightPos - fragPos);
   float diffuseLight = max(dot(normalVector, lightDir), 0.0);

   vec3 diffuse = diffuseLight * lightColor;

   float specularStrength = 0.5;

   vec3 viewDir = normalize(viewPos + fragPos);
   vec3 reflectDir = reflect(-lightDir, normalVector);

   float specularLight = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * specularLight * lightColor;

   vec3 result = (ambient + diffuse + specular) * passColor;
   
   color = vec4(result, 1.0);
}