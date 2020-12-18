// Gradess Games. All rights reserved.

#include "RadioStationPlaylist.h"
#include "Misc/Paths.h"
#include "Misc/ConfigCacheIni.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogRadio);

TArray<FString> URadioStationPlaylist::GetStreams()
{
	auto Streams = TArray<FString>();
	const auto PathToIni = FPaths::ProjectDir().Append("Radio.ini");
	
	if (!FPaths::FileExists(PathToIni))
	{
		CopyDefaultIniToRoot(PathToIni);
	}
	
	GConfig->GetArray(
		TEXT("RadioStationPlaylist"),
		TEXT("StreamURL"), Streams,
		PathToIni
	);

	return Streams;
}

void URadioStationPlaylist::CopyDefaultIniToRoot(const FString& PathToIni)
{
	const auto PluginIni = FPaths::ProjectPluginsDir().Append("SimpleRadio/Config/Radio.ini");
	auto& FileManager = IFileManager::Get();
	FileManager.Copy(*PathToIni, *PluginIni);
		
	UE_LOG(LogRadio, Warning, TEXT("Couldn't find Radio.ini in game config root. Default Radio.ini will be used"));
}
