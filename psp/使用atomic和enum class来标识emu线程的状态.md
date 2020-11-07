#
```
#include <atomic>

enum class EmuThreadState {
	DISABLED,
	START_REQUESTED,
	RUNNING,
	QUIT_REQUESTED,
	STOPPED,
};
static std::atomic<int> emuThreadState((int)EmuThreadState::DISABLED);

static void EmuThreadFunc()
{
	emuThreadState = (int)EmuThreadState::RUNNING;
	while (emuThreadState != (int)EmuThreadState::QUIT_REQUESTED) {
		//UpdateRunLoopAndroid(env);
	}
	emuThreadState = (int)EmuThreadState::STOPPED;
}

static void EmuThreadStart() 
{
	printf("EmuThreadStart");
	emuThreadState = (int)EmuThreadState::START_REQUESTED;
	//emuThread = std::thread(&EmuThreadFunc);
}

static void EmuThreadStop() 
{
	printf("EmuThreadStop - stopping...");
	emuThreadState = (int)EmuThreadState::QUIT_REQUESTED;
}

static void EmuThreadJoin() {
	/*emuThread.join();
	emuThread = std::thread();*/
	printf("EmuThreadJoin - joined");
}

```
