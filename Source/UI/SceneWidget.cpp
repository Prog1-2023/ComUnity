#include "SceneWidget.h"

SceneWidget::SceneWidget(const bool& _openedByDefault) : Widget("Scene", _openedByDefault)
{
	onDroppedElement = Event<void, string>();
}

void SceneWidget::Draw()
{
	Image((ImTextureID)0, GetContentRegionAvail(), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // TODO draw scene texture
	if (BeginDragDropTarget())
	{
		if (const ImGuiPayload* _payload = AcceptDragDropPayload("SPAWN_ACTOR"))
		{
			const string* _text = static_cast<string*>(_payload->Data);
			onDroppedElement.Invoke(*_text);
		}
		EndDragDropTarget();
	}
}

