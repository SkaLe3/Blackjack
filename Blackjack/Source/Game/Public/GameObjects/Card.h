#pragma once
#include <World/Entities/SpriteObject.h>



#include <unordered_map>

enum class ECardFace : byte
{
	Front = 0,
	Back = 1
};
enum class ECardRank : byte
{
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Jack = 10,
	Queen = 10,
	King = 10,
	Ace = 11 // Handle as a special case
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

	int32 GetValue();
	void TurnOver(float duration, byte axis = 0); // 0: x, 1: y
	void Flip();
	void Move(float duration, const glm::vec2& start, const glm::vec2& target, float startRot = 0, float targetRot = 0, bool clockwise = false);
	void AssignFrontFace(const String& faceName);
	void AssignBackFace(const String& backName);
	void AssignRank(ECardRank rank);
	void SetInitialState(ECardFace initialFace);

	SharedPtr<CardAnimationComponent> GetAnimationComponent();
private:
	void SelectFace();

private:
	WeakPtr<CardAnimationComponent> m_AnimComp;

	ECardFace m_CardFace;
	ECardRank m_Rank;

	String m_FaceName;
	String m_BackName;

	std::unordered_map<ECardFace, String> m_FacesMapping;


};

