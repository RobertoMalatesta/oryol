fips_begin_app(Instancing windowed)
    fips_vs_warning_level(3)
    fips_files(Instancing.cc)
    fips_generate(TYPE Shader FROM shaders.shd)
    fips_deps(Gfx Assets Time Dbg Input)
    oryol_add_web_sample(Instancing "Instanced rendering" "emscripten,pnacl,android" Instancing.jpg "Instancing/Instancing.cc")
fips_end_app()
