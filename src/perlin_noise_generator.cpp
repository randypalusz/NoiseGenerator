#include "generators.hpp"
#include "util.hpp"

#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <cmath>
#include <assert.h>

double PerlinNoiseGenerator::grad(unsigned int hash, double x, double y, double z) {
    // Take the hashed value and take the first 4 bits of it
    // (15 == 0b1111)

    unsigned h = hash & 15;

    // If the most significant bit (MSB) of the hash is 0
    // then set u = x.  Otherwise y.

    double u = h < 8 /* 0b1000 */ ? x : y;

    double v;

    if (h < 4 /* 0b0100 */)
        // If the first and second significant bits
        // are 0, set v = y
        v = y;
    else if (h == 12 /* 0b1100 */ || h == 14 /* 0b1110*/)
        // If the first and second significant bits
        // are 1, set v = x
        v = x;
    else
        // If the first and second significant bits are not
        // equal (0/1, 1/0) set v = z
        v = z;

    // Use the last 2 bits to decide if u and v are positive
    // or negative. Then return their addition.

    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double PerlinNoiseGenerator::noise(double x, double y, double z) {
    // Calculate the "unit cube" that the point asked will be located in
    // The left bound is ( |_x_|,|_y_|,|_z_| ) and the right bound is that
    // plus 1.  Next we calculate the location (from 0.0 to 1.0) in that
    // cube. We also fade the location to smooth the result.

    int xi = (int)x & 255;
    int yi = (int)y & 255;
    int zi = (int)z & 255;

    double xf = x - (int)x;
    double yf = y - (int)y;
    double zf = z - (int)z;

    double u = fade(xf);
    double v = fade(yf);
    double w = fade(zf);

    int aaa, aba, aab, abb, baa, bba, bab, bbb;
    auto& p = permutation;

    aaa = p[p[p[xi] + yi] + zi];
    aba = p[p[p[xi] + inc(yi)] + zi];
    aab = p[p[p[xi] + yi] + inc(zi)];
    abb = p[p[p[xi] + inc(yi)] + inc(zi)];
    baa = p[p[p[inc(xi)] + yi] + zi];
    bba = p[p[p[inc(xi)] + inc(yi)] + zi];
    bab = p[p[p[inc(xi)] + yi] + inc(zi)];
    bbb = p[p[p[inc(xi)] + inc(yi)] + inc(zi)];

    // printf("{xi, yi, zi}: {%u, %u, %u}\n", xi, yi, zi);
    // printf("{xf, yf, zf}: {%f, %f, %f}\n", xf, yf, zf);
    // printf("{u, v, w}: {%f, %f, %f}\n", u, v, w);
    // printf("{aaa, aba, aab, abb, baa, bba, bab, bbb}: {%i, %i, %i, %i, %i, %i, %i, %i}\n", aaa,
    // aba,
    //        aab, abb, baa, bba, bab, bbb);

    double x1, x2, y1, y2;

    // The gradient function calculates the dot product between a
    // pseudorandom gradient vector and the vector from the input
    // coordinate to the 8 surrounding points in its unit cube.

    // This is all then lerped together as a sort of weighted average
    // based on the faded (u,v,w) values we made earlier.

    x1 = lerp(grad(aaa, xf, yf, zf), grad(baa, xf - 1, yf, zf), u);

    x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);

    y1 = lerp(x1, x2, v);

    x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);

    x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);

    y2 = lerp(x1, x2, v);

    // printf("{x1, x2, y1, y2}: {%f, %f, %f, %f}\n", x1, x2, y1, y2);

    auto result = (lerp(y1, y2, w) + 1) / 2;
    // printf("{result}: {%f}\n\n", result);

    assert(0 <= result);
    assert(result <= 1);
    assert(false == std::isnan(result));

    return result;
}

void PerlinNoiseGenerator::generatePermutationArray() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<unsigned int> tempVec;
    tempVec.reserve(512);
    for (unsigned int i = 0; i < 256; i++) {
        tempVec.push_back(i);
    }
    std::shuffle(tempVec.begin(), tempVec.end(), std::default_random_engine(seed));
    for (unsigned int i : tempVec) {
        tempVec.push_back(i);
    }
    int i = 0;
    for (auto it = tempVec.begin(); it != tempVec.end(); it++, i++) {
        permutation[i] = (*it);
    }
}

void PerlinNoiseGenerator::run(Grid& grid) {
    auto pixelInfo = grid.getPixelInfo();
    int i = 0;
    while (!m_shouldStop) {
        for (auto it = pixelInfo.begin(); it != pixelInfo.end(); it++, i++) {
            if (m_shouldStop) {
                break;
            }
            auto next = std::chrono::system_clock::now() + std::chrono::nanoseconds(100);
            sf::Vector2f coords = grid.getCenterPixelPosition(i);
            double noiseResult = noise(coords.x * 0.01, coords.y * 0.01, 0);
            sf::Uint8 usableResult = static_cast<sf::Uint8>(rangeConvert(noiseResult));
            sf::Color newColor{usableResult, usableResult, usableResult, usableResult};
            grid.setPixelColor(i, newColor);
            std::this_thread::sleep_until(next);
        }
        m_shouldStop = true;
    }
    printf("exiting run in PerlinNoiseGenerator\n");
}