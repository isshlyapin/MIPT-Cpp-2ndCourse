from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.cmake import CMakeDeps, CMakeToolchain

class MainRecipe(ConanFile):
    name = "belady_and_2q_caches"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "test": ["true", "false"],
    }
    default_options = {
        "test": "false",
    }

    # generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = (
        "CMakeLists.txt",
        "debug_config.cmake",
        "include/*",
        "src/*",
        "test/*",
    )

    def generate(self):
        dp = CMakeDeps(self)
        dp.generate()
        
        tc = CMakeToolchain(self)
        if self.options.test == "true":
            tc.variables["ENABLE_TESTING"] = "ON"
        tc.generate()

    def requirements(self):
        if self.options.test == "true":
            self.test_requires("gtest/1.16.0")

    def build_requirements(self):
        self.tool_requires("cmake/4.0.1")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "*", f"{self.source_folder}/bin", self.package_folder)

    def package_info(self):
        self.cpp_info.libs = ["belady_and_2q_caches"]
