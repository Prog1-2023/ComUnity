#include "SceneWidget.h"

SceneWidget::SceneWidget(const bool& _openedByDefault) : Widget("Scene", _openedByDefault)
{
	onDroppedElement = Event<void, int>();
}

void SceneWidget::Draw()
{
	Image((ImTextureID)0, GetContentRegionAvail(), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // TODO draw scene texture
	if (BeginDragDropTarget())
	{
		if (const ImGuiPayload* _payload = AcceptDragDropPayload("SPAWN_ACTOR"))
		{
			const int* _int = static_cast<int*>(_payload->Data);
			onDroppedElement.Invoke(*_int);
		}
		EndDragDropTarget();
	}
}

