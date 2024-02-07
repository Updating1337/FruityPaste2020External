#pragma once

#include "includes.h"
#include <Windows.h>

#include <iostream>

#define xorstr(str) _(str).c_str()

namespace render
{

	void draw()
	{
		ImDrawList* draw = ImGui::GetBackgroundDrawList();

		for (final_player player : cache.final_player_list)
		{
			ImVec2 size = { (player.bottom.y - player.top.y) / 2,player.bottom.y - player.top.y };
		
			if (cfg.fill_box) drawing.fill_box({ player.top.x - (size.x / 2), player.top.y }, size, ImColor(0.f, 0.f, 0.f, 0.5f));
			if (cfg.tracers) draw->AddLine({ storage.screen_center.x ,storage.screen.y }, { player.top.x, player.top.y }, player.teammate ? ImColor(66, 245, 155) : get_color(cfg.tracers_color));
			//if (cfg.nickname) drawing.text({ player.top.x - (ImGui::CalcTextSize(player.name.c_str()).x / 2), player.top.y - 15.f }, player.teammate ? ImColor(66, 245, 155) : get_color(cfg.nickname_color), player.name.c_str(), false);
			if (cfg.health_bar) drawing.health_bar({ player.top.x - ((size.x / 2) + 3),player.top.y }, size.y, player.health, 100);
			if (cfg.border_box) drawing.border_box({ player.top.x - (size.x / 2), player.top.y }, size, get_color(cfg.border_box_color));
			if (cfg.corner_box) drawing.corner_box({ player.top.x - (size.x / 2), player.top.y }, size, get_color(cfg.corner_box_color));
			if (cfg.skeleton) drawing.draw_bones(player.bones, player.teammate ? ImColor(66, 245, 155) : get_color(cfg.skeleton_color), 1.5f);
			if (cfg.active_weapon) drawing.text({ player.bottom.x - (ImGui::CalcTextSize(player.active_weapon.c_str()).x / 2),player.bottom.y }, get_color(cfg.active_weapon_color), player.active_weapon.c_str(), true);
			
			std::string text = std::string(std::string(_(" [")) + std::to_string((int)player.distance) + _("m] ") + player.name.c_str());
			if (cfg.nickname) drawing.outline_text({ player.top.x - (ImGui::CalcTextSize(text.c_str()).x / 2), player.top.y - 15.f }, get_color(cfg.nickname_color), text.c_str());
		}
		
		if (cfg.drawTC)
		{
			for (final_tool_cupboard tc : cache.final_tool_cupboards)
			{
				std::string text = std::string(std::string(_("Tool Cupboard")) + std::string(_(" [")) + std::to_string((int)tc.distance) + _("]") + (tc.is_decaying ? std::string(_(" (decaying)")) : std::string(_(""))));

				//drawing.shadow_text(ImGui::CalcTextSize(text.c_str()), { tc.position.x - ImGui::CalcTextSize(text.c_str()).x / 2 ,tc.position.y }, ImColor(255, 255, 255), text.c_str());

				drawing.outline_text({ tc.position.x - ImGui::CalcTextSize(text.c_str()).x / 2 ,tc.position.y }, ImColor(cfg.tc_color[0], cfg.tc_color[1], cfg.tc_color[2]), text.c_str());

				for (int i = 0; i < tc.authed_players.size(); i++) {
					drawing.outline_text({ tc.position.x - ImGui::CalcTextSize(tc.authed_players[i].c_str()).x / 2 ,tc.position.y + 20 + (i * 15) }, ImColor(255, 255, 255), tc.authed_players[i].c_str());
				}
			}
		}

		//if (cfg.hotbar)
		//{
		//	ImGuiWindowFlags flags = ui.status ? ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoDecoration;

		//	ImGui::SetNextWindowSize({ 200, 135 }, ImGuiCond_Once);
		//	ImGui::SetNextWindowPos({ 50, 60 }, ImGuiCond_Once);
		//	ImGui::Begin("Player Hotbar", NULL, flags);

		//	ImDrawList* overlay = ImGui::GetOverlayDrawList();

		//	ImVec2 size = ImGui::GetWindowSize();
		//	ImVec2 pos = ImGui::GetWindowPos();

		//	std::vector<Item*> item_list = 
		//}

		if (cfg.radar)
		{

			//Vector2 screenMid = { (float)((p.x + cfg.radarsize) / 2), (float)((p.y + cfg.radarsize) / 2) };

			draw->AddRectFilled(ImVec2(50, 50), ImVec2(50 + cfg.radarsize, 50 + cfg.radarsize), ImColor(45, 50, 54, 100)); //250
			draw->AddRect(ImVec2(50 + 1, 50 + 1), ImVec2(50 + cfg.radarsize, 50 + cfg.radarsize), ImColor(cfg.radar_color[0], cfg.radar_color[1], cfg.radar_color[2]));
			draw->AddCircleFilled(ImVec2((float)(50 + (cfg.radarsize / 2)), (float)(50 + (cfg.radarsize / 2))), 2, ImColor(cfg.radar_color[0], cfg.radar_color[1], cfg.radar_color[2]), 1000); //middle of radar

			for (final_player player : cache.final_player_list)
			{
				draw->AddCircleFilled(ImVec2((float)(player.radarpoint.x), (float)(player.radarpoint.y)), 2, ImColor(255, 0, 0), 1000);
			}		
	
		}

		//drawing.draw_text(10, 125, ImColor(255, 255, 255), "Global Time : %0.00f", cache.time->get_time());

		if (game.completion_percentage > 0.f && cfg.reload_bar)
		{

				std::string reload = std::to_string((int)(game.completion_percentage * 100)) + _("%");
				
				drawing.draw_rectangle_filled(storage.screen_center.x - 50, storage.screen_center.y + 30, 100 * game.completion_percentage, 5, ImColor(255, 0, 0));
				drawing.draw_rectangle(storage.screen_center.x - 50, storage.screen_center.y + 30, 100, 5, ImColor(0, 0, 0), 1.f);
				drawing.draw_text(storage.screen_center.x - ImGui::CalcTextSizeV(reload.c_str()).x / 2, (storage.screen_center.y) - ImGui::CalcTextSizeV(reload.c_str()).y / 2 + 33, ImColor(255, 255, 255), reload.c_str());
		
		}
		
		for (object_info info : cache.final_object_list) drawing.text({ info.pos.x - ImGui::CalcTextSize(info.name.c_str()).x / 2,info.pos.y}, info.color, info.name.c_str(), true);

		for (tracer_info tracer : cache.tracers) draw->AddLine({ tracer.start_point.x,tracer.start_point.y }, { tracer.end_point.x,tracer.end_point.y }, ImColor(cfg.hit_tracers_color[0], cfg.hit_tracers_color[1], cfg.hit_tracers_color[2], cfg.hit_tracersopacity), cfg.hit_tracerthickness);

		if (cfg.fov_circle) draw->AddCircle({ storage.screen_center.x,storage.screen_center.y }, cfg.aimbot_fov, get_color(cfg.fov_circle_color));

		if (cfg.crosshair) drawing.crosshair(get_color(cfg.crosshair_color), 1.f, 5.f, storage.screen_center.x, storage.screen_center.y);

	}
}
