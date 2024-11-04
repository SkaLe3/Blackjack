#pragma once
#include <World/Entities/SpriteObject.h>



#include <unordered_map>

enum class ECardFace : byte
{
	Front = 0,
	Back = 1
};

class CardAnimationComponent;

class Card : public Core::SpriteObject
{
	DECLARE_SUPER(Core::SpriteObject)
public:
	Card();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Destroy() override;
	//~ End Object Interface

	void TurnOver(float duration, byte axis = 0); // 0: x, 1: y
	void Flip();
	void Move(float duration ,const glm::vec2& start, const glm::vec2& target, float startRot = 0, float targetRot = 0, bool clockwise = false);
	void AssignFrontFace(const String& faceName);
	void AssignBackFace(const String& backName);
	void SetInitialState(ECardFace initialFace);

	SharedPtr<CardAnimationComponent> GetAnimationComponent();
private:
	void SelectFace();

private:
	WeakPtr<CardAnimationComponent> m_AnimComp;

	ECardFace m_CardFace;

	String m_FaceName;
	String m_BackName;

	std::unordered_map<ECardFace, String> m_FacesMapping;


};

