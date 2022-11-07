#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <string>

struct PixelInfo {
    sf::Vector2f position[4];
    sf::Color color = sf::Color::White;

    PixelInfo(sf::Vector2f position[4], sf::Color color);
};

class Pixels {
   public:
    void addPixel(PixelInfo p);
    void setColor(sf::Color color, int idx);
    const sf::Color getColor(int idx) { return m_pixelInfoVec.at(idx).color; }
    bool isValidPixel(int idx) { return (idx >= 0) && (idx < (long)m_pixelInfoVec.size()); }
    const sf::VertexArray& getVertexArray() { return m_quad; }
    unsigned int getNumPixels() { return m_pixelInfoVec.size(); }
    const std::vector<PixelInfo>& getPixelInfo() { return m_pixelInfoVec; };

   private:
    sf::VertexArray m_quad{sf::Quads};
    std::vector<PixelInfo> m_pixelInfoVec{};
};

class Grid {
   public:
    Grid(unsigned int numPixelsX, unsigned int numPixelsY, float windowWidth);
    void setPixelColor(int pixelIdx, sf::Color color);
    std::vector<unsigned int> getNeighborIndices(unsigned int idx);
    const sf::Color getPixelColor(int pixelIdx) { return m_pixels.getColor(pixelIdx); };
    const Pixels& getPixels() { return m_pixels; };
    const sf::VertexArray& getVertexArray() { return m_pixels.getVertexArray(); }
    unsigned int getNumPixels() { return m_pixels.getNumPixels(); }
    const std::vector<PixelInfo>& getPixelInfo() { return m_pixels.getPixelInfo(); };

   private:
    void initialize();
    Pixels m_pixels{};
    unsigned int m_numPixelsX;
    unsigned int m_numPixelsY;
    float m_pixelSize;
};

#endif