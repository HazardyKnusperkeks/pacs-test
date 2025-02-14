#include "image.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <thread>

Image::Image(void) noexcept : Width{0}, Height{0} {
    return;
}

Image::Image(std::span<const std::uint16_t> data, int width, int height) noexcept :
        Data{data.begin(), data.end()}, Width{width}, Height{height} {
    return;
}

std::span<const uint16_t> Image::data(void) const noexcept {
    return Data;
}

Image& Image::operator=(std::span<const std::uint16_t> data) {
    if ( data.size() != Data.size() ) {
        throw std::runtime_error{"Size Mismatch"};
    } //if ( data.size() != Data.size() )

    std::ranges::copy(data, Data.begin());
    return *this;
}

Image Image::operator+(const Image& that) const noexcept {
    Image ret{*this};
    for ( auto index : allIndices() ) {
        ret[index] = std::clamp(operator[](index) + that[index], 0, (1 << 16) - 1);
    } //for ( auto index : allIndices() )
    return ret;
}

Image Image::operator-(const Image& that) const noexcept {
    Image ret{*this};
    for ( auto index : allIndices() ) {
        ret[index] = std::clamp(operator[](index) - that[index], 0, (1 << 16) - 1);
    } //for ( auto index : allIndices() )
    return ret;
}

Image Image::eroded(Kernel kernel) const noexcept {
    Image ret{*this};

    const auto size      = Width * Height;
    const auto chunkSize = size / std::jthread::hardware_concurrency();

    auto op              = [&ret, *this, &kernel](auto indices) {
        for ( auto index : indices ) {
            auto transformation = [this, &index](Offset offset) noexcept {
                auto offsetIndex = index + offset;
                if ( !offsetIndex.isValid(Width, Height) ) {
                    return std::numeric_limits<std::uint16_t>::max();
                } //if ( !offsetIndex.isValid(Width, Height) )
                return operator[](offsetIndex);
            };
            ret[index] = std::ranges::min(kernel | std::views::transform(transformation));
        } //for ( auto index : indices )
        return;
    };

    std::vector<std::jthread> threads;
    std::ranges::transform(allIndices() | std::views::chunk(chunkSize), std::back_inserter(threads),
                           [&op](auto indices) noexcept { return std::jthread{op, indices}; });
    threads.clear();

    return ret;
}

Image Image::dilated(Kernel kernel) const noexcept {
    Image ret{*this};

    const auto size      = Width * Height;
    const auto chunkSize = size / std::jthread::hardware_concurrency();

    auto op              = [&ret, *this, &kernel](auto indices) {
        for ( auto index : indices ) {
            auto transformation = [this, &index](Offset offset) noexcept {
                auto offsetIndex = index + offset;
                if ( !offsetIndex.isValid(Width, Height) ) {
                    return std::numeric_limits<std::uint16_t>::min();
                } //if ( !offsetIndex.isValid(Width, Height) )
                return operator[](offsetIndex);
            };
            ret[index] = std::ranges::max(kernel | std::views::transform(transformation));
        } //for ( auto index : indices )
        return;
    };

    std::vector<std::jthread> threads;
    std::ranges::transform(allIndices() | std::views::chunk(chunkSize), std::back_inserter(threads),
                           [&op](auto indices) noexcept { return std::jthread{op, indices}; });
    threads.clear();

    return ret;
}

std::uint16_t Image::at(const Index index, const Kernel kernel) const noexcept {
    std::uint32_t sum     = 0;
    int           counter = 0;

    for ( auto offset : kernel ) {
        auto offsetIndex = index + offset;

        if ( !offsetIndex.isValid(Width, Height) ) {
            continue;
        } //if ( !offsetIndex.isValid(Width, Height) )
        sum += operator[](offsetIndex);
        ++counter;
    } //for ( auto offset : kernel )
    const auto mean = sum / counter;
    return std::clamp(mean, 0u, (1u << 16) - 1);
}

void Image::transform(std::uint16_t newZero, std::uint16_t newOne) noexcept {
    for ( auto index : allIndices() ) {
        operator[](index) = std::clamp(operator[](index), newZero, newOne);
    } //for ( auto index : allIndices() )
    return;
}
