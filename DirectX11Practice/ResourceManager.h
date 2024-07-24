#pragma once
#include "ResourceBase.h"

class Mesh;
class Material;
class Animation;
class Shader;
class Texture;

class ResourceManager
{
public:
	ResourceManager(ComPtr<ID3D11Device> device);

	void Init();

	template<typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, shared_ptr<T> obj);

	template<typename T>
	shared_ptr<T> Get(const wstring& key);
	
	template<typename T>
	ResourceType GetResourceType();

private:
	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();

private:
	ComPtr<ID3D11Device> _device;

	using KeyObjMap = map<wstring, shared_ptr<ResourceBase>>;
	array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;
};

template<typename T> 
inline shared_ptr<T> ResourceManager::Load(const wstring& key, const wstring& path)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	shared_ptr<T> newObj = make_shared<T>();
	newObj->Load(path);
	keyObjMap[key] = newObj;

	return newObj;
}

template<typename T>
inline bool ResourceManager::Add(const wstring& key, shared_ptr<T> obj)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return false;

	keyObjMap[key] = obj;
	return true;
}

template<typename T>
inline shared_ptr<T> ResourceManager::Get(const wstring& key)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	return nullptr;
}

template<typename T>
inline ResourceType ResourceManager::GetResourceType()
{
	if (::is_same_v<T, Texture>)
		return ResourceType::Texture;
	if (::is_same_v<T, Animation>)
		return ResourceType::Animation;
	if (::is_same_v<T, Material>)
		return ResourceType::Material;
	if (::is_same_v<T, Mesh>)
		return ResourceType::Mesh;
	if (::is_same_v<T, Shader>)
		return ResourceType::Shader;

	assert(false);
	return ResourceType::None;
}
