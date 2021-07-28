#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <xaudio2.h>
#include <stdbool.h>
#include "platform.h"


#define FOURCC_RIFF 'FFIR';
#define FOURCC_DATA 'atad';
#define FOURCC_FMT  ' tmf';
#define FOURCC_WAVE 'EVAW';

#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_CHANNELS 2

static WAVEFORMATEX AUDIO_SOURCE_FORMAT = {
  .wFormatTag = WAVE_FORMAT_PCM,
  .nChannels = AUDIO_CHANNELS,
  .nSamplesPerSec = AUDIO_SAMPLE_RATE,
  .nAvgBytesPerSec = 176400,
  .nBlockAlign = 4,
  .wBitsPerSample = 16,
  .cbSize = 0
};

struct PlatformSound {
    WAVEFORMATEXTENSIBLE format;
    DWORD size;
    BYTE* data;
};

typedef struct {
    IXAudio2SourceVoice* voice;
    XAUDIO2_BUFFER buffer;
    bool inUse;
} Channel;

#define MAX_CHANNELS 8
#define MAX_SOUNDS 16

void OnBufferEnd(IXAudio2VoiceCallback* This, void* pBufferContext)    {
    Channel* channel = (Channel*) pBufferContext;
    channel->inUse = false;
}

void OnStreamEnd(IXAudio2VoiceCallback* This) { }
void OnVoiceProcessingPassEnd(IXAudio2VoiceCallback* This) { }
void OnVoiceProcessingPassStart(IXAudio2VoiceCallback* This, UINT32 SamplesRequired) { }
void OnBufferStart(IXAudio2VoiceCallback* This, void* pBufferContext) { }
void OnLoopEnd(IXAudio2VoiceCallback* This, void* pBufferContext) { }
void OnVoiceError(IXAudio2VoiceCallback* This, void* pBufferContext, HRESULT Error) { }

static struct {
    IXAudio2* xaudio;
    IXAudio2MasteringVoice* xaudioMasterVoice;
    Channel channels[MAX_CHANNELS];
    PlatformSound sounds[MAX_SOUNDS];
    size_t numSounds;
    IXAudio2VoiceCallback callbacks;
} audioEngine = {
    .callbacks = {
        .lpVtbl = &(IXAudio2VoiceCallbackVtbl) {
            .OnStreamEnd = OnStreamEnd,
            .OnVoiceProcessingPassEnd = OnVoiceProcessingPassEnd,
            .OnVoiceProcessingPassStart = OnVoiceProcessingPassStart,
            .OnBufferEnd = OnBufferEnd,
            .OnBufferStart = OnBufferStart,
            .OnLoopEnd = OnLoopEnd,
            .OnVoiceError = OnVoiceError
        }
    }
};

bool platform_initAudio(void) {
    HRESULT comResult;
    comResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(comResult)) {
        return false;
    }

    comResult = XAudio2Create(&audioEngine.xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR );

    if (FAILED(comResult)) {
        return false;
    }

    comResult = IXAudio2_CreateMasteringVoice(
        audioEngine.xaudio,
        &audioEngine.xaudioMasterVoice,
        AUDIO_CHANNELS,
        AUDIO_SAMPLE_RATE,
        0,
        NULL,
        NULL,
        AudioCategory_GameEffects
    );

    if (FAILED(comResult)) {
        return false;
    }

    for (int i = 0; i < MAX_CHANNELS; ++i) {
        audioEngine.channels[i].buffer.Flags = XAUDIO2_END_OF_STREAM;
        audioEngine.channels[i].buffer.pContext = audioEngine.channels + i;

        comResult = IXAudio2_CreateSourceVoice(
            audioEngine.xaudio,
            &audioEngine.channels[i].voice,
            &AUDIO_SOURCE_FORMAT,
            0,
            XAUDIO2_DEFAULT_FREQ_RATIO,
            &audioEngine.callbacks,
            NULL,
            NULL
        );

        if (FAILED(comResult)) {
            return false;
        }
    }

    return true;
}

void platform_playSound(PlatformSound* sound) {
    for (int i = 0; i < MAX_CHANNELS; ++i) {
        if (!audioEngine.channels[i].inUse) {
            audioEngine.channels[i].buffer.AudioBytes = sound->size;
            audioEngine.channels[i].buffer.pAudioData = sound->data;
            IXAudio2SourceVoice_Start(audioEngine.channels[i].voice, 0, XAUDIO2_COMMIT_NOW);
            IXAudio2SourceVoice_SubmitSourceBuffer(audioEngine.channels[i].voice, &audioEngine.channels[i].buffer, NULL);
            audioEngine.channels[i].inUse = true;
            break;
        }
    }
}

PlatformSound* platform_loadSound(const char* fileName) {
    HANDLE audioFile = CreateFileA(
      fileName,
      GENERIC_READ,
      FILE_SHARE_READ,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL
    );

    if (audioFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, L"Failed to load audio!", L"FAILURE", MB_OK);
        return NULL;
    }

    if (SetFilePointer(audioFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        MessageBox(NULL, L"Failed to set file pointer!", L"FAILURE", MB_OK);
        return NULL;
    }

    PlatformSound* sound = audioEngine.sounds + audioEngine.numSounds;

    DWORD chunkType;
    DWORD chunkDataSize;
    DWORD fileFormat;

    DWORD offset = 0;
    DWORD bytesRead = 0;

    // TODO(Tarek): This assumes chunk order. It should search for the different chunks.
    // TODO(Tarek): Error checking
    ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);     // RIFF chunk
    ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); // Data size (for all subchunks)
    ReadFile(audioFile, &fileFormat, sizeof(DWORD), &bytesRead, NULL);    // WAVE format
    ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);     // First subchunk (should be 'fmt')
    ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); // Data size for format
    ReadFile(audioFile, &sound->format, chunkDataSize, &bytesRead, NULL); // Wave format struct

    ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);     // Next subchunk (should be 'data')
    ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); // Data size for data

    BYTE* audioData = (BYTE*) malloc(chunkDataSize);
    ReadFile(audioFile, audioData, chunkDataSize, &bytesRead, NULL);      // FINALLY!

    sound->size = chunkDataSize;
    sound->data = audioData;

    CloseHandle(audioFile);

    ++audioEngine.numSounds;
    return sound;
}