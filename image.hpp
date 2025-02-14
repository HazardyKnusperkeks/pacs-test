#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

struct Index {
    int X;
    int Y;

    bool isValid(int width, int height) const noexcept {
        return X >= 0 && X < width && Y >= 0 && Y < height;
    }
};

struct Offset {
    int X;
    int Y;
};

inline Index operator+(Index index, Offset offset) noexcept {
    return {index.X + offset.X, index.Y + offset.Y};
}

using Kernel = std::span<const Offset>;

class Image {
    public:
    Image(void) noexcept;
    Image(std::span<const std::uint16_t> data, int width, int height) noexcept;

    Image& operator=(std::span<const std::uint16_t> data);

    std::uint16_t& operator[](int x, int y) noexcept;

    template<typename Self>
    decltype(auto) operator[](this Self&& self, Index index) noexcept {
        return self.Data[index.X + index.Y * self.Width];
    }

    Image operator+(const Image& that) const noexcept;
    Image operator-(const Image& that) const noexcept;

    std::span<const std::uint16_t> data(void) const noexcept;

    Image eroded(Kernel kernel) const noexcept;
    Image dilated(Kernel kernel) const noexcept;

    Image opened(Kernel kernel) const noexcept {
        return eroded(kernel).dilated(kernel);
    }

    Image closed(Kernel kernel) const noexcept {
        return dilated(kernel).eroded(kernel);
    }

    Image whiteHat(Kernel kernel) const noexcept {
        return *this - opened(kernel);
    }

    Image blackHat(Kernel kernel) const noexcept {
        return *this - closed(kernel);
    }

    Image enhanced(Kernel kernel) const noexcept {
        /* Idee von
         * https://towardsdatascience.com/contrast-enhancement-of-grayscale-images-using-morphological-operators-de6d483545a1/
         * funktioniert (hier) nur nicht, oder ich habe etwas falsch verstanden. */
        return *this + whiteHat(kernel) - blackHat(kernel);
    }

    void transform(std::uint16_t newZero, std::uint16_t newOne) noexcept;

    private:
    std::vector<std::uint16_t> Data;
    int                        Width;
    int                        Height;

    auto allIndices(void) const noexcept {
        return std::views::cartesian_product(std::views::iota(0, Width), std::views::iota(0, Height)) |
               std::views::transform(
                   [](const auto& tuple) noexcept { return Index{std::get<0>(tuple), std::get<1>(tuple)}; });
    }

    std::uint16_t at(Index index, Kernel kernel) const noexcept;
};

inline std::uint16_t& Image::operator[](int x, int y) noexcept {
    return operator[](Index{x, y});
}

#endif //IMAGE_HPP
