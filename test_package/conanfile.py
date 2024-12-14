import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, cmake_layout
from conan.tools.build import can_run
from os.path import join


class boosTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain" 

    def generate(self):
        deps = CMakeDeps(self)
        deps.check_components_exist = True
        deps.generate()

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("gtest/1.15.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()	

    def imports(self):
        self.copy("*.so", "bin", "lib")
        self.copy("*.dll", "bin", "bin")
        self.copy("*.dylib", "bin", "lib")

    def layout(self):
        cmake_layout(self)

    def test(self):
        self.run(join(self.build_folder, "test_package"), env="conanrun")
