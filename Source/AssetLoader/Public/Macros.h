#pragma once
#include "AssetLoaderHelper.h"

/**
 * Macro to asynchronously load a TSoftClassPtr and call a function when the class is loaded.
 *
 * @param SoftClassPtr The soft class pointer to load.
 * @param ClassType The type of the class being loaded.
 * @param FunctionName The name of the function to call when the class is loaded.
 */
#define LOAD_SOFT_CLASS_POINTER_ASYNC(SoftClassPtr, ClassType, FunctionName) \
FAssetLoaderHelper::LoadAsync<ClassType>(SoftClassPtr, [this](const TSubclassOf<ClassType>& LoadedClass) \
{ \
	if (LoadedClass) \
	{ \
		this->FunctionName(LoadedClass); \
	} \
})

/**
 * Macro to asynchronously load a TSoftObjectPtr and call a function when the object is loaded.
 *
 * @param SoftObjectPtr The soft object pointer to load.
 * @param ClassType The type of the object being loaded.
 * @param FunctionName The name of the function to call when the object is loaded.
 */
#define LOAD_SOFT_OBJECT_POINTER_ASYNC(SoftObjectPtr, ClassType, FunctionName) \
FAssetLoaderHelper::LoadAsync<ClassType>(SoftObjectPtr, [this](ClassType* LoadedObject) \
{ \
	if (LoadedObject) \
	{ \
		this->FunctionName(LoadedObject); \
	} \
})