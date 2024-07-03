#pragma once

struct VertexTextureData
{
	Vec3 position = Vec3::Zero;
	Vec2 uv = Vec2::Zero;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexColorData 
{
	Vec3 position = Vec3::Zero;
	Color color = {0, 0, 0, 0};

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

