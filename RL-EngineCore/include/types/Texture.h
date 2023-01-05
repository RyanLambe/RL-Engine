#pragma once

#include <d3d11.h>
#include <string>
#include <vector>
#include <map>

//external
//https://lodev.org/lodepng/
#include "../../External/LodePng/lodepng.h"

#include "../Debug.h"
#include "SmartPtr.h"

class Texture {
public:

	void Set(std::string fileName);
	void Update(ID3D11Device* device, ID3D11DeviceContext* context);
	int getId();
	float* getAverage();

private:

	float avColour[3] = { 0, 0, 0 };

	std::string name;

	static int nextId;
	static std::map<std::string, int> idMap;

	SmartPtr<ID3D11Texture2D> texture2D;
	SmartPtr<ID3D11ShaderResourceView> texView;

};