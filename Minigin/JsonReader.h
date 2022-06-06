#pragma once
#include "Scene.h"
#include "Singleton.h"
class JsonReader final: public dae::Singleton<JsonReader>
{
public:
	~JsonReader() override = default;

	JsonReader(const JsonReader& other) = delete;
	JsonReader(JsonReader&& other) noexcept = delete;
	JsonReader& operator=(const JsonReader& other) = delete;
	JsonReader& operator=(JsonReader&& other) noexcept = delete;

	void ReadFile(dae::Scene& scene, const std::string& path);

private:
	friend class Singleton<JsonReader>;
	JsonReader() = default;
};

