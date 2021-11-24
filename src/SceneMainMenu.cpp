
#include "SceneMainMenu.h"
#include <Log.h>
#include <stb_image.h>
#include <list>
#include <SystemBase.h>

//#include <oboe/AudioStreamBuilder.h>

namespace SceneSystem
{
	SceneMainMenu::SceneMainMenu(const std::string& sceneName, const std::string& sceneFileName) : Scene(sceneName, sceneFileName)
	{
		try
		{
			mainShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("StandardShader");

			Rect bgRect = { 0, 0, 1280, 720 };
			Rect spriteRect = { 650, 630, 632, 84 };
			Rect fontRect = {0, 0, 100, 40};
            //InstantiateSprite(bgRect, System::SYSTEM_PTR->GetTextureManager()->GetTexture("background"));
			InstantiateSprite("logothing", spriteRect, System::SYSTEM_PTR->GetTextureManager()->GetTexture("logo"));
			InstantiateFontObject("fontthing", fontRect, "Game Engine Test Scene");
		}
		catch (std::string err)
		{
			Log::Write(err, Log::LogType::ERR);
		}
/*
    #ifdef WIN32
		Log::Write("Init sound");

		HRESULT hr;
		if (FAILED(hr = XAudio2Create(&m_XAdudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		{
			Log::Write("Init sound failed");
		}

		if (FAILED(hr = m_XAdudio2->CreateMasteringVoice(&m_masterVoice)))
		{
			Log::Write("Mastering voice Init sound failed");
		}

		HANDLE hFile = CreateFile(audioFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (INVALID_HANDLE_VALUE == hFile)
			HRESULT_FROM_WIN32(GetLastError());

		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
			HRESULT_FROM_WIN32(GetLastError());

		DWORD dwChunkSize;
		DWORD dwChunkPosition;

		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		DWORD fileType;
		ReadChunkData(hFile, &fileType, sizeof(DWORD), dwChunkPosition);

		if (fileType != fourccWAVE)
			int x = S_FALSE;

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);


		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		BYTE* pDataBuffer = new BYTE[dwChunkSize];
		ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

		buffer.AudioBytes = dwChunkSize;
		buffer.pAudioData = pDataBuffer;
		buffer.Flags = XAUDIO2_END_OF_STREAM;

		hr = m_XAdudio2->CreateSourceVoice(&m_sourceVoice, (WAVEFORMATEX*)&wfx);

		m_sourceVoice->SubmitSourceBuffer(&buffer);

		//m_sourceVoice->Start();
    #endif // WIN32
		*/
	}

	SceneMainMenu::~SceneMainMenu()
	{
	}

	void SceneMainMenu::UpdateScene()
	{
		glm::mat4 cameraProjection = m_gameCamera->getProjection();
		glm::mat4 cameraView = m_gameCamera->getMatrixView();

		mainShader->setMat4("projection", cameraProjection);
		mainShader->setMat4("view", cameraView);

		glm::mat4 model1 = glm::mat4(1.0f);
		glm::vec3 modelPositionTranslate1 = glm::vec3(4.1f, 0.1f, -2.5f);
		glm::vec3 modelPositionRotate1 = glm::vec3(0.0f, 1.0f, 0.75f);
		mainShader->setMat4("model", model1);

		float deltaTime = System::SYSTEM_PTR->GetDeltaTime();
		int FPS = System::SYSTEM_PTR->GetFPS();
		//Log::Write("delta: " + std::to_string(deltaTime));
        Engine::TextObject* obj = static_cast<Engine::TextObject*>(GetSceneObject("test_text"));
        obj->SetText(std::to_string(deltaTime));

		Engine::TextObject* objFPS = static_cast<Engine::TextObject*>(GetSceneObject("fps_text"));
		objFPS->SetText(std::string("FPS:") + std::to_string(FPS));


		Vector2f cursorPos = System::SYSTEM_PTR->GetCursorPosition();
		//Vector2i cursorPos = System::SYSTEM_PTR->GetViewportDimensions();
		std::string maus = "X: ";
		maus += std::to_string(cursorPos.x);
		maus += " Y: ";
		maus += std::to_string(cursorPos.y);
		objFPS->SetText(maus);
	}

	void SceneMainMenu::RenderScene()
	{
		// 2D - ortho sprites
		glDisable(GL_DEPTH_TEST);

		// 3D - projection sprites
		//glEnable(GL_DEPTH_TEST);
	}

#ifdef WIN32
	HRESULT SceneMainMenu::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());

		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (hr == S_OK)
		{
			DWORD dwRead;
			if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());

			if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());

			switch (dwChunkType)
			{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
					hr = HRESULT_FROM_WIN32(GetLastError());
				break;

			default:
				if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
					return HRESULT_FROM_WIN32(GetLastError());
			}

			dwOffset += sizeof(DWORD) * 2;

			if (dwChunkType == fourcc)
			{
				dwChunkSize = dwChunkDataSize;
				dwChunkDataPosition = dwOffset;
				return S_OK;
			}

			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRIFFDataSize) return S_FALSE;

		}

		return S_OK;

	}

	HRESULT SceneMainMenu::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());
		DWORD dwRead;
		if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}
	
	#ifdef WIN32
	void SceneMainMenu::OnKeyPressed(System::Key Key)
	{
		Engine::AnimatedSprite* object = static_cast<Engine::AnimatedSprite*>(GetSceneObject("animation_sprite"));
		if (Key == System::Key::Num1)
		{
			object->PauseSpriteAnimation();
		}
		
		if (Key == System::Key::Num2)
		{
			object->ResumeSpriteAnimation();
		}

		if (Key == System::Key::Num3)
		{
			object->ResetSpriteAnimation();
		}
	}
	#endif
#endif // WIN32
}
