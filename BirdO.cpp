#include "BirdB.hpp"
#include "TextureManager.hpp"

// The Render method is used to render the bird based on its frame rate
void BirdO::Render(SDL_Renderer* ren)
{
    frate++;
	if (frate < 16)
	{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (frate >= 16 && frate <= 32)
	{
		SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (frate >32 && frate<=44)
	{
		SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
    else if (frate > 44)
	{
		SDL_RenderCopyEx(ren, Tex3, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	if (frate > 43)
	{
		frate = 0;
	}
//polymorphic behaviour
//we need three more create texture operation since one instance of the bird is already instantiated when the game loads. After that we only have three more pictures to cater out of the four for BirdO
}

// createTexture1, createTexture2, and createTexture3 methods are used to create additional textures 
void BirdO::createTexture1(const char* address, SDL_Renderer* ren){
    Tex1=TextureManager::Texture(address, ren);
}
void BirdO::createTexture2(const char* address, SDL_Renderer* ren){
    Tex2=TextureManager::Texture(address, ren);
}
void BirdO::createTexture3(const char* address, SDL_Renderer* ren){
    Tex2=TextureManager::Texture(address, ren);
}
