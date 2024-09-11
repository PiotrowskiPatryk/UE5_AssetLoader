
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]


## [0.0.3] - 2024-09-11

### Added

- Implemented additional validation checks for `TSoftObjectPtr` and `TSoftClassPtr` using `IsValid()` to ensure pointers are valid before attempting to load assets.
- Introduced detailed logging for invalid pointers, including the type of the asset in the log message for easier debugging.

### Changed

- Optimized asset loading functions by checking if assets are already loaded in memory before initiating asynchronous loading. If assets are already loaded, `TFuture` promises or delegate callbacks are immediately fulfilled, improving performance.
- Enhanced error handling in asynchronous loading functions, with clear and informative log messages detailing the asset type and name when loading fails.
- Added early `return` statements after handling invalid pointers to prevent further execution of loading operations.

### Fixed

- Resolved an issue where `TSubclassOf<TObjectType>` was incorrectly handled in `LoadAsync` methods for `TSoftObjectPtr`. The lambda functions were adjusted to correctly match the expected type and prevent potential type mismatch errors.
- Resolved an issue where asset loading functions could proceed with invalid pointers, potentially leading to undefined behavior or crashes.

## [0.0.2] - 2024-09-02

### Changed

- Updated repository url for version changes.
- Updated `LOAD_SOFT_CLASS_POINTER_ASYNC` and `LOAD_SOFT_OBJECT_POINTER_ASYNC` macros to allow handling of null values directly in user-defined callback functions. This change provides more control over error handling when assets fail to load.

## [0.0.1] - 2024-09-01

### Added

- Initial release of the `Asset Loader Plugin`.
- Asynchronous loading support for `TSoftObjectPtr` and `TSoftClassPtr`.
- Macros for simplifying the usage of the async loading functions.
- Delegate-based callbacks for handling loaded assets.

[unreleased]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/compare/v0.0.3...main
[0.0.3]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/releases/tag/v0.0.3
[0.0.2]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/releases/tag/v0.0.2
[0.0.1]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/releases/tag/v0.0.1