#pragma once

#include <span>
#include <string_view>

// The files built into the executable by cmake/Embed.cmake: the shaders and the icon.
namespace resources {

struct File {
    std::string_view name;
    std::span<const unsigned char> data;
};

// All of them, in the generated Embedded.cpp.
std::span<const File> Files();

// The bytes of a file, by its name ("disc.frag"); throws when there is no such file.
std::span<const unsigned char> Data(std::string_view name);
std::string_view Text(std::string_view name);

} // namespace resources
