#include "InspectorWidget.h"
#include "UIManager.h"
#include "HierarchyWidget.h"
#include "../Serialization/Serialization.h"
#include "../Utils/Array.h"

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
					if (!DrawFromType(_value))
					{
						vector<std::any> _values = _component->GenerateSerialization();
						DrawFromComplexeClass(_values);
					}
				}
			}
		}
	}
}

bool InspectorWidget::DrawFromType(SerializedValue* _value)
{
	if (_value->type == "int" || _value->type == "unsigned int")
	{
		DrawIntOutput(_value);
		return true;
	}
	else if (_value->type == "float")
	{
		DrawFloatOutput(_value);
		return true;
	}
	else if (_value->type == "bool")
	{
		DrawBoolOutput(_value);
		return true;
	}
	return false;
}

void InspectorWidget::DrawFromComplexeClass(vector<std::any> _vector)
{

}

void InspectorWidget::DrawIntOutput(SerializedValue* _value)
{
	int* _var = static_cast<int*>(_value->variable);
	string _stingVar = string(to_string(*_var));
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::InputText(_value->name.c_str(), _buffer, 10);
	string _result = _buffer;
	*_var = stoi(_result);
}

void InspectorWidget::DrawFloatOutput(SerializedValue* _value)
{
	float* _var = static_cast<float*>(_value->variable);
	string _stingVar = string(to_string(*_var));
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::InputText(_value->name.c_str(), _buffer, 10);
	string _result = _buffer;
	*_var = stof(_result);
}

void InspectorWidget::DrawBoolOutput(SerializedValue* _value)
{
	bool* _var = static_cast<bool*>(_value->variable);
	string _stingVar = string(to_string(*_var));
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::Checkbox(_value->name.c_str(), _var);
}
