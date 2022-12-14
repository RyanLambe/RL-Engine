cbuffer CBuf {
	float4 color;
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
	return color;
}