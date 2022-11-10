#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>

struct PixelInfo {
    sf::Vector2f position[4];
    sf::Color color = sf::Color::White;

    PixelInfo(sf::Vector2f position[4], sf::Color color);
};

class Pixels {
   public:
    void addPixel(PixelInfo p);
    const sf::Vector2f getCenterPixelPosition(unsigned int idx);
    void setColor(sf::Color color, int idx);
    inline const sf::Color getColor(int idx) { return m_pixelInfoVec.at(idx).color; }
    inline bool isValidPixel(int idx) {
        return (idx >= 0) && (idx < static_cast<long>(m_pixelInfoVec.size()));
    }
    inline const sf::VertexArray& getVertexArray() { return m_quad; }
    inline unsigned int getNumPixels() const { return m_pixelInfoVec.size(); }
    inline const std::vector<PixelInfo>& getPixelInfo() { return m_pixelInfoVec; };
    const std::vector<uint8_t> getColorArray();

   private:
    sf::VertexArray m_quad{sf::Quads};
    std::vector<PixelInfo> m_pixelInfoVec{};
};

class Grid {
   public:
    Grid(unsigned int numPixelsX, float windowWidth, float windowHeight);
    void setPixelColor(int pixelIdx, sf::Color color);
    const std::vector<unsigned int> getNeighborIndices(unsigned int idx);
    inline const sf::Color getPixelColor(int pixelIdx) { return m_pixels.getColor(pixelIdx); };
    // function used for rendering
    inline const sf::VertexArray& getVertexArray() { return m_pixels.getVertexArray(); }
    inline unsigned int getNumPixels() const { return m_pixels.getNumPixels(); }
    inline unsigned int getNumPixelsX() { return m_numPixelsX; }
    inline unsigned int getNumPixelsY() { return m_numPixelsY; }
    inline const std::vector<PixelInfo>& getPixelInfo() { return m_pixels.getPixelInfo(); };
    inline const PixelInfo& getPixelInfoAt(unsigned int idx) {
        return m_pixels.getPixelInfo().at(idx);
    };
    inline const sf::Vector2u idxToCoords(unsigned int idx) {
        return sf::Vector2u(idx % m_numPixelsX, static_cast<unsigned int>(idx / m_numPixelsX));
    }
    inline const sf::Vector2f getCenterPixelPosition(unsigned int idx) {
        return m_pixels.getCenterPixelPosition(idx);
    }
    inline const sf::Vector2f getCenterPixelPositionWindowRelative(unsigned int idx) {
        sf::Vector2f vec = m_pixels.getCenterPixelPosition(idx);
        return sf::Vector2f{vec.x / m_windowWidth, vec.y / m_windowHeight};
    }
    inline const std::vector<uint8_t> getColorArray() { return m_pixels.getColorArray(); }
    void writeToImage(const std::string& fileName) {
        // create the directory if doesn't exist
        std::filesystem::create_directory("out");
        sf::Image image;
        image.create(m_numPixelsX, m_numPixelsY, m_pixels.getColorArray().data());
        image.saveToFile("out/" + fileName + ".png");
    }

   private:
    void initialize();
    Pixels m_pixels{};
    unsigned int m_numPixelsX;
    unsigned int m_numPixelsY;
    float m_pixelSizeX;
    float m_pixelSizeY;
    float m_windowWidth;
    float m_windowHeight;
};

#endif