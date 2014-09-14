#ifndef STREAM_H
#define STREAM_H


#include <deque>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>
#include "doubleBuffer.h"
#include "common/message.h"
#include "common/pcmChunk.h"
#include "common/timeUtils.h"
#include "common/queue.h"
#include "common/sampleFormat.h"


class Stream
{
public:
	Stream(const SampleFormat& format);
	void addChunk(PcmChunk* chunk);
	void clearChunks();
	void getPlayerChunk(void* outputBuffer, double outputBufferDacTime, unsigned long framesPerBuffer);
	void setBufferLen(size_t bufferLenMs);
	const SampleFormat& format;

private:
	time_point_ms getNextPlayerChunk(void* outputBuffer, unsigned long framesPerBuffer, int correction = 0);
	time_point_ms getSilentPlayerChunk(void* outputBuffer, unsigned long framesPerBuffer);
	time_point_ms seek(long ms);
//	time_point_ms seekTo(const time_point_ms& to);
	void updateBuffers(int age);
	void resetBuffers();

	SampleFormat format_;

	long lastTick;
	long sleep;
	
	Queue<std::shared_ptr<PcmChunk>> chunks;
	DoubleBuffer<long>* pCardBuffer;
	DoubleBuffer<long>* pMiniBuffer;
	DoubleBuffer<long>* pBuffer;
	DoubleBuffer<long>* pShortBuffer;
	std::shared_ptr<PcmChunk> chunk;

	int median;
	int shortMedian;
	time_t lastUpdate;
	int bufferMs;
};



#endif

