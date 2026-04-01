# Upstream Source — libprojectM

## Library Information

| Field | Value |
|-------|-------|
| **Name** | libprojectM |
| **Version** | 4.1.2 |
| **License** | GNU Lesser General Public License v2.1 (LGPL-2.1) |
| **Upstream Repository** | https://github.com/projectM-visualizer/projectm |
| **Release Tag** | v4.1.2 |
| **Release Tarball** | https://github.com/projectM-visualizer/projectm/archive/refs/tags/v4.1.2.tar.gz |

## Modifications

**None.** libprojectM v4.1.2 is used completely unmodified. It is fetched directly
from the upstream repository during the NDK build using CMake FetchContent.

The only application-specific code is the thin bridge layer in `app/src/main/cpp/`
(see [BUILDING.md](BUILDING.md)), which is the "Application" portion as described
in LGPL-2.1 Section 6.
