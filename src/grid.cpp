#include "grid.hpp"

#include <algorithm>

PixelInfo::PixelInfo(sf::Vector2f position[4], sf::Color color) {
    for (int i = 0; i < 4; i++) {
        this->position[i] = position[i];
    }
    this->color = color;
}

void Pixels::addPixel(PixelInfo p) {
    m_pixelInfoVec.push_back(p);

    m_quad.append(p.position[0]);
    m_quad.append(p.position[1]);
    m_quad.append(p.position[2]);
    m_quad.append(p.position[3]);

    setColor(p.color, m_pixelInfoVec.size() - 1);
}

const sf::Vector2f Pixels::getCenterPixelPosition(unsigned int idx) {
    int startIdx = idx * 4;
    // TODO: consider caching this to improve performance
    return sf::Vector2f((m_quad[startIdx + 2].position.x + m_quad[startIdx].position.x) / 2.0f,
                        (m_quad[startIdx].position.y + m_quad[startIdx + 1].position.y) / 2.0f);
}

void Pixels::setColor(sf::Color color, int idx) {
    int startIdx = idx * 4;
    int endIdx = startIdx + 4;
    for (int i = startIdx; i < endIdx; i++) {
        m_quad[i].color = color;
    }
    // sync the color of the vertex array with the user-defined struct
    m_pixelInfoVec.at(idx).color = color;
}

const std::vector<uint8_t> Pixels::getColorArray() {
    std::vector<uint8_t> returnVec{};
    for (PixelInfo& p : m_pixelInfoVec) {
        returnVec.push_back(p.color.r);
        returnVec.push_back(p.color.g);
        returnVec.push_back(p.color.b);
        returnVec.push_back(p.color.a);
    }
    return returnVec;
}

Grid::Grid(unsigned int numPixelsX, float windowWidth, float windowHeight) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    unsigned int clampedNumPixelsX =
        std::clamp(numPixelsX, (unsigned int)2, (unsigned int)windowWidth);
    m_numPixelsX = clampedNumPixelsX;
    m_numPixelsY = static_cast<unsigned int>((windowHeight / windowWidth) * clampedNumPixelsX);
    m_pixelSizeX = windowWidth / (float)m_numPixelsX;
    m_pixelSizeY = windowHeight / (float)m_numPixelsY;
    printf("m_numPixelsX, m_numPixelsY: {%u, %u}\n", m_numPixelsX, m_numPixelsY);
    initialize();
}

void Grid::initialize() {
    bool whiteOrBlack = true;
    sf::Vector2f drawPosition{0.0f, 0.0f};
    for (unsigned int i = 0; i < m_numPixelsY; i++) {
        for (unsigned int j = 0; j < m_numPixelsX; j++) {
            sf::Vector2f pos[4];
            pos[0] = sf::Vector2f(drawPosition.x, drawPosition.y + m_pixelSizeY);
            pos[1] = sf::Vector2f(drawPosition.x, drawPosition.y);
            pos[2] = sf::Vector2f(drawPosition.x + m_pixelSizeX, drawPosition.y);
            pos[3] = sf::Vector2f(drawPosition.x + m_pixelSizeX, drawPosition.y + m_pixelSizeY);
            PixelInfo p{pos, sf::Color::White};
            p.color = whiteOrBlack ? sf::Color::White : sf::Color::Black;
            whiteOrBlack = !whiteOrBlack;
            drawPosition.x += m_pixelSizeX;
            m_pixels.addPixel(p);
        }
        drawPosition.x = 0.0f;
        drawPosition.y += m_pixelSizeY;
    }
}

void Grid::setPixelColor(int pixelIdx, sf::Color color) { m_pixels.setColor(color, pixelIdx); }

const std::vector<unsigned int> Grid::getNeighborIndices(unsigned int idx) {
    std::vector<unsigned int> toCheck{idx - 1, idx + 1, idx - m_numPixelsX, idx + m_numPixelsX};
    std::vector<unsigned int> ret{};
    std::copy_if(toCheck.begin(), toCheck.end(), std::back_inserter(ret),
                 [&](auto val) { return m_pixels.isValidPixel(val); });
    return ret;
}
