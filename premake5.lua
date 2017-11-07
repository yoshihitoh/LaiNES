function set_preferred_location()
    filter 'action:vs2015'
        location 'build_vs2015'
    filter 'action:gmake*'
        location 'build_gmake'
end

workspace 'LaiNES'
    set_preferred_location {}
    configurations { 'Debug', 'Release' }

    filter 'configurations:Debug'
        defines { 'DEBUG' }
        symbols 'On'
        targetdir '.'
        targetsuffix '_debug'

    filter 'configurations:Release'
        defines { 'NDEBUG' }
        optimize 'On'
        targetdir '.'
        targetsuffix '_release'

    filter 'platforms:Windows'
        system 'windows'

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
        files {
            '**/*.h',
            '**/*.hpp',
        }

    filter 'action:gmake*'
        buildoptions { '-std=c++14' }
