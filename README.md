# Asset Loader Plugin

The **Asset Loader Plugin** for Unreal Engine 5 provides helper functions to asynchronously load assets using `TSoftObjectPtr` and `TSoftClassPtr`. This plugin is designed to simplify the process of asset loading in a non-blocking manner, making it suitable for projects that require dynamic asset management.

## Features

- **Asynchronous Loading**: Load assets asynchronously to prevent blocking the main game thread.
- **Support for TSoftObjectPtr and TSoftClassPtr**: Easily load both objects and classes.
- **Delegate-Based Callbacks**: Pass your own delegate functions to handle the loaded assets.
- **Macros**: Convenient macros for simplifying the usage of the async loading functions.

## Installation

1. **Download the Plugin**: Clone or download this repository.
2. **Copy to Your Project**: Place the `AssetLoader` plugin folder into the `Plugins` directory of your Unreal Engine project.
3. **Enable the Plugin**: Open your project in Unreal Engine, navigate to the `Plugins` menu, and enable the `Asset Loader Plugin`.

## Usage

### 1. Loading a Soft Object Asynchronously

To load a soft object pointer asynchronously:

```cpp
TSoftObjectPtr<UStaticMesh> MeshPtr = /* your asset pointer */;
LOAD_SOFT_OBJECT_POINTER_ASYNC(MeshPtr, UStaticMesh, OnMeshLoaded);

void YourClass::OnMeshLoaded(UStaticMesh* LoadedMesh)
{
    if (LoadedMesh)
    {
        // Handle the loaded mesh
    }
}
```

### 2. Loading a Soft Class Asynchronously

To load a soft class pointer asynchronously:

```cpp
TSoftClassPtr<YourClassType> ClassPtr = /* your class pointer */;
LOAD_SOFT_CLASS_POINTER_ASYNC(ClassPtr, YourClassType, OnClassLoaded);

void YourClass::OnClassLoaded(TSubclassOf<YourClassType> LoadedClass)
{
    // Handle the loaded class
}
```

### 3. Custom Asynchronous Loading

You can also directly use the helper functions provided:

```cpp
TSoftObjectPtr<USkeletalMesh> SkeletalMeshPtr = /* your skeletal mesh pointer */;
FAssetLoaderHelper::LoadAsync<USkeletalMesh>(SkeletalMeshPtr, [](USkeletalMesh* LoadedMesh)
{
    if (LoadedMesh)
    {
        // Handle the loaded mesh
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load Skeletal Mesh"));
    }
});
```

## Logging

The plugin logs errors and important events using the `LogAssetLoader` category. Ensure your log settings are configured to capture these logs if necessary.

## Contributing

Contributions are welcome! Please submit a pull request or open an issue to discuss any changes or features you'd like to add.
