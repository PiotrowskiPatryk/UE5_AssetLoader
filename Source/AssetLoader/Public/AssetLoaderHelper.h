#pragma once
#include "Engine/AssetManager.h"

class FAssetLoaderHelper
{
public:
	// Template function for loading a soft object asynchronously
	template <typename TObjectType>
	static TFuture<TObjectType*> LoadAsync(TSoftObjectPtr<TObjectType> SoftObjectPointer);

	// Template function for loading a soft class asynchronously
	template <typename TObjectType>
	static TFuture<TSubclassOf<TObjectType>> LoadAsync(TSoftClassPtr<TObjectType> SoftClassPointer);
};

// Implementation of the LoadAsync function for soft object pointers
template <typename TObjectType>
TFuture<TObjectType*> FAssetLoaderHelper::LoadAsync(TSoftObjectPtr<TObjectType> SoftObjectPointer)
{
	TSharedPtr<TPromise<TObjectType*>> Promise = MakeShared<TPromise<TObjectType*>>();
	TFuture<TObjectType*> Future = Promise->GetFuture();

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(SoftObjectPointer.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
		                                   [SoftObjectPointer, Promise]() mutable
		                                   {
			                                   TObjectType* LoadedObject = SoftObjectPointer.Get();
			                                   Promise->SetValue(LoadedObject);
		                                   }));

	return Future;
}

// Implementation of the LoadAsync function for soft class pointers
template <typename TObjectType>
TFuture<TSubclassOf<TObjectType>> FAssetLoaderHelper::LoadAsync(TSoftClassPtr<TObjectType> SoftClassPointer)
{
	TSharedPtr<TPromise<TSubclassOf<TObjectType>>> Promise = MakeShared<TPromise<TSubclassOf<TObjectType>>>();
	TFuture<TSubclassOf<TObjectType>> Future = Promise->GetFuture();

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(SoftClassPointer.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
		                                   [SoftClassPointer, Promise]() mutable
		                                   {
			                                   TSubclassOf<TObjectType> LoadedObject = SoftClassPointer.Get();
			                                   Promise->SetValue(LoadedObject);
		                                   }));

	return Future;
}
