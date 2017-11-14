function set_preferred_location()
    filter 'action:vs2015'
        location 'build_vs2015'
    filter 'action:gmake*'
        location 'build_gmake'
end

workspace 'LaiNES'
    configurations { 'Debug', 'Release' }
    targetdir 'bin/x86'
    debugdir '.'

    filter 'configurations:Debug'
        defines { 'DEBUG' }
        symbols 'On'
        targetsuffix '_debug'

    filter 'configurations:Release'
        defines { 'NDEBUG' }
        optimize 'On'
        targetsuffix '_release'

    set_preferred_location {}

project 'LaiNES'
    kind 'WindowedApp'
    language 'C++'
    set_preferred_location {}

    filter {}

    files {
        'src/*.cpp',
        'lib/*.cpp',
        'src/**/*.cpp',
        'lib/**/*.cpp',
    }

    removefiles {
        'src/porting/**.cpp',
    }

    includedirs {
        'simpleini',
        'lib/include',
        'src/include',
    }

    links {
        'SDL2',
        'SDL2_image',
        'SDL2_ttf',
    }

    filter 'action:vs*'
        toolset "msc-llvm-vs2014"

        files {
            '**/*.h',
            '**/*.hpp',
            'src/porting/windows/**.h',
            'src/porting/windows/**.hpp',
            'src/porting/windows/**.cpp',
        }

        includedirs {
            'third_party/sdl2/include',
        }

        libdirs {
            'third_party/sdl2/lib/x86',
        }

        links {
            'SDL2main',
        }

    filter 'action:gmake*'
        buildoptions { '-std=c++14' }

        files {
            'src/porting/unix/**.hpp',
            'src/porting/unix/**.cpp',
        }
