set_languages("c++20")
set_policy("build.c++.modules", false) -- 可选，避免旧版模块策略干扰
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
-- 平台判断
local is_android = is_plat("android")

local function copy_shaders(outdir, copy, mkdir)
    local src_dir = path.join(os.projectdir(), "src", "shaders")
    local shaders = os.files(path.join(src_dir, "**"))
    if #shaders == 0 then
        raise("No shader files found in %s", src_dir)
    end

    for _, file in ipairs(shaders) do
        local dst = path.join(outdir, "shaders", path.relative(file, src_dir))
        mkdir(path.directory(dst))
        copy(file, dst)
    end
end

-- 依赖声明


add_requires("vcpkg::skia", {alias = "skia", configs = {features = {"gl"}}})
if not is_android then
    add_requires("vcpkg::glfw3")
end

target("PhoUI")
    set_kind("static")
    add_files(
        "src/**.cpp"
    )

    -- 头文件目录，public 让依赖方自动继承
    add_includedirs("src", {public = true})

    -- 包依赖
    add_packages("skia", {public = true})
    on_load(function (target)
        local pkg = target:pkg("skia")
        if pkg then
            local incs = table.join(
                pkg:get("includedirs") or {},
                pkg:get("sysincludedirs") or {}
            )
            for _, inc in ipairs(incs) do
                if path.filename(inc) == "include" and path.filename(path.directory(inc)) == "skia" then
                    target:add("includedirs", path.directory(inc), {public = true})
                end
            end
        end
    end)
    if not is_android then
        add_packages("vcpkg::glfw3", {public = true})
    end

    -- 平台相关的系统库
    if is_android then
        add_syslinks("android", "log", "EGL", "GLESv3")
    else
        add_syslinks("GLESv2", "EGL")
    end

    -- 编译定义
    add_defines("PHOUI_BUILD_DLL")

    -- POST_BUILD：复制头文件和 shaders
    after_link(function (target)
        copy_shaders(target:targetdir(), os.cp, os.mkdir)
        local src_dir = path.join(os.projectdir(), "src")
        local dst_dir = path.join(target:targetdir(), "include")
        os.mkdir(dst_dir)
        -- 递归收集所有 .h 和 .hpp
        local headers = table.join(
            os.files(path.join(src_dir, "**.h")),
            os.files(path.join(src_dir, "**.hpp"))
        )
        for _, file in ipairs(headers) do
            local rel = path.relative(file, src_dir)
            local dst = path.join(dst_dir, rel)
            os.mkdir(path.directory(dst))
            os.cp(file, dst)
        end
    end)

target("test")
    set_kind("binary")
    add_files("test/test.cpp")
    add_deps("PhoUI")
    after_link(function (target)
        copy_shaders(target:targetdir(), os.cp, os.mkdir)
    end)