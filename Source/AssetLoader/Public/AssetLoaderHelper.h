#pragma once
#include "AssetLoader.h"
#include "Engine/AssetManager.h"
#include "Logging/StructuredLog.h"

/**
 * Helper class for asynchronously loading assets using TSoftObjectPtr and TSoftClassPtr.
 */
class FAssetLoaderHelper
{
public:
	/**
	 * Asynchronously loads a TSoftObjectPtr and returns a future of the loaded object.
	 *
	 * @tparam TObjectType The type of the object being loaded.
	 * @param SoftObjectPointer The soft object pointer to the asset.
	 * @return TFuture<TObjectType*> A future object pointing to the loaded asset.
	 */
	template <typename TObjectType>
	static TFuture<TObjectType*> LoadAsync(TSoftObjectPtr<TObjectType> SoftObjectPointer);

	/**
	 * Asynchronously loads a TSoftClassPtr and returns a future of the loaded class.
	 *
	 * @tparam TObjectType The type of the class being loaded.
	 * @param SoftClassPointer The soft class pointer to the asset.
	 * @return TFuture<TSubclassOf<TObjectType>> A future object pointing to the loaded class.
	 */
	template <typename TObjectType>
	static TFuture<TSubclassOf<TObjectType>> LoadAsync(TSoftClassPtr<TObjectType> SoftClassPointer);

	/**
	 * Asynchronously loads a TSoftObjectPtr and triggers the provided delegate upon completion.
	 *
	 * @tparam TObjectType The type of the object being loaded.
	 * @param SoftObjectPointer The soft object pointer to the asset.
	 * @param LoadedDelegate The delegate to call once the asset is loaded. The delegate receives a pointer to the loaded object or nullptr if loading fails.
	 */
	template <typename TObjectType>
	static void LoadAsync(TSoftObjectPtr<TObjectType> SoftObjectPointer, TFunction<void(TObjectType*)> LoadedDelegate);

	/**
	 * Asynchronously loads a TSoftClassPtr and triggers the provided delegate upon completion.
	 *
	 * @tparam TObjectType The type of the class being loaded.
	 * @param SoftClassPointer The soft class pointer to the asset.
	 * @param LoadedDelegate The delegate to call once the class is loaded. The delegate receives a subclass pointer to the loaded class or nullptr if loading fails.
	 */
	template <typename TObjectType>
	static void LoadAsync(TSoftClassPtr<TObjectType> SoftClassPointer,
	                      TFunction<void(TSubclassOf<TObjectType>)> LoadedDelegate);
};

template <typename TObjectType>
TFuture<TObjectType*> FAssetLoaderHelper::LoadAsync(TSoftObjectPtr<TObjectType> SoftObjectPointer)
{
	TSharedPtr<TPromise<TObjectType*>> Promise = MakeShared<TPromise<TObjectType*>>();
	TFuture<TObjectType*> Future = Promise->GetFuture();

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(
		SoftObjectPointer.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[SoftObjectPointer, Promise]() mutable
			{
				if (TObjectType* LoadedObject = SoftObjectPointer.Get())
				{
					Promise->SetValue(LoadedObject);
				}
				else
				{
					UE_LOGFMT(LogAssetLoader, Error, "Failed to load asset of type `{AssetType}`: `{AssetName}`",
					          *TObjectType::StaticClass()->GetName(), *SoftObjectPointer.ToString());
					Promise->SetValue(nullptr);
				}
			}));

	return Future;
}

template <typename TObjectType>
TFuture<TSubclassOf<TObjectType>> FAssetLoaderHelper::LoadAsync(TSoftClassPtr<TObjectType> SoftClassPointer)
{
	TSharedPtr<TPromise<TSubclassOf<TObjectType>>> Promise = MakeShared<TPromise<TSubclassOf<TObjectType>>>();
	TFuture<TSubclassOf<TObjectType>> Future = Promise->GetFuture();

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(
		SoftClassPointer.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[SoftClassPointer, Promise]() mutable
			{
				if (TSubclassOf<TObjectType> LoadedObject = SoftClassPointer.Get())
				{
					Promise->SetValue(LoadedObject);
				}
				else
				{
					UE_LOGFMT(LogAssetLoader, Error, "Failed to load asset of type `{AssetType}`: `{AssetName}`",
					          *TObjectType::StaticClass()->GetName(), *SoftClassPointer.ToString());
					Promise->SetValue(nullptr);
				}
			}));

	return Future;
}

template <typename TObjectType>
void FAssetLoaderHelper::LoadAsync(TSoftObjectPtr<TObjectType> SoftObjectPointer,
                                   TFunction<void(TObjectType*)> LoadedDelegate)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(
		SoftObjectPointer.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[SoftObjectPointer, LoadedDelegate]() mutable
			{
				if (TSubclassOf<TObjectType> LoadedObject = SoftObjectPointer.Get())
				{
					LoadedDelegate(LoadedObject);
				}
				else
				{
					UE_LOGFMT(LogAssetLoader, Error, "Failed to load asset of type `{AssetType}`: `{AssetName}`",
					          *TObjectType::StaticClass()->GetName(), *SoftObjectPointer.ToString());
					LoadedDelegate(nullptr);
				}
			})
	);
}

template <typename TObjectType>
void FAssetLoaderHelper::LoadAsync(TSoftClassPtr<TObjectType> SoftClassPointer,
                                   TFunction<void(TSubclassOf<TObjectType>)> LoadedDelegate)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(
		SoftClassPointer.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[SoftClassPointer, LoadedDelegate]() mutable
			{
				if (TSubclassOf<TObjectType> LoadedClass = SoftClassPointer.Get())
				{
					LoadedDelegate(LoadedClass);
				}
				else
				{
					UE_LOGFMT(LogAssetLoader, Error, "Failed to load asset of type `{AssetType}`: `{AssetName}`",
					          *TObjectType::StaticClass()->GetName(), *SoftClassPointer.ToString());
					LoadedDelegate(nullptr);
				}
			})
	);
}
