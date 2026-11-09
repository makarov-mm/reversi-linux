#include "Resources.h"

#include <algorithm>
#include <stdexcept>
#include <string>

namespace resources {

std::span<const unsigned char> Data(std::string_view name)
{
    const auto files = Files();
    const auto found = std::ranges::find(files, name, &File::name);
    if (found == files.end())
        throw std::runtime_error("A file is missing from the program: " + std::string(name));
    return found->data;
}

std::string_view Text(std::string_view name)
{
    const auto data = Data(name);
    return {reinterpret_cast<const char*>(data.data()), data.size()};
}

} // namespace resources
