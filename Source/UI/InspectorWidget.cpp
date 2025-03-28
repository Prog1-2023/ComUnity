#include "InspectorWidget.h"
#include "UIManager.h"
#include "HierarchyWidget.h"
#include "../Serialization/Serialization.h"
#include "Log.h"
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
	Array<ValueAttachedToObject*> _serializedValues = Serialization::GetInstance().GetStoredValues();

	for (ValueAttachedToObject* _valAttached : _serializedValues)
	{
		if (_valAttached->object == currentSelectedActor)
		{
			Array<Component*> _allComponents = currentSelectedActor->GetComponents();

			for (Component* _component : _allComponents)
			{
				string _type = typeid(*_component).name();
				_type = _type.substr(_type.find_first_of(" ") + 1);

				if (!_valAttached->values.contains(_type))
					continue;

				map<string, Array<SerializedValue*>> _values = _valAttached->values;

				SetWindowFontScale(1.2f);
				Text(_type.c_str());
				SetWindowFontScale(1.0f);
				for (SerializedValue* _value : _values[_type])
				{
					if (!DrawFromType(_value))
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
						DrawFromComplexeClass(_serializedValues,_value);
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

void InspectorWidget::DrawFromComplexeClass(Array<ValueAttachedToObject*> _serializedValues,SerializedValue* _value)
{
	for (ValueAttachedToObject* _varAttached : _serializedValues)
	{
		if (_varAttached->object == _value->variable)
		{
			map<string, Array<SerializedValue*>> _values2 = _varAttached->values;
			SetWindowFontScale(1.1f);
			Text(_value->name.c_str());
			SetWindowFontScale(1.0f);
			for (SerializedValue* _value2 : _values2[_value->type])
			{
				DrawFromType(_value2);
			}
		}
	}
}

void InspectorWidget::DrawIntOutput(SerializedValue* _intValue)
{
	int* _var = static_cast<int*>(_intValue->variable);
	string _stingVar = to_string(*_var);
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::InputText(_intValue->name.c_str(), _buffer, 10);
	string _result = _buffer;
	*_var = stoi(_result);
}

void InspectorWidget::DrawFloatOutput(SerializedValue* _floatValue)
{
	float* _var = static_cast<float*>(_floatValue->variable);
	string _stingVar = to_string(*_var);
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::InputText(_floatValue->name.c_str(), _buffer, 10);
	string _result = _buffer;
	*_var = stof(_result);
}

void InspectorWidget::DrawBoolOutput(SerializedValue* _boolValue)
{
	bool* _var = static_cast<bool*>(_boolValue->variable);
	string _stingVar = to_string(*_var);
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::Checkbox(_boolValue->name.c_str(), _var);
}

void InspectorWidget::DrawDoubleOutput(SerializedValue* _doubleValue)
{
	double* _var = static_cast<double*>(_doubleValue->variable);
	string _stingVar = to_string(*_var);
	const char* _temp = _stingVar.c_str();
	char* _buffer = const_cast<char*>(_temp);

	ImGui::InputText(_doubleValue->name.c_str(), _buffer, 10);
	string _result = _buffer;
	*_var = stof(_result);
}
