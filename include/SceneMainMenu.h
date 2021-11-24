#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H

#include <Scene.h>
#include <Sprite.h>
#include <AnimatedSprite.h>

#ifdef WIN32
#include <xaudio2.h>

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif // WIN32


namespace SceneSystem
{
	class SceneMainMenu final : public Scene
	{
	public:
		SceneMainMenu(const std::string& SceneName, const std::string& sceneFileName);
		~SceneMainMenu();

		void UpdateScene() override;
		void RenderScene() override;

    #ifdef WIN32
		HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);


		WAVEFORMATEXTENSIBLE wfx = { 0 };
		XAUDIO2_BUFFER buffer = { 0 };

		const TCHAR* audioFileName = "D:\\market.wav";
    #endif

	protected:
	#ifdef WIN32
		void OnKeyPressed(System::Key Key) override;
	#endif

	private:
		Shader *mainShader;
    #ifdef WIN32
		IXAudio2* m_XAdudio2 = nullptr;
		IXAudio2MasteringVoice* m_masterVoice = nullptr;
		IXAudio2SourceVoice* m_sourceVoice = nullptr;
    #endif
	};

}
#endif // SCENE_MAIN_MENU_H
