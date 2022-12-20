
//constant buffers
cbuffer material : register(b0) {
	float4 colour;
};

cbuffer lightData : register(b1) {
	float3 dirColour;

	struct PointData {
		float3 colour;
	} pointData[4];
}

//resouces
Texture2D tex;
SamplerState Sampler;


float4 main( float2 tc : TexCoord, float3 norm : Normal, float3 toLight[5] : toLight, float3 lightColour[5] : lightColour) : SV_TARGET
{

	float intensity = dot(normalize(norm), normalize(toLight[0]));
	intensity = max(0.0f, intensity);

	return mul(intensity, colour);
}