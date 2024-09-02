#pragma once

/**
 * Macro to asynchronously load a TSoftClassPtr and call a function when the class is loaded.
 * 
 * The callback function will receive a `nullptr` if the class fails to load.
 *
 * @param SoftClassPtr The soft class pointer to load.
 * @param ClassType The type of the class being loaded.
 * @param FunctionName The name of the function to call when the class is loaded. The function should handle the case where the loaded class is `nullptr`.
 */
#define LOAD_SOFT_CLASS_POINTER_ASYNC(SoftClassPtr, ClassType, FunctionName) \
FAssetLoaderHelper::LoadAsync<ClassType>(SoftClassPtr, [this](const TSubclassOf<ClassType>& LoadedClass) \
{ \
	this->FunctionName(LoadedClass); \
})

/**
 * Macro to asynchronously load a TSoftObjectPtr and call a function when the object is loaded.
 * 
 * The callback function will receive a `nullptr` if the object fails to load.
 *
 * @param SoftObjectPtr The soft object pointer to load.
 * @param ClassType The type of the object being loaded.
 * @param FunctionName The name of the function to call when the object is loaded. The function should handle the case where the loaded object is `nullptr`.
 */
#define LOAD_SOFT_OBJECT_POINTER_ASYNC(SoftObjectPtr, ClassType, FunctionName) \
FAssetLoaderHelper::LoadAsync<ClassType>(SoftObjectPtr, [this](ClassType* LoadedObject) \
{ \
	this->FunctionName(LoadedObject); \
})