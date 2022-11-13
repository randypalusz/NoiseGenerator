from conans import ConanFile, CMake


class NoiseGeneratorConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "sfml/2.5.1"
    generators = "cmake"

    def imports(self):
        if self.settings.os == "Macos":
            self.copy("*.dylib*", dst="bin", src="lib")

    def configure(self):
        if self.settings.os == "Macos":
            self.options["sfml"].shared = True
            self.options["sfml"].window = True
            self.options["sfml"].graphics = True
