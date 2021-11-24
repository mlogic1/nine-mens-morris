#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/SystemAndroid.h>
#include <Log.h>
#include <string>
#include <SceneManager.h>
#include "SceneMainMenu.h"

extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidMain(JNIEnv *env, jobject instance)
{
    /* initialize all systems   */
    Log::Write("Starting application | Android", Log::LogType::SUCCESS);

    if (!System::InitGameEngine())
    {
        Log::Write("Failed to initialize system", Log::LogType::ERR);
        return -1;
    }

    System::SYSTEM_PTR->m_sceneManager->SwitchScene(new SceneSystem::SceneMainMenu(STARTING_SCENE, "Scene_Main_Menu.xml"));

    // System
    /*if (!System::InitSystem())
    {
        Log::Write("Failed to initialize system", Log::LogType::ERR);
        return -1;
    }*/

    //EventSystem::InitEventManager();

    //SceneSystem::SceneManager::GetSceneManager()->SwitchScene(new SceneSystem::SceneMainMenu(STARTING_SCENE));

    /*while(System::IsRunning())
    {
        System::update();
    }*/

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_mlogic1_morrisgame_MainActivity_SetAssetManager(JNIEnv *env, jobject thiz, jobject manager)
{
    AAssetManager* assetManager = AAssetManager_fromJava(env, manager);
    //System::SystemAndroid* sysptr = static_cast<System::SystemAndroid*>(System::SYSTEM_PTR);
    //static_cast<System::SystemAndroid*>(System::SYSTEM_PTR)->SetSystemAssetManager(assetManager);
    System::SetSystemAssetManager(assetManager);
}

extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidUpdate(JNIEnv *env, jobject thiz)
{
    System::SYSTEM_PTR->Update();
    return 0;
}