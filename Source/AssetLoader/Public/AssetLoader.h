#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Log category for the Asset Loader module.
 */
DECLARE_LOG_CATEGORY_EXTERN(LogAssetLoader, Log, All);

class FAssetLoaderModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
