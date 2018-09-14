#version 410 core
#define NR_POINT_LIGHTS 1

// Material
struct Material {
    sampler2D diffuseMap1;
    sampler2D diffuseMap2;
    sampler2D diffuseMap3;
    sampler2D specularMap1;
    sampler2D specularMap2;
    sampler2D emissionMap;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
    bool hasDiffMap;
    bool hasSpecMap;
    bool hasEmissionMap;
};
// Directional light
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
};
// Point light
struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    float constant;
    float linear;
    float quadratic;
};
// Spotlight
struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    float innerCone;
    float outerCone;
    float constant;
    float linear;
    float quadratic;
};

// Uniforms
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 camPos;
uniform float time;

// From vertex shader
in vec3 Pos;
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

// Fragment color
out vec4 FragColor;

// Function declarations
vec3 calcDirLight(DirLight light, vec3 normal, vec3 camDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 camDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 camDir);
vec3 calcEmission();

void main()
{
    vec3 color = vec3(0.0);
    vec3 normal = normalize(Normal);
    vec3 camDir = normalize(camPos - FragPos);

//    color += calcDirLight(dirLight, normal, camDir);
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        color += calcPointLight(pointLights[i], normal, camDir);
    color += calcSpotLight(spotLight, normal, camDir);
//    color += calcEmission();

    FragColor = vec4(color, 1.0);
}

//---------------------------------------------------------------------------------
// Function definitions
//---------------------------------------------------------------------------------

vec3 calcDirLight(DirLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse
    float diffStr = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStr = pow(max(dot(camDir, reflectDir), 0.0), material.shininess);
    // Result
    vec3 amb, diff, spec;
    if (material.hasDiffMap) {
        amb = light.ambient * texture(material.diffuseMap1, UV).rgb;
        diff = light.diffuse * diffStr * texture(material.diffuseMap1, UV).rgb;
    } else {
        amb = light.ambient * material.diffuseColor;
        diff = light.diffuse * diffStr * material.diffuseColor;
    }
    if (material.hasSpecMap) {
        spec = light.diffuse * specStr * texture(material.specularMap1, UV).rgb;
    } else {
        spec = light.diffuse * specStr * material.specularColor;
    }
    return (amb + diff + spec);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    // Diffuse
    float diffStr = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStr = pow(max(dot(reflectDir, camDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Result
    vec3 amb, diff, spec;
    if (material.hasDiffMap) {
        amb = light.ambient * texture(material.diffuseMap1, UV).rgb;
        diff = light.diffuse * diffStr * texture(material.diffuseMap1, UV).rgb;
    } else {
        amb = light.ambient * material.diffuseColor;
        diff = light.diffuse * diffStr * material.diffuseColor;
    }
    if (material.hasSpecMap) {
        spec = light.diffuse * specStr * texture(material.specularMap1, UV).rgb;
    } else {
        spec = light.diffuse * specStr * material.specularColor;
    }
    amb *= attenuation;
    diff *= attenuation;
    spec *= attenuation;
    return (amb + diff + spec);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    // Diffuse
    float diffStr = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStr = pow(max(dot(reflectDir, camDir), 0.0) , material.shininess);
    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float intensity = clamp((theta - light.outerCone) / (light.innerCone - light.outerCone), 0.0, 1.0);
    // Result
    vec3 amb, diff, spec;
    if (material.hasDiffMap) {
        amb = light.ambient * texture(material.diffuseMap1, UV).rgb;
        diff = light.diffuse * diffStr * texture(material.diffuseMap1, UV).rgb;
    } else {
        amb = light.ambient * material.diffuseColor;
        diff = light.diffuse * diffStr * material.diffuseColor;
    }
    if (material.hasSpecMap) {
        spec = light.diffuse * specStr * texture(material.specularMap1, UV).rgb;
    } else {
        spec = light.diffuse * specStr * material.specularColor;
    }
    amb *= attenuation * intensity;
    diff *= attenuation * intensity;
    spec *= attenuation * intensity;
    return (amb + diff + spec);
}

vec3 calcEmission()
{
    if(material.hasEmissionMap)
        return texture(material.emissionMap, UV).rgb;
    else
        return vec3(0);
}
