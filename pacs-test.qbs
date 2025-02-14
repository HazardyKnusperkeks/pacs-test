Project {
    name: "PACS-Test"

    Application {
        files: [
            "list_view.cpp",
            "list_view.hpp",
            "main.cpp",
        ]
        name: "List View"
        version: "0.1.0"

        Depends { name: "cpp" }
        Depends { name: "Qt"; submodules: ["core", "gui", "widgets"] }

        cpp.cxxLanguageVersion: "c++23"
    }

    Product {
        files: [
            ".clang-format",
            ".gitignore",
        ]
        name: "Projekt Dateien"
    }
}

