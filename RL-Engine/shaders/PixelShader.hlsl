#define MaxLights 4

//constant buffers
cbuffer material : register(b0) {
	float4 colour;
	float smoothness;
	float reflectivity;
};

cbuffer lightData : register(b1) {
	float3 dirColour;

	struct PointData {
		float3 colour;
	} pointData[MaxLights];
}

//resouces
Texture2D tex;
SamplerState Sampler;

//input
struct PSIn {
	float2 tc : TexCoord;
	float3 norm : Normal;
	float3 toCam: toCamera;
	float3 toLight[1 + MaxLights] : toLight;
};

float4 main(PSIn In) : SV_TARGET
{
	//get values
	float4 albedo = colour * tex.Sample(Sampler, In.tc);
	float4 specularTint = albedo * reflectivity;
	albedo *= 1 - reflectivity;

	//diffuse
	float diffuse = dot(normalize(In.norm), normalize(In.toLight[0]));
	diffuse = saturate(diffuse);

	//specular
	float3 halfDir = normalize(In.toLight[0] + In.toCam);
	float specAngle = saturate(dot(halfDir, normalize(In.norm)));
	float specular = pow(specAngle, smoothness * 100);

	//output
	float4 DiffuseFinal;// = albedo * float4(1, 1, 1, 1) * diffuse;
	float4 specFinal = specularTint * float4(1, 1, 1, 1) * specular;

	//point lights
	for (int i = 2; i <= MaxLights; i++) {
		diffuse = dot(normalize(In.norm), normalize(In.toLight[i]));
		diffuse = saturate(diffuse);

		halfDir = normalize(In.toLight[i] + In.toCam);
		specAngle = saturate(dot(halfDir, normalize(In.norm)));
		specular = pow(specAngle, smoothness * 100);

		DiffuseFinal += diffuse;// albedo* float4(pointData[i - 1].colour, 1)* diffuse;
		specFinal += specularTint * float4(pointData[i-1].colour, 1) * specular;
	}

	return DiffuseFinal;// +specFinal;
}