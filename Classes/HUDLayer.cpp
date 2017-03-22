//SAMANTHA MARAH
//K00200782

#include "HUDLayer.h"

USING_NS_CC;

HudLayer::HudLayer()
{};

HudLayer::~HudLayer()
{};

void HudLayer::init_hud_layer(SecondWorld* SecondWorldScene)
{
	HUD = LayerGradient::create(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 0));
	HUD->setContentSize(m_size_a);
	HUD->setPosition(Vec2(m_position_x, m_position_y));

	SecondWorldScene->addChild(HUD, 4);
};

float HudLayer::set_hud_layer_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};

cocos2d::Size HudLayer::set_hud_layer_size(cocos2d::Size a)
{
	m_size_a = a;

	return m_size_a;
};

void HudLayer::init_lap_number(SecondWorld* scene4)
{
	lap_number = Label::createWithTTF("LAP NUMBER: ", "fonts/Marker Felt.ttf", 20);
	lap_number->setPosition(Vec2(m_position_c, m_position_d));
	lap_number->setAnchorPoint(Vec2(0, 0));

	lap_number->setString("LAP NUMBER: " + std::to_string(m_number_b) + "/10");

	HUD->addChild(lap_number, 5);
};

float HudLayer::set_lap_number_position(float c, float d)
{
	m_position_c = c;
	m_position_d = d;

	return m_position_c, m_position_d;
};

int HudLayer::set_lap_number(int b)
{
	m_number_b = b;

	return m_number_b;
};