
cbuffer Test : register(b0) {
	float3 color;
};

float4 main() : SV_TARGET
{
    return float4(color, 0);
}