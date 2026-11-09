#include "Desktop.h"

#include "Resources.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <X11/Xlib.h>
#include <png.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

namespace desktop {

float TextScale(SDL_Window* window)
{
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    if (!SDL_GetWindowWMInfo(window, &info) || info.subsystem != SDL_SYSWM_X11)
        return 1;
    const char* resource = XGetDefault(info.info.x11.display, "Xft", "dpi");
    if (!resource)
        return 1;
    const float dpi = std::strtof(resource, nullptr);
    return dpi >= 48 && dpi <= 480 ? dpi / 96 : 1;
}

void SetIcon(SDL_Window* window)
{
    const auto file = resources::Data("reversi3d.png");
    png_image image{};
    image.version = PNG_IMAGE_VERSION;
    if (!png_image_begin_read_from_memory(&image, file.data(), file.size()))
        return;
    image.format = PNG_FORMAT_RGBA;
    std::vector<std::uint8_t> pixels(PNG_IMAGE_SIZE(image));
    if (!png_image_finish_read(&image, nullptr, pixels.data(), 0, nullptr)) {
        png_image_free(&image);
        return;
    }
    const int width = static_cast<int>(image.width), height = static_cast<int>(image.height);
    if (SDL_Surface* icon = SDL_CreateRGBSurfaceWithFormatFrom(pixels.data(), width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32)) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }
}

} // namespace desktop
