#include "GameWidget.h"

GameWidget::GameWidget(const bool& _openedByDefault) : Widget("Game", _openedByDefault)
{
}

void GameWidget::Draw()
{
	Image((ImTextureID)0, GetContentRegionAvail(), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // TODO draw game texture
}

