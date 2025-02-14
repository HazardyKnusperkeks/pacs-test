Project {
    name: "PACS-Test"

    Application {
        files: [
            "columns.hpp",
            "columns.qdoc",
            "list_view.cpp",
            "list_view.hpp",
            "main.cpp",
            "person_model.cpp",
            "person_model.hpp",
            "vip_delegate.cpp",
            "vip_delegate.hpp",
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

