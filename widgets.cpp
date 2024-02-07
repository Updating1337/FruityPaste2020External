#include "widgets.h"

void widgets::draw_notifications()
{
	long long time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000;

	ImDrawList* renderer = ImGui::GetBackgroundDrawList();

	for (int i = 0; i < this->notifications.size(); i++)
	{
		notifcation current = this->notifications.at(i);

		if (current.max_time < time)
			renderer->AddText(ImVec2(15, 50 + (i * 20)), IM_COL32(255, 255, 255, 255), current.title);
	}
}

template <typename T> std::string to_string_with_precision(const T a_value)
{
	std::ostringstream out;
	out.precision(2);
	out << std::fixed << a_value;
	return out.str();
}

void widgets::child(const char* name, ImVec2 size, ImVec2 pos)
{
	this->start_point = { pos.x + 5,0.0f };

	this->total_size = pos.y - 25;

	ImDrawList* renderer = ImGui::GetOverlayDrawList();

	ImVec2 window_pos = ImGui::GetWindowPos();

	ImVec2 name_size = ImGui::CalcTextSize(name);

	/*Background*/
	renderer->AddLine(ImVec2(window_pos.x + pos.x + (size.x / 2), window_pos.y + pos.y), ImVec2(window_pos.x + pos.x + (size.x / 2), window_pos.y + pos.y + size.y), style::child_bg, size.x);
	
	/* Accent Line */
	renderer->AddLine(ImVec2(window_pos.x + pos.x, window_pos.y + pos.y + name_size.y + 4), ImVec2(window_pos.x + pos.x + size.x, window_pos.y + pos.y + name_size.y + 4), style::accent, 2.0f);
	
	/* Title */
	renderer->AddText(ImVec2(window_pos.x + pos.x + (size.x / 2) - (name_size.x / 2), window_pos.y + pos.y + (name_size.y / 16)), style::text, name);
	
	/* Border Left*/
	renderer->AddLine(ImVec2(window_pos.x + pos.x, window_pos.y + pos.y), ImVec2(window_pos.x + pos.x, window_pos.y + pos.y + size.y), style::outline, 1.0f);
	
	/* Border Right*/
	renderer->AddLine(ImVec2(window_pos.x + pos.x + size.x, window_pos.y + pos.y), ImVec2(window_pos.x + pos.x + size.x, window_pos.y + pos.y + size.y), style::outline, 1.0f);
	
	/* Border Top*/
	renderer->AddLine(ImVec2(window_pos.x + pos.x, window_pos.y + pos.y), ImVec2(window_pos.x + pos.x + size.x, window_pos.y + pos.y), style::outline, 1.0f);
	
	/* Border Bottom*/
	renderer->AddLine(ImVec2(window_pos.x + pos.x, window_pos.y + pos.y + size.y), ImVec2(window_pos.x + pos.x + size.x, window_pos.y + pos.y + size.y), style::outline, 1.0f);
}

void widgets::slider(const char* label, float* val, float min, float max)
{
	ImGui::PushFont(this->sliderfont);

	ImVec2 pos = ImVec2(this->start_point.x, 65 + this->total_size);

	ImVec2 window_pos = ImGui::GetWindowPos();

	ImGuiSliderFlags flags = ImGuiSliderFlags_None; const char* format = "";

	ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImGuiStyle* style = &ImGui::GetStyle();

	float text_size = ImGui::GetFontSize();
	float width_offset = text_size * 2.1;
	float height_offset = label_size.y + style->FramePadding.y * 1.50f;

	float size = 200 - 15;

	ImGui::PushItemWidth(size);
	ImGui::SetCursorPos(pos);
	std::string new_label = "###" + std::string(label);

	ImVec4* colors = ImGui::GetStyle().Colors;
	ImVec4 Slider = colors[ImGuiCol_SliderGrab];
	ImVec4 grab = colors[ImGuiCol_SliderGrabActive];

	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ImColor(0, 0, 0, 0)));
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(ImColor(0, 0, 0, 0)));

	ImGui::SliderScalar(new_label.c_str(), ImGuiDataType_Float, val, &min, &max, format, flags);

	ImGui::PopFont();

	ImGui::PushStyleColor(ImGuiCol_SliderGrab, grab);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, Slider);

	ImDrawList* renderer = ImGui::GetOverlayDrawList();

	if (ImGui::IsItemHovered())
		renderer->AddLine(ImVec2(pos.x + window_pos.x, (pos.y - label_size.y / 2) + label_size.y + style->FramePadding.y + window_pos.y), ImVec2(pos.x + window_pos.x + size, (pos.y - label_size.y / 2) + label_size.y + style->FramePadding.y + window_pos.y), style::checkbox_hovered, label_size.y + style->FramePadding.y * 1.50f);
	else
		renderer->AddLine(ImVec2(pos.x + window_pos.x, (pos.y - label_size.y / 2) + label_size.y + style->FramePadding.y + window_pos.y), ImVec2(pos.x + window_pos.x + size, (pos.y - label_size.y / 2) + label_size.y + style->FramePadding.y + window_pos.y), style::checkbox_bg, label_size.y + style->FramePadding.y * 1.50f);

	float current = *val;

	renderer->AddLine(ImVec2(pos.x + window_pos.x, (pos.y - label_size.y / 2) + label_size.y + style->FramePadding.y + window_pos.y), ImVec2(pos.x + window_pos.x + (size * (current / max)), (pos.y - label_size.y / 2) + label_size.y + style->FramePadding.y + window_pos.y), style::accent, label_size.y + style->FramePadding.y * 1.50f);

	float y_text = label_size.y;

	/* Outline */
	renderer->AddLine(ImVec2(pos.x + window_pos.x, pos.y + window_pos.y), ImVec2(pos.x + window_pos.x, pos.y + label_size.y + style->FramePadding.y * 2.0 + window_pos.y), style::outline, 2.0f); // Left

	renderer->AddLine(ImVec2(pos.x + window_pos.x, pos.y + window_pos.y), ImVec2(pos.x + size + window_pos.x, pos.y + window_pos.y), style::outline, 2.0f); // Top

	renderer->AddLine(ImVec2(pos.x + size + window_pos.x, pos.y + window_pos.y), ImVec2(pos.x + size + window_pos.x, pos.y + label_size.y + style->FramePadding.y * 2.0 + window_pos.y), style::outline, 2.0f); // Right

	renderer->AddLine(ImVec2(pos.x + window_pos.x, (pos.y + window_pos.y) + label_size.y + style->FramePadding.y * 2.0), ImVec2(pos.x + window_pos.x + size, (pos.y + window_pos.y) + label_size.y + style->FramePadding.y * 2.0), style::outline, 2.0f); // Bottom

	ImGui::PushFont(this->font);

	label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 var_size = ImGui::CalcTextSize(to_string_with_precision<float>(current).c_str(), NULL, true);

	renderer->AddText(ImVec2(window_pos.x + pos.x, window_pos.y + pos.y - label_size.y), style::text, label);
	renderer->AddText(ImVec2(window_pos.x + pos.x + size - var_size.x, window_pos.y + pos.y - var_size.y), style::text, to_string_with_precision<float>(current).c_str());

	ImGui::PopFont();

	this->total_size = this->total_size + 40.0f;
}

void widgets::checkbox(const char* label, bool* state)
{
	ImVec2 location = ImVec2(this->start_point.x, 50 + total_size);

	ImDrawList* renderer = ImGui::GetOverlayDrawList();

	ImVec2 size = ImVec2(15, 15);

	ImGui::SetCursorPos(location);

	ImGuiWindow* window = ImGui::GetCurrentWindow();

	ImVec2 pos = window->DC.CursorPos;

	ImVec2 text_size = ImGui::CalcTextSize(label);

	const ImRect bb(pos, ImVec2(pos.x + size.x + 5 + text_size.x, pos.y + size.y / 2 + (text_size.y / 2)));
	const ImGuiID id = window->GetID(label);

	ImGui::ItemSize(bb, 1);
	ImGui::ItemAdd(bb, id);

	if (ImGui::IsItemClicked())
		*state = !*state;

	if (*state)
		renderer->AddLine(ImVec2(pos.x, pos.y + size.y / 2), ImVec2(pos.x + size.x, pos.y + size.y / 2), style::accent, size.y);

	if (!*state)
		renderer->AddLine(ImVec2(pos.x, pos.y + size.y / 2), ImVec2(pos.x + size.x, pos.y + size.y / 2), style::checkbox_bg, size.y);

	if (ImGui::IsItemHovered() && !*state)
		renderer->AddLine(ImVec2(pos.x, pos.y + size.y / 2), ImVec2(pos.x + size.x, pos.y + size.y / 2), style::checkbox_hovered, size.y);

	/* Top Outline*/
	renderer->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y), style::outline, 2.0f);

	/* Right Outline*/
	renderer->AddLine(ImVec2(pos.x + size.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y), style::outline, 2.0f);

	/* Bottom Outline*/
	renderer->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x + size.x + 0.1, pos.y + size.y), style::outline, 2.0f);

	/* Right Outline*/
	renderer->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y + size.y), style::outline, 2.0f);

	if (!*state)
		renderer->AddText(ImVec2(pos.x + size.x + 5.0f, pos.y + ((size.y / 2) - text_size.y / 2)), style::text_inactive, label);

	if (*state)
		renderer->AddText(ImVec2(pos.x + size.x + 5.0f, pos.y + ((size.y / 2) - text_size.y / 2)), style::text, label);

	this->total_size = this->total_size + size.y + 5;
}

bool ColorPicker(const char* label, float col[3])
{
	static const float HUE_PICKER_WIDTH = 20.0f;
	static const float CROSSHAIR_SIZE = 7.0f;
	static const ImVec2 SV_PICKER_SIZE = ImVec2(180, 200);

	ImColor color(col[0], col[1], col[2]);
	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	ImColor colors[] = { ImColor(255, 0, 0),
		ImColor(255, 255, 0),
		ImColor(0, 255, 0),
		ImColor(0, 255, 255),
		ImColor(0, 0, 255),
		ImColor(255, 0, 255),
		ImColor(255, 0, 0) };

	for (int i = 0; i < 6; ++i)
	{
		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 10, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 10 + HUE_PICKER_WIDTH,
				picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
			colors[i],
			colors[i],
			colors[i + 1],
			colors[i + 1]);
	}

	float hue, saturation, value;
	ImGui::ColorConvertRGBtoHSV(
		color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

	draw_list->AddLine(
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 8, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 12 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImColor(255, 255, 255));

	{
		const int step = 5;
		ImVec2 pos = ImVec2(0, 0);

		ImVec4 c00(1, 1, 1, 1);
		ImVec4 c10(1, 1, 1, 1);
		ImVec4 c01(1, 1, 1, 1);
		ImVec4 c11(1, 1, 1, 1);
		for (int y = 0; y < step; y++) {
			for (int x = 0; x < step; x++) {
				float s0 = (float)x / (float)step;
				float s1 = (float)(x + 1) / (float)step;
				float v0 = 1.0 - (float)(y) / (float)step;
				float v1 = 1.0 - (float)(y + 1) / (float)step;

				ImGui::ColorConvertHSVtoRGB(hue, s0, v0, c00.x, c00.y, c00.z);
				ImGui::ColorConvertHSVtoRGB(hue, s1, v0, c10.x, c10.y, c10.z);
				ImGui::ColorConvertHSVtoRGB(hue, s0, v1, c01.x, c01.y, c01.z);
				ImGui::ColorConvertHSVtoRGB(hue, s1, v1, c11.x, c11.y, c11.z);

				draw_list->AddRectFilledMultiColor(
					ImVec2(picker_pos.x + pos.x, picker_pos.y + pos.y),
					ImVec2(picker_pos.x + pos.x + SV_PICKER_SIZE.x / step, picker_pos.y + pos.y + SV_PICKER_SIZE.y / step),
					ImGui::ColorConvertFloat4ToU32(c00),
					ImGui::ColorConvertFloat4ToU32(c10),
					ImGui::ColorConvertFloat4ToU32(c11),
					ImGui::ColorConvertFloat4ToU32(c01));

				pos.x += SV_PICKER_SIZE.x / step;
			}
			pos.x = 0;
			pos.y += SV_PICKER_SIZE.y / step;
		}
	}

	float x = saturation * SV_PICKER_SIZE.x;
	float y = (1 - value) * SV_PICKER_SIZE.y;
	ImVec2 p(picker_pos.x + x, picker_pos.y + y);
	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(
			ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		/**/ if (mouse_pos_in_canvas.x < 0) mouse_pos_in_canvas.x = 0;
		else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1) mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

		/**/ if (mouse_pos_in_canvas.y < 0) mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1) mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
		saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
		value_changed = true;
	}

	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 10, picker_pos.y));
	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if ((ImGui::IsItemHovered() || ImGui::IsItemActive()) && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(
			ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		/* Previous horizontal bar will represent hue=1 (bottom) as hue=0 (top). Since both colors are red, we clamp at (-2, above edge) to avoid visual continuities */
		/**/ if (mouse_pos_in_canvas.y < 0) mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 2) mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 2;

		hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
		value_changed = true;
	}

	color = ImColor::HSV(hue > 0 ? hue : 1e-6, saturation > 0 ? saturation : 1e-6, value > 0 ? value : 1e-6);
	col[0] = color.Value.x;
	col[1] = color.Value.y;
	col[2] = color.Value.z;
	return value_changed | ImGui::ColorEdit3(label, col);
}

void widgets::color_selector(const char* label, float color[3])
{
	this->item_count++;

	ImVec2 window_pos = ImGui::GetWindowPos();

	ImVec2 location = ImVec2(this->start_point.x + 170, 50 + total_size);

	ImVec2 size = ImVec2(15, 10);

	ImDrawList* renderer = ImGui::GetOverlayDrawList();

	ImU32 final_color = IM_COL32(color[0] * 255, color[1] * 255, color[2] * 255, 255);

	renderer->AddLine(ImVec2(window_pos.x + location.x, window_pos.y + location.y + (size.y / 2)), ImVec2(window_pos.x + location.x + size.x, window_pos.y + location.y + (size.y / 2)), final_color, size.y);

	renderer->AddLine(ImVec2(window_pos.x + location.x, window_pos.y + location.y), ImVec2(window_pos.x + location.x + size.x, window_pos.y + location.y), style::outline, 2.0f);

	renderer->AddLine(ImVec2(window_pos.x + location.x, window_pos.y + location.y), ImVec2(window_pos.x + location.x, window_pos.y + location.y + size.y), style::outline, 2.0f);

	renderer->AddLine(ImVec2(window_pos.x + location.x, window_pos.y + location.y + size.y), ImVec2(window_pos.x + location.x + size.x, window_pos.y + location.y + size.y), style::outline, 2.0f);

	renderer->AddLine(ImVec2(window_pos.x + location.x + size.x, window_pos.y + location.y), ImVec2(window_pos.x + location.x + size.x, window_pos.y + location.y + size.y), style::outline, 2.0f);

	ImGui::SetCursorPos(location);

	ImGuiWindow* window = ImGui::GetCurrentWindow();

	ImVec2 pos = window->DC.CursorPos;

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	const ImGuiID id = window->GetID(label);

	ImGui::ItemSize(bb, 1);
	ImGui::ItemAdd(bb, id);

	if (ImGui::IsItemClicked())
	{
		if (this->enabled_index == item_count)
			this->enabled_index = 0;

		else
		{
			this->enabled_index = item_count;
			this->open = true;
		}
	}

	if (!this->open)
		if (this->enabled_index == item_count)
			this->enabled_index = 0;

	if (this->enabled_index == this->item_count)
	{
		ImGui::Begin("color_window", &this->open, ImGuiWindowFlags_NoDecoration);

		ImVec2 size = ImVec2(250, 250);

		ImGui::SetWindowSize(size);

		ImGui::SetCursorPos(ImVec2(5, 10));
		ColorPicker(label, color);

		ImGui::End();
	}

}

void widgets::combo(std::vector<const char*> list, int* selected)
{
	ImDrawList* draw = ImGui::GetOverlayDrawList();

	ImVec2 location = ImVec2(this->start_point.x , 50 + total_size);
	ImVec2 window_pos = ImGui::GetWindowPos();

	ImVec2 size = ImVec2(15, 10);

	ImGui::SetCursorPos({ location.x + 5,location.y });
	ImGui::Text(_("<").c_str());

	bool left_hovered = ImGui::IsItemHovered();
	bool left_clicked = ImGui::IsItemClicked();

	int list_max = list.size() - 1;
	int list_min = -1;

	int index = *selected;

	/* go down by one */
	if (left_clicked)
	{
		if (index - 1 <= list_min) *selected = list_max;
		else if (index - 1 < list_max) *selected = *selected - 1;
	}

	draw->AddText({ (location.x + window_pos.x) + 5,location.y + window_pos.y }, left_hovered ? ImColor(255, 0, 0) : ImColor(255, 255, 255), _("<").c_str());

	ImGui::SetCursorPos({ location.x + 175,location.y });
	ImGui::Text(_(">").c_str());
	
	bool right_hovered = ImGui::IsItemHovered();
	bool right_clicked = ImGui::IsItemClicked();

	/* go up by one */
	if (right_clicked)
	{
		if (index + 1 > list_max) *selected = 0;
		else if (index + 1 > list_min) *selected = *selected + 1;
	}

	draw->AddText({ (location.x + window_pos.x) + 175,location.y + window_pos.y }, right_hovered ? ImColor(255, 0, 0) : ImColor(255, 255, 255), _(">").c_str());

	const char* current = list[*selected];

	draw->AddText({ (location.x + window_pos.x) + 90 - ImGui::CalcTextSize(current).x / 2.5f,location.y + window_pos.y}, ImColor(255, 255, 255), current);

	this->total_size = this->total_size + ImGui::CalcTextSize(_("i").c_str()).y + 7;
}



void widgets::keybind(const char* key_name, int key_selected)
{
	ImVec2 location = ImVec2(this->start_point.x + 170, 50 + total_size);
	ImVec2 window_pos = ImGui::GetWindowPos();

	ImVec2 size = ImVec2(15, 10);

	ImDrawList* draw = ImGui::GetOverlayDrawList();

	ImGui::SetCursorPos(location);
	ImGui::Text(key_name);

	bool hovered = ImGui::IsItemHovered();
	bool clicked = ImGui::IsItemClicked();

	std::string name = std::string(_("[")) + std::string(key_name) + _("]");

	draw->AddText({ location.x + window_pos.x,location.y + window_pos.y }, hovered ? ImColor(255, 255, 255) : ImColor(1.0f, 1.0f, 1.0f,0.5f), name.c_str());
}

void widgets::spacing(float spacing)
{
	this->total_size += spacing;
}

void widgets::add_notification(const char* title, int time)
{
	long long current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000;

	std::cout << current_time << std::endl;
	std::cout << current_time + time << std::endl;

	notifcation _notification;

	_notification.title = title;
	_notification.max_time = current_time + time;

	this->notifications.push_back(_notification);
}
