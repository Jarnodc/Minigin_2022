#include "MiniginPCH.h"
#include "JsonReader.h"
#include <fstream>

#include "BoxCollider.h"
#include "GameObject.h"
#include "document.h"
#include <istreamwrapper.h>


void JsonReader::ReadFile(dae::Scene& scene,const std::string& path)
{
	if (std::ifstream is{ path })
	{
		assert(is);
		rapidjson::IStreamWrapper isw{ is };

		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		const rapidjson::Value& valName = jsonDoc["Colliders"];
		for (const auto& p : valName.GetArray())
		{
			const auto tag = p["Object"].GetString();
			const auto dimensions = p["Dimensions"].GetArray();
			SDL_Rect col{};
			for (int i = 0; i < static_cast<int>(dimensions.Size()); ++i)
			{
				switch (i)
				{
				case 0:
					col.x = dimensions[i].GetInt() * 2 + 112;
					break;
				case 1:
					col.y = dimensions[i].GetInt() * 2 + 40;
					break;
				case 2:
					col.w = dimensions[i].GetInt() * 2;
					break;
				case 3:
					col.h = dimensions[i].GetInt() * 2;
					break;
				default:
					std::cout << "out of range" << std::endl;
					break;
				}
			}
			const auto obj = std::make_shared<dae::GameObject>(tag);
			obj->AddComponent(new BoxCollider(obj.get(), col));
			scene.Add(obj);
		}
	}
}
