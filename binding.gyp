{
    "conditions": [
        ['OS=="win"', {
            "variables": {
                "VCPKG_PATH": "K:\\vcpkg\\installed\\x64-windows"
            }
        }, {
            "variables": {
                "VCPKG_PATH": "/root/vcpkg/installed/x64-linux"
            }
        }]
    ],
    "targets": [
        {
            "target_name": "BindingImage",
            'include_dirs': [ 
                '.',
                'include',
                "<!(node -e \"require('nan')\")"
            ],
            "defines": [
                "_USE_MATH_DEFINES",
                "__STDC_CONSTANT_MACROS"
            ],
            "sources": [ 
                "source/binding.cc",
                "source/Frame.cc"
            ],
            "conditions": [
                ['OS=="win"', { 
                    "include_dirs": [
                        "<(VCPKG_PATH)\\include",
                        "<(VCPKG_PATH)\\include\\cairo",
                        "<(VCPKG_PATH)\\include\\glib-2.0",
                        "<(VCPKG_PATH)\\include\\gdk-pixbuf-2.0",
                        "<(VCPKG_PATH)\\lib\\glib-2.0\\include"
                    ],
                    "libraries": [
                        "<(VCPKG_PATH)\\lib\\*.lib"
                    ],
                    "defines": [
                        "USE_BINDING_WIN"
                    ],
                    "configurations": {
                        "Release": {
                            "msvs_settings": {
                                "VCCLCompilerTool": {
                                    "WarningLevel": 4,
                                    "ExceptionHandling": 1,
                                    "DisableSpecificWarnings": [
                                        4100, 4611, 4996
                                    ], 
                                    "AdditionalOptions": [
                                        "/MP", "/EHsc"
                                    ],
                                    "RuntimeLibrary": 2
                                }
                            }
                        },
                        "Debug": {
                            "msvs_settings": {
                                "VCCLCompilerTool": {
                                    "WarningLevel": 4,
                                    "ExceptionHandling": 1,
                                    "DisableSpecificWarnings": [
                                        4100, 4611, 4996
                                    ],
                                    "AdditionalOptions": [
                                        "/MP", "/EHsc"
                                    ],
                                    "RuntimeLibrary": 3
                                }
                            }
                        } 
                    }
                }, {
                    "include_dirs": [
                        "<(VCPKG_PATH)/include",
                        "<(VCPKG_PATH)/include/cairo",
                        "<(VCPKG_PATH)/include/glib-2.0",
                        "<(VCPKG_PATH)/include/gdk-pixbuf-2.0",
                        "<(VCPKG_PATH)/lib/glib-2.0/include"
                    ], 
                    "cflags": [
                        "-Wno-cast-function-type"
                    ],
                    "cflags!": [
                        "-fno-exceptions"
                    ],
                    "cflags_cc!": [
                        "-fno-exceptions"
                    ]
                }]
            ],
        } 
    ]
}