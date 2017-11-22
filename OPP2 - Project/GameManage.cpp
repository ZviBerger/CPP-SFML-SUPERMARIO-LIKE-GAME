#include "GameManage.h"


GameManage::GameManage(sf::Texture & texture, sf::Vector2f position, sf::Vector2f size)
    : m_texture(texture), m_position(position), m_size(size)
{
}

GameManage::~GameManage()
{
}
