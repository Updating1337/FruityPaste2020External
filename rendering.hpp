#pragma once
#include "includes.h"
#include "structs.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <math.h>

ImColor get_color(float color[3])
{
	return ImColor(color[0], color[1], color[2]);
}

static enum SIDES
{
	NONE,
	LEFT,
	RIGHT,
};

class rendering_t
{
public:
	void draw_bones(player_bones bones, ImU32 color,float thickness)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		/* upper left */
		{
			/* upper spine -> left shoulder */
			renderer->AddLine({ bones.upper_spine.x - 1.f,bones.upper_spine.y + 1.f }, { bones.left_shoulder.x - 1.f,bones.left_shoulder.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* left shoulder -> left elbow */
			renderer->AddLine({ bones.left_shoulder.x - 1.f,bones.left_shoulder.y + 1.f }, { bones.left_elbow.x - 1.f,bones.left_elbow.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* left elbow -> left wrist*/
			renderer->AddLine({ bones.left_elbow.x - 1.f,bones.left_elbow.y + 1.f }, { bones.left_wrist.x - 1.f,bones.left_wrist.y + 1.f }, ImColor(0, 0, 0), thickness);
		}

		/* upper right */
		{
			/* upper spine -> right shoulder */
			renderer->AddLine({ bones.upper_spine.x - 1.f,bones.upper_spine.y + 1.f }, { bones.right_shoulder.x - 1.f,bones.right_shoulder.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* right shoulder -> right elbow */
			renderer->AddLine({ bones.right_shoulder.x - 1.f,bones.right_shoulder.y + 1.f }, { bones.right_elbow.x - 1.f,bones.right_elbow.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* right elbow -> right wrist*/
			renderer->AddLine({ bones.right_elbow.x - 1.f,bones.right_elbow.y + 1.f }, { bones.right_wrist.x - 1.f,bones.right_wrist.y + 1.f }, ImColor(0, 0, 0), thickness);
		}

		/* connector */
		{
			renderer->AddLine({ bones.upper_spine.x - 1.f,bones.upper_spine.y + 1.f }, { bones.lower_spine.x - 1.f,bones.lower_spine.y + 1.f }, ImColor(0, 0, 0), thickness);
		}

		/* lower left */
		{
			/* lower spine -> left hip */
			renderer->AddLine({ bones.lower_spine.x - 1.f,bones.lower_spine.y + 1.f }, { bones.left_hip.x - 1.f,bones.left_hip.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* left hip -> left knee */
			renderer->AddLine({ bones.left_hip.x - 1.f,bones.left_hip.y + 1.f }, { bones.left_knee.x - 1.f,bones.left_knee.y + 1.f }, ImColor(0, 0, 0), thickness);
		}

		/* lower right */
		{
			/* lower spine -> right hip */
			renderer->AddLine({ bones.lower_spine.x - 1.f,bones.lower_spine.y + 1.f }, { bones.right_hip.x - 1.f,bones.right_hip.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* right hip -> right knee */
			renderer->AddLine({ bones.right_hip.x - 1.f,bones.right_hip.y + 1.f }, { bones.right_knee.x - 1.f,bones.right_knee.y + 1.f }, ImColor(0, 0, 0), thickness);

			/* right knee -> right ankle */
			renderer->AddLine({ bones.right_knee.x - 1.f,bones.right_knee.y + 1.f }, { bones.right_ankle.x - 1.f,bones.right_ankle.y + 1.f }, ImColor(0, 0, 0), thickness);
		}


		//---------------------------------------------------------------------------------------------------------------------------------


		/* upper left */
		{
			/* upper spine -> left shoulder */
			renderer->AddLine({ bones.upper_spine.x,bones.upper_spine.y }, { bones.left_shoulder.x,bones.left_shoulder.y }, color, thickness);

			/* left shoulder -> left elbow */
			renderer->AddLine({ bones.left_shoulder.x,bones.left_shoulder.y }, { bones.left_elbow.x,bones.left_elbow.y }, color, thickness);

			/* left elbow -> left wrist*/
			renderer->AddLine({ bones.left_elbow.x,bones.left_elbow.y }, {bones.left_wrist.x,bones.left_wrist.y}, color, thickness);
		}

		/* upper right */
		{
			/* upper spine -> right shoulder */
			renderer->AddLine({ bones.upper_spine.x,bones.upper_spine.y }, { bones.right_shoulder.x,bones.right_shoulder.y }, color, thickness);

			/* right shoulder -> right elbow */
			renderer->AddLine({ bones.right_shoulder.x,bones.right_shoulder.y }, { bones.right_elbow.x,bones.right_elbow.y }, color, thickness);

			/* right elbow -> right wrist*/
			renderer->AddLine({ bones.right_elbow.x,bones.right_elbow.y }, { bones.right_wrist.x,bones.right_wrist.y }, color, thickness);
		}

		/* connector */
		{
			renderer->AddLine({ bones.upper_spine.x,bones.upper_spine.y }, { bones.lower_spine.x,bones.lower_spine.y }, color, thickness);
		}

		/* lower left */
		{
			/* lower spine -> left hip */
			renderer->AddLine({ bones.lower_spine.x,bones.lower_spine.y }, { bones.left_hip.x,bones.left_hip.y }, color, thickness);
			
			/* left hip -> left knee */
			renderer->AddLine({ bones.left_hip.x,bones.left_hip.y }, { bones.left_knee.x,bones.left_knee.y }, color, thickness);
		}

		/* lower right */
		{
			/* lower spine -> right hip */
			renderer->AddLine({ bones.lower_spine.x,bones.lower_spine.y }, { bones.right_hip.x,bones.right_hip.y }, color, thickness);

			/* right hip -> right knee */
			renderer->AddLine({ bones.right_hip.x,bones.right_hip.y }, { bones.right_knee.x,bones.right_knee.y }, color, thickness);

			/* right knee -> right ankle */
			renderer->AddLine({ bones.right_knee.x,bones.right_knee.y }, { bones.right_ankle.x,bones.right_ankle.y }, color, thickness);
		}
	}

	void text2(ImVec2 v2_pos, std::string str_text, ImVec4 v4_col, bool b_outline, double font_size = 0.f)
	{
		ImGuiContext& g = *GImGui;
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		//const char* text_end = str_text.c_str() + strlen(str_text.c_str());
		//const char* text_display_end = ImGui::FindRenderedTextEnd(str_text.c_str(), text_end);

		if (font_size == 0.f) font_size = g.FontSize;

		if (b_outline) {
			renderer->AddText(g.Font, font_size, v2_pos - ImVec2(1, 0), ImGui::GetColorU32(ImVec4(0, 0, 0, v4_col.w)), str_text.c_str(), NULL, 0.0f, NULL);
			renderer->AddText(g.Font, font_size, v2_pos - ImVec2(0, 1), ImGui::GetColorU32(ImVec4(0, 0, 0, v4_col.w)), str_text.c_str(), NULL, 0.0f, NULL);
			renderer->AddText(g.Font, font_size, v2_pos + ImVec2(1, 0), ImGui::GetColorU32(ImVec4(0, 0, 0, v4_col.w)), str_text.c_str(), NULL, 0.0f, NULL);
			renderer->AddText(g.Font, font_size, v2_pos + ImVec2(0, 1), ImGui::GetColorU32(ImVec4(0, 0, 0, v4_col.w)), str_text.c_str(), NULL, 0.0f, NULL);
		}
		renderer->AddText(g.Font, font_size, v2_pos, ImGui::GetColorU32(v4_col), str_text.c_str(), NULL, 0.0f, NULL);
	}

	void draw_rectangle(float x, float y, float x2, float y2, ImColor color, float thickness)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		renderer->AddRect(ImVec2(x, y), ImVec2(x + x2, y + y2), color, 0, -1, thickness);

		return;
	}

	void draw_text(float x, float y, ImColor color, const char* string, ...)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();


		char buf[512];
		va_list arg_list;

		ZeroMemory(buf, sizeof(buf));

		va_start(arg_list, string);
		vsnprintf(buf, sizeof(buf), string, arg_list);
		va_end(arg_list);

		renderer->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x - 1, y), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);
		renderer->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x + 1, y), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);
		renderer->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y - 1), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);
		renderer->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y + 1), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);

		renderer->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y), color, buf, 0, 0, 0);

		return;
	}

	void draw_rectangle_filled(float x, float y, float x2, float y2, ImColor color)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		renderer->AddRectFilled(ImVec2(x, y), ImVec2(x + x2, y + y2), color);

		return;
	}

	void outline_text(ImVec2 pos, ImColor color, const char* text)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		/* outline */
		renderer->AddText({ pos.x, pos.y - 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x, pos.y + 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x + 1, pos.y }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x - 1, pos.y }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x + 1, pos.y + 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x - 1, pos.y + 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x + 1, pos.y - 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x - 1, pos.y - 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);
		renderer->AddText({ pos.x - 1, pos.y - 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), text);

		/* normal text */
		renderer->AddText({ pos.x,pos.y }, color, text);
	}

	void text(ImVec2 position, ImU32 color, const char* text, bool outline)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		if (outline)
		{
			renderer->AddText(ImVec2(position.x, position.y - 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x, position.y + 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x + 1, position.y), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x - 1, position.y), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x + 1, position.y + 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x - 1, position.y + 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x + 1, position.y - 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x - 1, position.y - 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
			renderer->AddText(ImVec2(position.x - 1, position.y - 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);
		}

		if (!outline) renderer->AddText(ImVec2(position.x + 1, position.y + 1), ImColor(0.f, 0.f, 0.f, 1.0f), text);


		// normal
		renderer->AddText(position, color, text);
	}

	void shadow_text(ImVec2 position, ImVec2 size, ImU32 color, const char* text, float opacity = 1.0f)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		renderer->AddRectFilled({ position.x - 1,position.y }, { position.x + size.x + 1,position.y + size.y }, ImColor(0.f, 0.f, 0.f, 0.5f), 2.0f);

		renderer->AddText(ImVec2(position.x + 1, position.y + 1), ImColor(0.f, 0.f, 0.f, opacity), text);
		renderer->AddText(position, color, text);
	}

	void border_box(ImVec2 position, ImVec2 size, ImU32 color)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		// outline
		renderer->AddRect({ position.x,position.y + 1 }, { position.x + size.x,position.y + size.y + 1 }, ImColor(0.f, 0.f, 0.f, 1.0f), 0);
		renderer->AddRect({ position.x + 1,position.y }, { position.x + size.x + 1,position.y + size.y }, ImColor(0.f, 0.f, 0.f, 1.0f), 0);

		// normal
		renderer->AddRect({ position.x,position.y }, { position.x + size.x,position.y + size.y }, color, 0);
	}

	void draw_line2(float x, float y, float x2, float y2, ImColor color, float thickness)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		if (x < 0)
			return;

		if (y < 0)
			return;

		if (x2 > (float)1920)
			return;

		if (y2 > (float)1080)
			return;

		renderer->AddLine(ImVec2(x, y), ImVec2(x2, y2), color, thickness);
		return;
	}

	void crosshair(ImU32 col, float f_thickness, float len, float xoffset, float yoffset)
	{
		//ImGuiContext& g = *GImGui;
		//ImGuiWindow* window = g.CurrentWindow;

		int CenterX = GetSystemMetrics(0) / 2 - 1;
		int CenterY = GetSystemMetrics(1) / 2 - 1;

		auto color = ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f });
		auto& [width, height] = ImGui::GetIO().DisplaySize;
		draw_line2(width / 2, height / 2 - 9, width / 2, height / 2 + 9, col, 1.f);
		draw_line2(width / 2 - 9, height / 2, width / 2 + 9, height / 2, col, 1.f);

		//rect(ImVec2(CenterX - (len * 2) + xoffset, CenterY + yoffset), ImVec2(len, 1), ImVec4(1.f, 1.f, 1.f, 1.f), 0.5f, true, true);//Left line
		//rect(ImVec2(CenterX + len + xoffset, CenterY + yoffset), ImVec2(len, 1), ImVec4(1.f, 1.f, 1.f, 1.f), 0.5f, true, true);//Right line
		//circle(ImVec2(CenterX, CenterY), 1, ImVec4(0.f, 0.f, 0.f, 1.f), 0.5, true, true);
	}

	void corner_box(ImVec2 pos, ImVec2 size, ImU32 color, float thickness = 1.0f)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		float magic = size.x / 4;

		ImVec2 shadow_pos = ImVec2(pos.x - thickness, pos.y + thickness);

		/* Top Left */
		renderer->AddLine(ImVec2(shadow_pos.x, shadow_pos.y), ImVec2(shadow_pos.x + magic, shadow_pos.y), IM_COL32(0, 0, 0, 255), thickness);
		renderer->AddLine(ImVec2(shadow_pos.x, shadow_pos.y), ImVec2(shadow_pos.x, shadow_pos.y + magic), IM_COL32(0, 0, 0, 255), thickness);

		/* Top Right */
		renderer->AddLine(ImVec2(shadow_pos.x + size.x, shadow_pos.y), ImVec2(shadow_pos.x + size.x - magic, shadow_pos.y), IM_COL32(0, 0, 0, 255), thickness);
		renderer->AddLine(ImVec2(shadow_pos.x + size.x, shadow_pos.y), ImVec2(shadow_pos.x + size.x, shadow_pos.y + magic), IM_COL32(0, 0, 0, 255), thickness);

		/* Bottom Left */
		renderer->AddLine(ImVec2(shadow_pos.x, shadow_pos.y + size.y), ImVec2(shadow_pos.x, shadow_pos.y + size.y - magic), IM_COL32(0, 0, 0, 255), thickness);
		renderer->AddLine(ImVec2(shadow_pos.x, shadow_pos.y + size.y), ImVec2(shadow_pos.x + magic, shadow_pos.y + size.y), IM_COL32(0, 0, 0, 255), thickness);

		/* Bottom Right */
		renderer->AddLine(ImVec2(shadow_pos.x + size.x, shadow_pos.y + size.y), ImVec2(shadow_pos.x + size.x, shadow_pos.y + size.y - magic), IM_COL32(0, 0, 0, 255), thickness);
		renderer->AddLine(ImVec2(shadow_pos.x + size.x, shadow_pos.y + size.y), ImVec2(shadow_pos.x + size.x - magic, shadow_pos.y + size.y), IM_COL32(0, 0, 0, 255), thickness);


		/* Top Left */
		renderer->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + magic, pos.y), color, thickness);
		renderer->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y + magic), color, thickness);

		/* Top Right */
		renderer->AddLine(ImVec2(pos.x + size.x, pos.y), ImVec2(pos.x + size.x - magic, pos.y), color, thickness);
		renderer->AddLine(ImVec2(pos.x + size.x, pos.y), ImVec2(pos.x + size.x, pos.y + magic), color, thickness);

		/* Bottom Left */
		renderer->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x, pos.y + size.y - magic), color, thickness);
		renderer->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x + magic, pos.y + size.y), color, thickness);

		/* Bottom Right */
		renderer->AddLine(ImVec2(pos.x + size.x, pos.y + size.y), ImVec2(pos.x + size.x, pos.y + size.y - magic), color, thickness);
		renderer->AddLine(ImVec2(pos.x + size.x, pos.y + size.y), ImVec2(pos.x + size.x - magic, pos.y + size.y), color, thickness);
	}

	void fill_box(ImVec2 position, ImVec2 size, ImU32 color, float thickness = 1.0f)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		renderer->AddRectFilled({ position.x,position.y }, { position.x + size.x,position.y + size.y }, color, 1.5f);
	}

	void health_bar(ImVec2 pos, float height, float health, float max_health)
	{
		ImDrawList* renderer = ImGui::GetBackgroundDrawList();

		float health_percent = (health / max_health) * 100;

		ImU32 color = ImColor(44, 219, 91);
		if (health_percent < 75) color = ImColor(173, 173, 24);
		if (health_percent < 50) color = ImColor(173, 89, 24);
		if (health_percent < 25) color = ImColor(173, 41, 24);

		renderer->AddRectFilled({ pos.x + 1,pos.y }, { pos.x,pos.y + height }, ImColor(20, 20, 20));
		renderer->AddRect({ pos.x - 1,pos.y }, { pos.x + 1,pos.y + height }, ImColor(0, 0, 0));
		renderer->AddRectFilled({ pos.x + 1,pos.y + (height * (abs((health / max_health) - 1))) }, { pos.x,pos.y + height }, color);
	}

} drawing;