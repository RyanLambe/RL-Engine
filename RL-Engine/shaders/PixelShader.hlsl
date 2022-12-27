#define MaxLights 4

//constant buffers
cbuffer material : register(b0) {
	float4 colour;
	float smoothness;
	float reflectivity;
	int glow;
	int texId;
};

cbuffer lightData : register(b1) {
	float3 dirColour;

	struct PointData {
		float3 colour;
		float power;
		float range;
	} pointData[MaxLights];

    float4 ambientLight;
}

//resouces
Texture2D tex[128] : register(t0);
SamplerState Sampler;

//input
struct PSIn {
	float2 tc : TexCoord;
	float3 norm : Normal;
	float3 toCam: toCamera;
	float3 toLight[1 + MaxLights] : toLight;
};

float4 sampleTexture(PSIn In, int id);

float4 getPointDiffuse(PSIn In, float4 albedo, int index) {

	//diffuse
	float diffuse = dot(normalize(In.norm), normalize(In.toLight[index + 1]));
	
	//attenuation 
	float distanceSqr = max(dot(In.toLight[index + 1], In.toLight[index + 1]), 0.00001);
	//range = max(0, 1-(d^2/r^2))^2
	float range = pow(saturate(1 - pow(distanceSqr * (1 / max(pointData[index].range * pointData[index].range, 0.00001f)), 2)), 2);

	//return
	float4 Out = albedo;
	Out *= float4(pointData[index].colour, 1);
	Out *= diffuse;
	Out *= pointData[index].power;
	Out *= range;
	return Out;
}

float4 getPointSpecular(PSIn In, float4 specularTint, int index) {

	//calculate
	float3 halfDir = normalize(In.toLight[index + 1] + In.toCam);
	float specAngle = saturate(dot(halfDir, normalize(In.norm)));
	float specular = pow(specAngle, smoothness * 100);

	//attenuation
	float distanceSqr = max(dot(In.toLight[index + 1], In.toLight[index + 1]), 0.00001);
	//range = max(0, 1-(d^2/r^2))^2
	float range = pow(saturate(1 - pow(distanceSqr * (1 / max(pointData[index].range * pointData[index].range, 0.00001f)), 2)), 2);
	
	//return
	float4 Out = specularTint;
	Out *= float4(pointData[index].colour, 1);
	Out *= specular;
	Out *= pointData[index].power;
	Out *= range;
	return Out;
}

float4 main(PSIn In) : SV_TARGET
{
    //get values
    //float3 texCoord = float3(In.tc.x, In.tc.y, 0);
    float4 albedo = colour * sampleTexture(In, texId);
	float4 specularTint = albedo * reflectivity;
	albedo *= 1 - reflectivity;

	if (glow == 1)
		return albedo;

	//directional light
	float diffuse = dot(normalize(In.norm), normalize(In.toLight[0]));
	diffuse = saturate(diffuse);

	float3 halfDir = normalize(In.toLight[0] + In.toCam);
	float specAngle = saturate(dot(halfDir, normalize(In.norm)));
	float specular = pow(specAngle, smoothness * 100);

	//Create Diffuse/Specular
	float4 DiffuseFinal =  albedo * float4(dirColour, 1) * diffuse;
	float4 specFinal = specularTint * float4(dirColour, 1) * specular;

	//point lights
	for (int i = 0; i < MaxLights; i++) {
		DiffuseFinal += getPointDiffuse(In, albedo, i);
		specFinal += getPointSpecular(In, specularTint, i);
	}

    return max(DiffuseFinal + specFinal, ambientLight);
}

//unable to load on draw or load all textures into Texture Array
//this is the best option as i am not using directx 12
float4 sampleTexture(PSIn In, int id) {
	switch (id) {
    case 0:
        return tex[0].Sample(Sampler, In.tc);
    case 1:
        return tex[1].Sample(Sampler, In.tc);
    case 2:
        return tex[2].Sample(Sampler, In.tc);
    case 3:
        return tex[3].Sample(Sampler, In.tc);
    case 4:
        return tex[4].Sample(Sampler, In.tc);
    case 5:
        return tex[5].Sample(Sampler, In.tc);
    case 6:
        return tex[6].Sample(Sampler, In.tc);
    case 7:
        return tex[7].Sample(Sampler, In.tc);
    case 8:
        return tex[8].Sample(Sampler, In.tc);
    case 9:
        return tex[9].Sample(Sampler, In.tc);
    case 10:
        return tex[10].Sample(Sampler, In.tc);
    case 11:
        return tex[11].Sample(Sampler, In.tc);
    case 12:
        return tex[12].Sample(Sampler, In.tc);
    case 13:
        return tex[13].Sample(Sampler, In.tc);
    case 14:
        return tex[14].Sample(Sampler, In.tc);
    case 15:
        return tex[15].Sample(Sampler, In.tc);
    case 16:
        return tex[16].Sample(Sampler, In.tc);
    case 17:
        return tex[17].Sample(Sampler, In.tc);
    case 18:
        return tex[18].Sample(Sampler, In.tc);
    case 19:
        return tex[19].Sample(Sampler, In.tc);
    case 20:
        return tex[20].Sample(Sampler, In.tc);
    case 21:
        return tex[21].Sample(Sampler, In.tc);
    case 22:
        return tex[22].Sample(Sampler, In.tc);
    case 23:
        return tex[23].Sample(Sampler, In.tc);
    case 24:
        return tex[24].Sample(Sampler, In.tc);
    case 25:
        return tex[25].Sample(Sampler, In.tc);
    case 26:
        return tex[26].Sample(Sampler, In.tc);
    case 27:
        return tex[27].Sample(Sampler, In.tc);
    case 28:
        return tex[28].Sample(Sampler, In.tc);
    case 29:
        return tex[29].Sample(Sampler, In.tc);
    case 30:
        return tex[30].Sample(Sampler, In.tc);
    case 31:
        return tex[31].Sample(Sampler, In.tc);
    case 32:
        return tex[32].Sample(Sampler, In.tc);
    case 33:
        return tex[33].Sample(Sampler, In.tc);
    case 34:
        return tex[34].Sample(Sampler, In.tc);
    case 35:
        return tex[35].Sample(Sampler, In.tc);
    case 36:
        return tex[36].Sample(Sampler, In.tc);
    case 37:
        return tex[37].Sample(Sampler, In.tc);
    case 38:
        return tex[38].Sample(Sampler, In.tc);
    case 39:
        return tex[39].Sample(Sampler, In.tc);
    case 40:
        return tex[40].Sample(Sampler, In.tc);
    case 41:
        return tex[41].Sample(Sampler, In.tc);
    case 42:
        return tex[42].Sample(Sampler, In.tc);
    case 43:
        return tex[43].Sample(Sampler, In.tc);
    case 44:
        return tex[44].Sample(Sampler, In.tc);
    case 45:
        return tex[45].Sample(Sampler, In.tc);
    case 46:
        return tex[46].Sample(Sampler, In.tc);
    case 47:
        return tex[47].Sample(Sampler, In.tc);
    case 48:
        return tex[48].Sample(Sampler, In.tc);
    case 49:
        return tex[49].Sample(Sampler, In.tc);
    case 50:
        return tex[50].Sample(Sampler, In.tc);
    case 51:
        return tex[51].Sample(Sampler, In.tc);
    case 52:
        return tex[52].Sample(Sampler, In.tc);
    case 53:
        return tex[53].Sample(Sampler, In.tc);
    case 54:
        return tex[54].Sample(Sampler, In.tc);
    case 55:
        return tex[55].Sample(Sampler, In.tc);
    case 56:
        return tex[56].Sample(Sampler, In.tc);
    case 57:
        return tex[57].Sample(Sampler, In.tc);
    case 58:
        return tex[58].Sample(Sampler, In.tc);
    case 59:
        return tex[59].Sample(Sampler, In.tc);
    case 60:
        return tex[60].Sample(Sampler, In.tc);
    case 61:
        return tex[61].Sample(Sampler, In.tc);
    case 62:
        return tex[62].Sample(Sampler, In.tc);
    case 63:
        return tex[63].Sample(Sampler, In.tc);
    case 64:
        return tex[64].Sample(Sampler, In.tc);
    case 65:
        return tex[65].Sample(Sampler, In.tc);
    case 66:
        return tex[66].Sample(Sampler, In.tc);
    case 67:
        return tex[67].Sample(Sampler, In.tc);
    case 68:
        return tex[68].Sample(Sampler, In.tc);
    case 69:
        return tex[69].Sample(Sampler, In.tc);
    case 70:
        return tex[70].Sample(Sampler, In.tc);
    case 71:
        return tex[71].Sample(Sampler, In.tc);
    case 72:
        return tex[72].Sample(Sampler, In.tc);
    case 73:
        return tex[73].Sample(Sampler, In.tc);
    case 74:
        return tex[74].Sample(Sampler, In.tc);
    case 75:
        return tex[75].Sample(Sampler, In.tc);
    case 76:
        return tex[76].Sample(Sampler, In.tc);
    case 77:
        return tex[77].Sample(Sampler, In.tc);
    case 78:
        return tex[78].Sample(Sampler, In.tc);
    case 79:
        return tex[79].Sample(Sampler, In.tc);
    case 80:
        return tex[80].Sample(Sampler, In.tc);
    case 81:
        return tex[81].Sample(Sampler, In.tc);
    case 82:
        return tex[82].Sample(Sampler, In.tc);
    case 83:
        return tex[83].Sample(Sampler, In.tc);
    case 84:
        return tex[84].Sample(Sampler, In.tc);
    case 85:
        return tex[85].Sample(Sampler, In.tc);
    case 86:
        return tex[86].Sample(Sampler, In.tc);
    case 87:
        return tex[87].Sample(Sampler, In.tc);
    case 88:
        return tex[88].Sample(Sampler, In.tc);
    case 89:
        return tex[89].Sample(Sampler, In.tc);
    case 90:
        return tex[90].Sample(Sampler, In.tc);
    case 91:
        return tex[91].Sample(Sampler, In.tc);
    case 92:
        return tex[92].Sample(Sampler, In.tc);
    case 93:
        return tex[93].Sample(Sampler, In.tc);
    case 94:
        return tex[94].Sample(Sampler, In.tc);
    case 95:
        return tex[95].Sample(Sampler, In.tc);
    case 96:
        return tex[96].Sample(Sampler, In.tc);
    case 97:
        return tex[97].Sample(Sampler, In.tc);
    case 98:
        return tex[98].Sample(Sampler, In.tc);
    case 99:
        return tex[99].Sample(Sampler, In.tc);
    case 100:
        return tex[100].Sample(Sampler, In.tc);
    case 101:
        return tex[101].Sample(Sampler, In.tc);
    case 102:
        return tex[102].Sample(Sampler, In.tc);
    case 103:
        return tex[103].Sample(Sampler, In.tc);
    case 104:
        return tex[104].Sample(Sampler, In.tc);
    case 105:
        return tex[105].Sample(Sampler, In.tc);
    case 106:
        return tex[106].Sample(Sampler, In.tc);
    case 107:
        return tex[107].Sample(Sampler, In.tc);
    case 108:
        return tex[108].Sample(Sampler, In.tc);
    case 109:
        return tex[109].Sample(Sampler, In.tc);
    case 110:
        return tex[110].Sample(Sampler, In.tc);
    case 111:
        return tex[111].Sample(Sampler, In.tc);
    case 112:
        return tex[112].Sample(Sampler, In.tc);
    case 113:
        return tex[113].Sample(Sampler, In.tc);
    case 114:
        return tex[114].Sample(Sampler, In.tc);
    case 115:
        return tex[115].Sample(Sampler, In.tc);
    case 116:
        return tex[116].Sample(Sampler, In.tc);
    case 117:
        return tex[117].Sample(Sampler, In.tc);
    case 118:
        return tex[118].Sample(Sampler, In.tc);
    case 119:
        return tex[119].Sample(Sampler, In.tc);
    case 120:
        return tex[120].Sample(Sampler, In.tc);
    case 121:
        return tex[121].Sample(Sampler, In.tc);
    case 122:
        return tex[122].Sample(Sampler, In.tc);
    case 123:
        return tex[123].Sample(Sampler, In.tc);
    case 124:
        return tex[124].Sample(Sampler, In.tc);
    case 125:
        return tex[125].Sample(Sampler, In.tc);
    case 126:
        return tex[126].Sample(Sampler, In.tc);
    case 127:
        return tex[127].Sample(Sampler, In.tc);
	default:
		return tex[0].Sample(Sampler, In.tc);
	}
}