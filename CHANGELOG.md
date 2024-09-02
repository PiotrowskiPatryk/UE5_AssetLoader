
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

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

[unreleased]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/compare/v0.0.2...main
[0.0.2]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/releases/tag/v0.0.2
[0.0.1]: https://github.com/PiotrowskiPatryk/UE5_AssetLoader/releases/tag/v0.0.1