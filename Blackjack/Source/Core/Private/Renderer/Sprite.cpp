#include "Renderer/Sprite.h"

namespace Core
{

	Sprite::Sprite(SharedPtr<Texture> inTexture, glm::vec2 inSrcSize, glm::vec2 inSrcPos)
		: m_Texture(inTexture), m_SourceSize(inSrcSize), m_SourcePos(inSrcPos) {}

}