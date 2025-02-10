from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class helloRecipe(ConanFile):
    name = "sapy"
    version = "0.0.2"
    package_type = "library"

    # Optional metadata
    license = "BSD 3-Clause"
    author = "CairBin; EPTansuo"
    url = "https://github.com/CairBin/sapy"
    description = "Sapy is a collection of C++ libraries that are as \"simple as Python\"."
    topics = ("Basic", "Library", "Python")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "test/*", "bench/*"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("reflect-cpp/0.17.0")


    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["sapy"]

