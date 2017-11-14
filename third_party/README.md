# Instructions

## Windows

1. get SDL2 libraries
    - SDL2
    - SDL2-image
    - SDL2-ttf
2. copy files to ...
```
LaiNes/
  third_party/
    sdl2/
      include/
        SDL2/   - sdl2 headers here, e.g. SDL.h, SDL_image.h, SDL_ttf.h, ...
      lib/
        x64/    - sdl2 64bit libraries here, *.lib, *.dll
        x86/    - sdl2 32bit libraries here, *.lib, *.dll
```

## macOS

### Homebrew

```bash
brew install sdl2
```
