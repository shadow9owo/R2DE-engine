#include "exportUtils.hpp"
#include "../../data.hpp"
#include "../json.hpp"
#include <fstream>
#include "../../types.hpp"
#include <memory>

namespace projecthandling
{
    namespace json
    {
        bool exporttofile(const Types::Project& project, std::string path)
        {
            try
            {
                nlohmann::json j;
                j["objects"] = nlohmann::json::array();

                for (const auto& obj : project.objects)
                {
                    nlohmann::json jobj;
                    jobj["position"]["x"] = obj->position.x;
                    jobj["position"]["y"] = obj->position.y;
                    j["objects"].push_back(jobj);
                }

                std::ofstream file(path);
                if (!file.is_open()) return false;

                file << j.dump();
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        Types::Project importprojectfromfile(std::string path)
        {
            Types::Project project;

            try
            {
                std::ifstream file(path);
                if (!file.is_open()) return project;

                nlohmann::json j;
                file >> j;

                if (!j.contains("objects") || !j["objects"].is_array())
                    return project;

                for (auto& jobj : j["objects"])
                {
                    auto obj = std::make_unique<Types::Object>();
                    if (jobj.contains("position"))
                    {
                        obj->position.x = jobj["position"].value("x", 0.0f);
                        obj->position.y = jobj["position"].value("y", 0.0f);
                    }

                    project.objects.push_back(std::move(obj));
                }
            }
            catch (...)
            {
                return {};
            }

            return project;
        }
    }

	namespace f_export
	{
		bool f_export()
		{
			return json::exporttofile(data::project,data::filepath);
		}
	}
	namespace f_import
	{
		bool f_import()
		{
            data::project = json::importprojectfromfile(data::filepath);
            return true;
		}
    }
}
