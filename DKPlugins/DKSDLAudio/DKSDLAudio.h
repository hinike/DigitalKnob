//https://gist.github.com/armornick/3447121

#pragma once
#ifndef DKSDLAudio_H
#define DKSDLAudio_H
#include "DK.h"
#include "SDL.h"


///////////////////////////////////////////////
class DKSDLAudio : public DKObjectT<DKSDLAudio>
{
public:
	void Init();
	void End();

	void initAudio();
	void endAudio();
	void playSound(const char * filename, int volume);
	void playMusic(const char * filename, int volume);

	void* PlaySound(void* data);
	void* PlayMusic(void* data);
};


REGISTER_OBJECT(DKSDLAudio, true);

#endif //DKSDLAudio_H

