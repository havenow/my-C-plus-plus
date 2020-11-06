#
```
#include <queue>
#include <mutex>
struct FrameCommand {
	FrameCommand() {}
	FrameCommand(std::string cmd, std::string prm) : command(cmd), params(prm) {}

	std::string command;
	std::string params;
};

static std::mutex frameCommandLock;
static std::queue<FrameCommand> frameCommands;

void PushCommand(std::string cmd, std::string param) {
	std::lock_guard<std::mutex> guard(frameCommandLock);
	frameCommands.push(FrameCommand(cmd, param));
}

void UpdateRunLoopAndroid()
{
	std::lock_guard<std::mutex> guard(frameCommandLock);
	while (!frameCommands.empty())
		frameCommands.pop();
}

static void ProcessFrameCommands()
{
	while (!frameCommands.empty()) 
	{
		FrameCommand frameCmd;
		frameCmd = frameCommands.front();
		frameCommands.pop();

		printf("frameCommand '%s' '%s'", frameCmd.command.c_str(), frameCmd.params.c_str());

		/*jstring cmd = env->NewStringUTF(frameCmd.command.c_str());
		jstring param = env->NewStringUTF(frameCmd.params.c_str());
		env->CallVoidMethod(nativeActivity, postCommand, cmd, param);
		env->DeleteLocalRef(cmd);
		env->DeleteLocalRef(param);*/
	}
}

void shutdown()
{
	while (frameCommands.size())
		frameCommands.pop();
}

```
