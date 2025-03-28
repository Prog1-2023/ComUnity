#include "GameWidget.h"

#include "UIManager.h"

GameWidget::GameWidget(const bool& _openedByDefault) : Widget("Game", _openedByDefault)
{
	UIManager::GetInstance().GetToolbar().OnGameStatusChanged().Add(this, &GameWidget::UpdateFocus);
}

void GameWidget::UpdateFocus(bool _gameStatus)
{
	if (!_gameStatus)
		return;
	SetWindowFocus("Game");
}

void GameWidget::Draw()
{
	Image((ImTextureID)0, GetContentRegionAvail(), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // TODO draw game texture
}

