#include <string>
#include <SDL2/SDL.h>

using namespace std;

class TexturedRect {
  private:
    SDL_Rect rect;
    SDL_Texture *texture;

  public:
    
    // Constructor
    TexturedRect(SDL_Renderer *&renderer, string imagePath);

    // Destructor
    ~TexturedRect();

    // Set rectangle properties
    void setProperties(int x, int y, int width, int height);

    void setCoordinates(int x, int y);

    int getXValue();

    int getYValue();

    // Render the texture
    void render(SDL_Renderer *&renderer);
};
