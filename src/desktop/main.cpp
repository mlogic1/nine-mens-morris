#include <iostream>
#include <SystemBase.h>
#include <Log.h>
#include <EventManager.h>
#include <SceneManager.h>
#include <SceneMainMenu.h>
#include <Constants.h>

int main()
{
	/* initialize all systems   */

	// System
	if (!System::InitGameEngine())
	{
		Log::Write("Failed to initialize Game system", Log::LogType::ERR);
		return -1;
	}

	System::SYSTEM_PTR->m_sceneManager->SwitchScene(new SceneSystem::SceneMainMenu(STARTING_SCENE, "Scene_Main_Menu.xml"));

	while (System::SYSTEM_PTR->IsRunning())
	{
		System::SYSTEM_PTR->Update();
	}

	return 0;
}
