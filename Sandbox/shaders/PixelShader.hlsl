
cbuffer Test : register(b0) {
	float3 color;
};

struct PSIn
{
    float3 norm : Normal;
};

float4 main(PSIn In) : SV_TARGET
{
    float shading = max(dot(normalize(In.norm), normalize(float3(0.44, 0.22, 0.87))), 0.2);
    return float4(color * shading, 0);
}