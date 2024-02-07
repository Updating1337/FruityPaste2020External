#include "ui.h"

LPDIRECT3D9              g_pD3D = NULL;
LPDIRECT3DDEVICE9        pDevice = NULL;
D3DPRESENT_PARAMETERS    g_d3dpp = {};

HWND _window = NULL;

void user_interface::input_handling(bool* status)
{
	bool left = false;

	for (;;)
	{
		if (GetAsyncKeyState(VK_INSERT) & 0x1)
		{
			if (GetForegroundWindow() == FindWindowA(_("UnityWndClass").c_str(), _("Rust").c_str()) || GetForegroundWindow() == _window)
			{
				*status = !*status;

				if (*status) has_opened = true;

				this->set_window_active(_window);
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON)) left = true;
		else left = false;

		ImGuiIO& io = ImGui::GetIO();

		if (left) io.MouseDown[0] = true;

		if (!left)
		{
			io.MouseDown[0] = false;
			io.MouseReleased[0] = true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void user_interface::set_window_active(HWND window)
{
	/* getting current window style */
	long style = GetWindowLong(window, GWL_EXSTYLE);

	if (status)
	{
		/* remove ex layered allowing us to click */
		style &= ~WS_EX_LAYERED;
		SetWindowLong(window, -20, style);

		HWND hForeground = GetForegroundWindow();

		// attaching input from our cheat to current foreground window
		int curThread = GetCurrentThreadId();
		int remoteThread = GetWindowThreadProcessId(hForeground, 0);
		AttachThreadInput(curThread, remoteThread, TRUE);

		/* making sure window is showing */
		ShowWindow(window, SW_SHOWDEFAULT);
		BringWindowToTop(window);

		while (!SetForegroundWindow(window)) std::this_thread::sleep_for(std::chrono::milliseconds(1));

		/* deataching from current windows input */
		AttachThreadInput(curThread, remoteThread, FALSE);
	}

	if (!status)
	{
		style |= WS_EX_LAYERED;
		SetWindowLong(window, -20, style);
		while (!SetForegroundWindow(FindWindowA("UnityWndClass", "Rust"))) std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

bool create_dx9_device()
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	/* check to see if created the template successfully */
	if (!g_pD3D) return false;

	/* configuring the device to how we want it */
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.hDeviceWindow = _window;
	g_d3dpp.FullScreen_RefreshRateInHz = 0;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	g_d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;

	/* creating the device with the desired configuration */
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &pDevice) < 0) return false;

	return true;
}

void user_interface::window_check(HWND window)
{
	if (!window)
	{
		printf(_("Please Install Medal.tv\n").c_str());
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		exit(0);
	}
}

bool user_interface::initialize(HWND window, std::vector<const char*> tabs, function_callback menu, function_callback draw)
{
	if (window != NULL) _window = window;

	/* changing the window to what we want it to be for our overlay*/
	SetWindowPos(window, NULL, 0, 0, GetDeviceCaps(GetWindowDC(NULL), HORZRES), GetDeviceCaps(GetWindowDC(NULL), VERTRES), SWP_FRAMECHANGED);
	SetWindowPos(window, NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0);
	SetWindowLongA(window, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

	/* extending the window to the screen size */
	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(window, &margin);

	/* making sure the window is showing */
	ShowWindow(window, SW_SHOW);

	/* creating device */
	if (!create_dx9_device()) return false;

	/* setting window opacity */
	SetLayeredWindowAttributes(window, 0x000001, 0xFF, 0x02);

	/* create imgui context and init imgui using DX9 */
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
	ImGui::StyleColorsDark();

	ImGuiStyle* _style = &ImGui::GetStyle();
	_style->WindowRounding = 1.0f;
	_style->ChildRounding = 0.0f;
	_style->FrameRounding = 0.0f;
	_style->GrabRounding = 0.0f;
	_style->FramePadding = ImVec2(2, 2);
	_style->PopupRounding = 0.0f;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.24f, 0.24f, 0.24f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.35f, 0.35f, 0.35f, 1.0f));

	/* ready to handle input */
	std::thread([&]() { input_handling(&status); }).detach();

	bool is_open = true;

	ImFont* verdana = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&verdana_font, sizeof(verdana_font), 14.f);
	ImFont* aharoni = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&aharoni_font, sizeof(aharoni_font), 22.5f);
	ImFont* segoe_large = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(segoeui_font, sizeof(segoeui_font), 21.f);
	ImFont* segoe = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(segoeui_font, sizeof(segoeui_font), 16.f);
	this->smallest = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&verdana_font, sizeof(verdana_font), 12);
	this->slidersmall = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&verdana_font, sizeof(verdana_font), 8.f);

	while (true)
	{
		if (!is_open) this->safe_exit();

		this->begin_scene();

		if (GetForegroundWindow() == FindWindowA(_("UnityWndClass").c_str(), _("Rust").c_str()) || GetForegroundWindow() == _window) draw();

		if (status)
		{
			if (GetForegroundWindow() == FindWindowA(_("UnityWndClass").c_str(), _("Rust").c_str()) || GetForegroundWindow() == _window)
			{
				ImGui::Begin(_("Fruityskills").c_str(), &is_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings);

				ImGui::SetWindowSize(ImVec2(610, 500));

				ImDrawList* renderer = ImGui::GetOverlayDrawList();

				ImVec2 pos = ImGui::GetWindowPos();
				ImVec2 size = ImGui::GetWindowSize();

				/* Background / Nav Bar */
				renderer->AddLine(ImVec2(pos.x, pos.y + size.y / 2), ImVec2(pos.x + size.x, pos.y + size.y / 2), style::window_bg, size.y);
				renderer->AddLine(ImVec2(pos.x + 75, pos.y), ImVec2(pos.x + 75, pos.y + size.y), style::nav_bg, 150);

				/* Water Mark */
				ImGui::PushFont(aharoni);
					
				renderer->AddText(ImVec2(pos.x + 17, pos.y + 15), style::header_text, _("Fruityskills").c_str());
				//renderer->AddText(ImVec2(pos.x + 17 + ImGui::CalcTextSize(_("Fruityskills").c_str()).x, pos.y + 15), style::accent, _(".com").c_str());
				renderer->AddLine(ImVec2(pos.x, pos.y + 50), ImVec2(pos.x + 150, pos.y + 50), style::window_bg, 1.0f);

				ImGui::PopFont();

				ImGui::PushFont(segoe_large);

				for (int i = 0; i < tabs.size(); i++)
				{
					if (i != this->selected_tab)
					{
						ImVec2 position = ImVec2(pos.x + 25, pos.y + 70 + (i * 30));

						renderer->AddText(position, style::text_inactive, tabs.at(i));

						ImGui::SetCursorPos(ImVec2(25, 70 + (i * 30)));
						ImGui::Text(tabs.at(i));

						if (ImGui::IsItemClicked()) this->selected_tab = i;
						if (ImGui::IsItemHovered()) renderer->AddText(position, IM_COL32(183, 0, 255, 40), tabs.at(i));
					}
					else
						renderer->AddText(ImVec2(pos.x + 25, pos.y + 70 + (i * 30)), style::accent, tabs.at(i));
				}

				ImGui::PopFont();

				ImGui::PushFont(segoe);

				menu();

				ImGui::End();
			}
		}

		this->end_scene();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void user_interface::begin_scene()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	pDevice->BeginScene();
}

void user_interface::end_scene()
{
	ImGui::EndFrame();

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 0.0f, 0);

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	pDevice->EndScene();

	HRESULT result = pDevice->Present(NULL, NULL, NULL, NULL);
}

void user_interface::safe_exit()
{
	this->begin_scene();
	this->end_scene();

	status = false;

	this->set_window_active(_window);
	exit(0);

}
