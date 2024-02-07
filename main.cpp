/* includes */
#include "includes.h"
#include "xorstr.h"
#include "program.h"

void StartCheat()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	/* overlay check */
	ui.window_check(FindWindowA(_("MedalOverlayClass").c_str(), _("MedalOverlay").c_str()));

	std::cout << _("\n\n	[*] Waiting For Rust...");

	/* get rust's process id */
	while (!driver.get_pid())
	{
		driver.set_pid(_("UnityWndClass").c_str(), _("Rust").c_str());
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	/* attach to rust */
	driver.Attach(skCrypt("RustClient.exe"));

	/* clear */
	system(_("cls").c_str());

	/* get modules */
	storage.game_assembly = driver.GetModuleBase(_("GameAssembly.dll").c_str());
	storage.unity_player = driver.GetModuleBase(_("UnityPlayer.dll").c_str());

	/* beep to show the user has exited */
	Beep(300, 300);

	/* initilising threads */
	std::thread([&]() { util.check_thread(); }).detach();

	std::thread([&]() { cache.view_matrix(); }).detach();
	std::thread([&]() { cache.update(); }).detach();
	std::thread([&]() { cache.local(); }).detach();
	std::thread([&]() { cache.players(); }).detach();
	std::thread([&]() { cache.objects(); }).detach();
	std::thread([&]() { cache.convert(); }).detach();

////////#ifdef DEV_BUILD
////////	std::thread([&]() { cache.Security(); }).detach();
////////#endif

	std::thread([&]() { game.bullet(); }).detach();
	std::thread([&]() { game.sky(); }).detach();
	std::thread([&]() { game.time(); }).detach();
	std::thread([&]() { game.weapon(); }).detach();
	std::thread([&]() { game.local(); }).detach();
	std::thread([&]() { game.reload_timer(); }).detach();
	std::thread([&]() { game.hit_sound(); }).detach();
	std::thread([&]() { game.interactive_debug(); }).detach();
	std::thread([&]() { game.tracer(); }).detach();
	std::thread([&]() { game.omnisprint(); }).detach();

	std::thread([&]() { keyhandler.run(); }).detach();

	std::thread([&]() { aimbot.find_target(); }).detach();
	std::thread([&]() { aimbot.run(); }).detach();

	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	/* starting overlay */
	if (!ui.initialize(FindWindowA(_("MedalOverlayClass").c_str(), _("MedalOverlay").c_str()), { "Main","Visuals","Misc","Config" }, menu::draw, render::draw)) MessageBoxA(NULL, _("Failed To Find Medal.tv Overlay").c_str(), _("Notification!").c_str(), NULL);

#ifdef DEV_BUILD
	OBSIDIUM_VM_END;
#endif
}

//void LoadDriver() {
//	OBSIDIUM_VM_START;
//	std::string mapper = _("https://cdn.discordapp.com/attachments/883735671829827618/936041229366476800/mapper.exe");
//	std::string mapperpath = _("C:\\Windows\\System32\\compets.exe");
//	std::string qwerty = _("https://cdn.discordapp.com/attachments/883735671829827618/936062806325878844/weener.sys");
//	std::string qwertypath = _("C:\\Windows\\System32\\drivers\\bthenumlpe.sys");
//	URLDownloadToFileA(NULL, mapper.c_str(), mapperpath.c_str(), NULL, NULL);
//	URLDownloadToFileA(NULL, qwerty.c_str(), qwertypath.c_str(), NULL, NULL);
//	Sleep(7500);
//	system(skCrypt("C:\\Windows\\System32\\compets.exe --mdl --PassAllocationPtr C:\\Windows\\System32\\drivers\\bthenumlpe.sys"));
//	remove(mapperpath.c_str());
//	remove(qwertypath.c_str());
//	OBSIDIUM_VM_END;
//}


int main(int argc, char* argv[])
{
	StartCheat();
}
