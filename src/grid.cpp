#include "grid.hpp"

Grid::Grid(unsigned int numPixelsX, unsigned int numPixelsY, float windowWidth) {
    m_numPixelsX = numPixelsX;
    m_numPixelsY = numPixelsY;
    // assuming square window here
    m_pixelSize = windowWidth / (float)numPixelsX;
    initialize();
}

void Grid::initialize() {
    bool whiteOrBlack = true;
    sf::Vector2f drawPosition{0.0f, 0.0f};
    for (int i = 0; i < m_numPixelsY; i++) {
        for (int j = 0; j < m_numPixelsX; j++) {
            sf::Vector2f position[4];
            position[0] = sf::Vector2f(drawPosition.x, drawPosition.y + m_pixelSize);
            position[1] = sf::Vector2f(drawPosition.x, drawPosition.y);
            position[2] = sf::Vector2f(drawPosition.x + m_pixelSize, drawPosition.y);
            position[3] = sf::Vector2f(drawPosition.x + m_pixelSize, drawPosition.y + m_pixelSize);
            Pixel p{position, sf::Color::White};
            p.color = whiteOrBlack ? sf::Color::White : sf::Color::Black;
            whiteOrBlack = !whiteOrBlack;
            drawPosition.x += m_pixelSize;
            m_pixels.addPixel(p);
        }
        drawPosition.x = 0.0f;
        drawPosition.y += m_pixelSize;
    }
}

void Grid::setPixelColor(int pixelIdx, sf::Color color) { m_pixels.setColor(color, pixelIdx); }

std::vector<unsigned int> Grid::getNeighborIndices(unsigned int idx) {
    std::vector<unsigned int> toCheck{idx - 1, idx + 1, idx - m_numPixelsX, idx + m_numPixelsX};
    std::vector<unsigned int> ret{};
    std::copy_if(toCheck.begin(), toCheck.end(), std::back_inserter(ret),
                 [&](auto val) { return m_pixels.isValidPixel(val); });
    printf("Neighbors of %i: {", idx);
    for (unsigned int i : ret) {
        printf("%i, ", i);
    }
    printf("}\n");
    return ret;
}
