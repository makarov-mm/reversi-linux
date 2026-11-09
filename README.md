# 3D Reversi — C++23, SDL2 and OpenGL 4.6 for Linux

[![GitHub Sponsors](https://img.shields.io/github/sponsors/makarov-mm?style=flat&logo=github)](https://github.com/sponsors/makarov-mm)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-00599C?logo=cplusplus&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-4.6-5586A4?logo=opengl&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?logo=linux&logoColor=black)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?logo=linkedin&logoColor=white)](https://www.linkedin.com/in/makarov-mm/)
[![Threads](https://img.shields.io/badge/Threads-000000?logo=threads&logoColor=white)](https://www.threads.net/@m.m.makarov)
[![Instagram](https://img.shields.io/badge/Instagram-E4405F?logo=instagram&logoColor=white)](https://www.instagram.com/m.m.makarov/)

A 3D Reversi (Othello) game for Linux written in modern C++ on SDL2 and OpenGL 4.6.

There is no game engine and no model, texture or sound file: the discs are turned on a lathe in code at startup, the materials are procedural, the lighting environment is baked on the GPU, and the sounds are synthesized. The only libraries are the ones every Linux desktop has: SDL2 for the window, the input and the sound, FreeType and fontconfig for the text. The shaders and the icon are built into the executable, so the game is a single file.

![Screenshot](screenshot.png)

![Themes](themes.png)

## Features

### Rules

- The standard rules: Black moves first from the four discs in the middle; a disc must bracket a line of the opponent's discs, which all turn over
- A side with no move passes, and the pass is announced; the game ends when neither side can move, and the most discs wins
- The squares are named as on a printed board, `a1` at the top left, so transcripts such as `f5d6c3d3c4` read the usual way

### Play

- A computer opponent with five levels, from Beginner to Master: iterative deepening, principal variation search and a transposition table, with an evaluation of mobility, frontier, corners, the squares next to them and stable discs, tuned in matches against itself; from 20 empty squares (at the top level) it plays the ending out exactly. It thinks in the background, so the window stays responsive
- Play Black, play White, two players on one computer, or watch a demo game
- The legal moves are marked; over one of them a see-through disc shows the move, and the discs it would turn lean towards turning and glow. The marks can be switched off
- Undo and redo, the move list with how many discs each move turned, the discs of each side and a bar of the score
- Hints: the suggested square is ringed
- Copy the game as a transcript or the position as a board string, and paste either to continue from it
- The game in progress, the settings and the window's size are kept between sessions
- English and Russian interface, chosen from the system language
- An about card with the author and links to his pages, which open in the browser
- Sound effects, mixed so that they can play over each other
- Full screen; the interface follows the desktop's scaling (X11's `Xft.dpi`, as Cinnamon, GNOME, KDE and Xfce set it, or the output scale on Wayland)
- Shortcuts work in any keyboard layout: by their letters in Latin layouts, by their places in others, such as the Russian one
- No work while nothing moves: the game waits for input instead of drawing the same picture

### Graphics

- Physically based shading: GGX highlights, a clear lacquer coat, soft light inside the discs, image-based lighting from a procedural studio environment
- Soft shadows (PCSS), contact shadows, and the discs reflected in the polished boards
- HDR rendering with 4× MSAA, bloom, ACES tone mapping, vignette and dithering
- Smooth edges everywhere: multisampling for the outlines, and the grid lines, the dots and the marks drawn by the shaders filtered over each pixel; highlights widen where the surface curves within a pixel, so they do not sparkle
- Discs of two halves turned on a lathe, white on one face and black on the other, with a fine groove where they meet
- Animation: each disc flies from its player's stack beside the board to its square, then the discs it brackets turn over in a wave running out from it; a move taken back runs the other way, and a new game dissolves in
- Four themes: Classic (green baize), Walnut, Marble and Neon
- An interface of frosted-glass panels, sharp at any screen scale

## Controls

| Action | Control |
|---|---|
| Place a disc | Click a marked square |
| Turn the view | Drag with either mouse button |
| Zoom | Mouse wheel |
| Take back / replay a move | `Ctrl+Z` / `Ctrl+Y`, `←` / `→`, `Backspace` |
| Hint | `H` |
| New game | `N` |
| Flip the board | `F` |
| View from above | `V` |
| Reset the view | `Home` |
| Computer level | `1` … `5` |
| Who plays whom | `M` (`Shift+M` back) |
| Show / hide the legal moves | `D` |
| Next theme | `T` (`Shift+T` back) |
| Sound on / off | `S` |
| English / Russian | `L` |
| Show / hide the panel | `Tab` |
| Full screen | `F11`, `Alt+Enter` |
| Copy the game / the position | `Ctrl+C` / `Ctrl+Shift+C` |
| Paste a game or a position | `Ctrl+V` |
| Help | `F1` |
| About the game and its author | `A` |
| Leave full screen | `Esc` |

## Requirements

- Linux Mint 22 or newer, Ubuntu 24.04 or newer, or another distribution with GCC 13 or newer (or Clang 19 or newer), CMake 3.20 or newer and SDL 2.0.18 or newer
- An X11 desktop, or a Wayland one (through XWayland or natively)
- A graphics card and driver with OpenGL 4.6 (4.5 is enough): Mesa for Intel and AMD, or the NVIDIA driver

## Building and running

On Linux Mint, Ubuntu or Debian, install the compiler and the libraries:

```sh
sudo apt install build-essential cmake libsdl2-dev libfreetype-dev libfontconfig-dev libpng-dev libx11-dev
```

Then build and run in the project's folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/reversi3d
```

To have the game in the applications menu, install it (to `/usr/local` by default):

```sh
sudo cmake --install build
```

The settings and the game in progress are kept in `~/.config/reversi3d/reversi3d.ini`.

## Project structure

```text
.
├── assets/                the icon and the menu entry (reversi3d.desktop)
├── cmake/Embed.cmake      builds the shaders and the icon into the executable
├── shaders/               GLSL shaders
├── src/
│   ├── Main.cpp           entry point
│   ├── App.*              the window, game flow, input and interface
│   ├── Reversi.*          the rules: bitboard move generation, notation, transcripts, the game record
│   ├── Engine.*           the computer player: search, evaluation and the exact solver of the ending
│   ├── PieceModels.*      the two halves of the disc, turned on a lathe
│   ├── BoardGeometry.*    meshes of the board, its frame and the table
│   ├── BoardView.*        the discs on the board and in the stacks, and their animation
│   ├── Camera.*           orbit camera and mouse rays
│   ├── Renderer.*         the rendering pipeline
│   ├── Themes.*           materials and lighting of the themes
│   ├── Gl.*               OpenGL context (SDL) and functions
│   ├── Text.*             font atlases drawn with FreeType from the fonts fontconfig finds
│   ├── UiPainter.*        drawing of the interface
│   ├── Sound.*            synthesized sound effects, mixed on the audio device
│   ├── Settings.*         the settings file
│   ├── Strings.*          English and Russian texts
│   ├── Desktop.*          the desktop's scaling (Xft.dpi) and the window icon
│   ├── Resources.*        access to the files built into the executable, and the icon decoded
│   └── MathTypes.h        vectors and matrices
└── CMakeLists.txt
```

## How a frame is drawn

1. **Shadow map** — the discs seen from the key light, for soft shadows.
2. **Reflection** — the discs mirrored under the board, drawn at half resolution and blurred into mipmaps, so the polish of each theme can show a sharper or softer reflection.
3. **Main pass** — the table, the board and the discs in HDR with 4× MSAA, lit by the key light and the baked environment; the background is the environment itself, and the disc a click would place is blended over it all.
4. **Post-processing** — the samples are resolved, bright parts spread into a six-level bloom, and the composite pass applies tone mapping and vignetting and frosts the glass behind the interface panels.
5. **Interface** — panels, text and icons, drawn on top.

The environment maps are baked with compute shaders when the theme changes, and the BRDF table once at startup.

## License

MIT License

Copyright (c) 2026 Mykhailo Makarov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Support

If you found this project interesting or useful, you can support my work:

[![GitHub Sponsors](https://img.shields.io/github/sponsors/makarov-mm?style=flat&logo=github)](https://github.com/sponsors/makarov-mm)
