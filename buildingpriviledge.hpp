#include "includes.h"

class BuildingPrivlidge
{
public:
    std::vector<std::string> players()
    {
        uintptr_t list = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x590);

        int list_size = driver.Read<int>(list + 0x18);
        uintptr_t list_start = driver.Read<uintptr_t>(list + 0x10);

        std::vector<std::string> temp_names{};

        for (int i = 0; i < list_size; i++)
        {
            auto current_ptr = driver.Read<uintptr_t>(list_start + (0x20 + (i * 0x8)));

            std::wstring wname = driver.read_wstr(driver.Read<uintptr_t>(current_ptr + 0x18) + 0x14);

            temp_names.push_back(std::string(wname.begin(), wname.end()));
        }

        return temp_names;
    }

    bool is_decaying()
    {
        return driver.Read<float>(reinterpret_cast<uintptr_t>(this) + 0x580) <= 0;
    }
};