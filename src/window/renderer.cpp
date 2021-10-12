#include "renderer.h"

#include <vector>

Renderer::Renderer(
    SDL_Renderer *renderer,
    unsigned int scrWidth, unsigned int scrHeight,
    std::shared_ptr<Control> ctrl,
    std::shared_ptr<World> world) : SDLRenderer(renderer),
                                    screenWidth(scrWidth),
                                    screenHeight(scrHeight),
                                    control(ctrl),
                                    world(world)
{
    IMG_Init(IMG_INIT_PNG);
    loadTextures();

    clear(SDL_Color{0, 0, 0, 255});
    swap();
}

Renderer::~Renderer()
{
    IMG_Quit();
}

void Renderer::clear(SDL_Color color)
{
    SDL_Color prev;
    SDL_GetRenderDrawColor(SDLRenderer, &prev.r, &prev.g, &prev.b, &prev.a);

    SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(SDLRenderer);

    SDL_SetRenderDrawColor(SDLRenderer, prev.r, prev.g, prev.b, prev.a);
}

void Renderer::swap()
{
    SDL_RenderPresent(SDLRenderer);
}

void Renderer::render()
{
    clear(SDL_Color{0, 0, 0, 255});

    int blockLength = 10 * control->cameraScale;
    auto blockRange = Vec2i{(screenWidth / 2) / blockLength + 2, (screenHeight / 2) / blockLength + 2};
    auto blockAmount = blockRange * 2;

    std::vector<std::vector<std::shared_ptr<Block>>> renderBlocks(
        blockAmount.x, std::vector<std::shared_ptr<Block>>(blockAmount.y));
    for (auto x = -blockRange.x; x < blockRange.x; x++)
    {
        for (auto y = -blockRange.y; y < blockRange.y; y++)
        {
            renderBlocks[x + blockRange.x][y + blockRange.y] = world->getBlock(
                control->cameraPos.x + x,
                control->cameraPos.y + y);
        }
    }

    Vec2i screenCenter = {screenWidth / 2, screenHeight / 2};
    Vec2i cameraBlock = control->cameraPos;
    Vec2f cameraOffset = control->cameraPos - cameraBlock;

    for (auto x = 0; x < blockAmount.x; x++)
        for (auto y = 0; y < blockAmount.y; y++)
        {
            auto blockOffset = Vec2i{x - blockRange.x, y - blockRange.y} * blockLength;
            blockOffset += cameraOffset * blockLength * -1;
            auto blockScreenPos = screenCenter + blockOffset;
            SDL_Rect dstRect = {blockScreenPos.x, screenHeight - blockScreenPos.y, blockLength, blockLength};
            SDL_RenderCopy(SDLRenderer, textures[renderBlocks[x][y]->type]->texture, NULL, &dstRect);
        }

    swap();
}

void Renderer::loadTextures()
{
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::Air, std::make_unique<Texture>(SDLRenderer, "asset/block/Air.png")));
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::Dirt, std::make_unique<Texture>(SDLRenderer, "asset/block/Dirt.png")));
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::Grass, std::make_unique<Texture>(SDLRenderer, "asset/block/Grass.png")));
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::GrassBlock, std::make_unique<Texture>(SDLRenderer, "asset/block/GrassBlock.png")));
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::Leaf, std::make_unique<Texture>(SDLRenderer, "asset/block/Leaf.png")));
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::Water, std::make_unique<Texture>(SDLRenderer, "asset/block/Water.png")));
    textures.insert(std::pair<Block::Type, std::unique_ptr<Texture>>(
        Block::Type::Wood, std::make_unique<Texture>(SDLRenderer, "asset/block/Wood.png")));
}
