#pragma once
#include <World/Entities/SpriteObject.h>


#include <unordered_map>

enum class ECardFace : byte
{
	Front = 0,
	Back = 1
};


class Card : public Core::SpriteObject
{
	DECLARE_SUPER(Core::SpriteObject)
public:
	Card();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void TurnOver();
	void AssignFrontFace(const String& faceName);
	void AssignBackFace(const String& backName);
	void SetInitialState(ECardFace initialFace);
private:
	void SelectFace();

private:
	ECardFace m_CardFace;

	String m_FaceName;
	String m_BackName;

	std::unordered_map<ECardFace, String> m_FacesMapping;


};

