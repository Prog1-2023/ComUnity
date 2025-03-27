#include "InspectorWidget.h"
#include "UIManager.h"
#include "HierarchyWidget.h"
#include "../Serialization/Serialization.h"
#include "Log.h"

InspectorWidget::InspectorWidget(const bool& _openedByDefault) : Widget("Inspector", _openedByDefault)
{
	currentSelectedActor = nullptr;

	UIManager& _manager = UIManager::GetInstance();
	HierarchyWidget* _widget = _manager.GetWidgetOfType<HierarchyWidget>();
	if (!_widget) return;

	_widget->OnActorSelected().Add(this,&InspectorWidget::SetCurrentActor);
}

void InspectorWidget::Draw()
{
	if (!currentSelectedActor)
		return;

	DrawComponents();
}

void InspectorWidget::DrawComponents()
{	
	vector<ValueAttachedToObject*> _serializedValues = Serialization::GetInstance().GetStoredValues();

	for (ValueAttachedToObject* _valAttached : _serializedValues)
	{
		if (_valAttached->object == currentSelectedActor)
		{
			vector<Component*> _allComponents = currentSelectedActor->GetComponents();

			for (Component* _component : _allComponents)
			{
				string _type = typeid(*_component).name();
				_type = _type.substr(_type.find_first_of(' ') + 1);

				if (!_valAttached->values.contains(_type))
					continue;

				map<string, vector<SerializedValue*>> _values = _valAttached->values;

				Text(_type.c_str());
				for (SerializedValue* _value : _values[_type])
				{
					//aled
					if (_value->type == "int" || _value->type == "unsigned int")
					{
						int* _var = static_cast<int*>(_value->variable);
						string _stingVar = string(to_string(*_var));
						const char* _temp = _stingVar.c_str();
						char* _buffer = const_cast<char*>(_temp);

						ImGui::InputText(_value->name.c_str(), _buffer, 10);
						string _result = _buffer;
						*_var = stoi(_result);
					}
					else if (_value->type == "float")
					{
						float* _var = static_cast<float*>(_value->variable);
						string _stingVar = string(to_string(*_var));
						const char* _temp = _stingVar.c_str();
						char* _buffer = const_cast<char*>(_temp);

						ImGui::InputText(_value->name.c_str(), _buffer, 10);
						string _result = _buffer;
						*_var = stof(_result);
					}
					else if (_value->type == "bool")
					{
						bool* _var = static_cast<bool*>(_value->variable);
						string _stingVar = string(to_string(*_var));
						const char* _temp = _stingVar.c_str();
						char* _buffer = const_cast<char*>(_temp);

						ImGui::Checkbox(_value->name.c_str(), _var);
					}
					else
					{
						LOG_WARNING("No Serializable Type");
					}
				}
			}
		}
	}

	
}

void InspectorWidget::ChangeValue()
{
}

