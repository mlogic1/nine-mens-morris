#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/SystemAndroid.h>
#include <Log.h>
#include <string>
#include <SceneManager.h>
#include "SceneMainMenu.h"

System::SystemAndroid* systemPtr = nullptr;

extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidMain(JNIEnv *env, jobject instance, int width, int height)
{
    /* initialize all systems   */
    Log::Write("Starting application | Android", Log::LogType::SUCCESS);

    if (!System::InitGameEngine())
    {
        Log::Write("Failed to initialize system", Log::LogType::ERR);
        return -1;
    }

    systemPtr = static_cast<System::SystemAndroid*>(System::SYSTEM_PTR);
    systemPtr->SetWindowDimensions(Vector2i{width, height});
    System::SetSystemEnvPointer(env);
    System::SYSTEM_PTR->m_sceneManager->SwitchScene(new SceneSystem::SceneMainMenu(STARTING_SCENE, "Scene_Main_Menu.xml"));
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_mlogic1_morrisgame_MainActivity_SetAssetManager(JNIEnv *env, jobject thiz, jobject manager)
{
    AAssetManager* assetManager = AAssetManager_fromJava(env, manager);
    System::SetSystemAssetManager(assetManager);
}

extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidUpdate(JNIEnv *env, jobject thiz)
{
    System::SYSTEM_PTR->Update();
    return 0;
}
extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidUpdateCursor(JNIEnv *env, jobject thiz, jint x, jint y)
{
    systemPtr->SetCursorPosition(x, y);
    return 0;
}
extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidOnTouchPressed(JNIEnv *env, jobject thiz, jint x, jint y)
{
    systemPtr->OnCursorPressed(x, y);
    return 0;
}
extern "C"
JNIEXPORT jint JNICALL
Java_mlogic1_morrisgame_rendering_CppRenderer_AndroidOnTouchReleased(JNIEnv *env, jobject thiz)
{
    systemPtr->OnCursorReleased();
    return 0;
}