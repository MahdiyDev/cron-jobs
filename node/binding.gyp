{
	"targets": [
		{
			"target_name": "Cronjob",
			"cflags!": ["-fno-exceptions"],
			"cflags_cc!": ["-fno-exceptions"],
			"cflags": ["-Wall", "-Wno-psabi", "-std=c++14", "-pthread"],
			"cflags_cc": ["-Wall", "-Wno-psabi", "-pthread"],
			"sources": ["src/Cronjob.cc"],
			"include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")", "../src/"],
			"dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
			"defines": ["NAPI_CPP_EXCEPTIONS"],
			'conditions': [
				["OS=='win'", {
					"defines": [
						"_HAS_EXCEPTIONS=1"
					],
					"msvs_settings": {
						"VCCLCompilerTool": {
							"ExceptionHandling": 1
						},
					},
				}],
			],
		}
	]
}
