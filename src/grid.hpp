#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <string>

struct Pixel {
    sf::Vector2f position[4];
    sf::Color color = sf::Color::White;

    Pixel(sf::Vector2f position[4], sf::Color color) {
        for (int i = 0; i < 4; i++) {
            this->position[i] = position[i];
        }
        this->color = color;
    }
};

struct Pixels {
    sf::VertexArray m_quad{sf::Quads};
    std::vector<Pixel> m_pixels{};

    void addPixel(Pixel p) {
        m_pixels.push_back(p);

        m_quad.append(p.position[0]);
        m_quad.append(p.position[1]);
        m_quad.append(p.position[2]);
        m_quad.append(p.position[3]);

        setColor(p.color, m_pixels.size() - 1);
    }

    void setColor(sf::Color color, int idx) {
        int startIdx = idx * 4;
        int endIdx = startIdx + 4;
        for (int i = startIdx; i < endIdx; i++) {
            m_quad[i].color = color;
        }
        // sync the color of the vertex array with the user-defined struct
        m_pixels.at(idx).color = color;
    }

    const sf::Color getColor(int idx) { return m_pixels.at(idx).color; }

    // returns whether the pixel is inside the bounds of the grid
    bool isValidPixel(int idx) {
        bool condition = (idx >= 0) && (idx < m_pixels.size());
        std::string append = condition ? "is" : "is not";
        printf("%i %s a valid pixel\n", idx, append.c_str());
        return condition;
    }
};

class Grid {
   public:
    Grid(unsigned int numPixelsX, unsigned int numPixelsY, float windowWidth);
    void setPixelColor(int pixelIdx, sf::Color color);
    std::vector<unsigned int> getNeighborIndices(unsigned int idx);
    const sf::Color getPixelColor(int pixelIdx) { return m_pixels.getColor(pixelIdx); };
    const Pixels& getPixels() { return m_pixels; };

   private:
    void initialize();
    Pixels m_pixels;
    unsigned int m_numPixelsX;
    unsigned int m_numPixelsY;
    float m_pixelSize;
};

#endif