# LGPL-2.1 Compliance — Profile Equalizer

This repository contains the compliance materials required by the
**GNU Lesser General Public License, Version 2.1 (LGPL-2.1)** for the
use of **libprojectM** in the **Profile Equalizer** Android application.

## Library

| Library | Version | License |
|---------|---------|---------|
| libprojectM | 4.1.2 | LGPL-2.1 |

## Application

**Profile Equalizer** (com.androho.profileequalizer)  
Available on Google Play Store.

## LGPL Compliance

libprojectM is used **unmodified** and compiled from source via CMake FetchContent
during the NDK build. The application-specific integration code (bridge layer) is
contained in this repository.

In accordance with **LGPL-2.1 Section 6(a)**:

- The upstream source of libprojectM is publicly available (see [UPSTREAM.md](UPSTREAM.md))
- Instructions for recompiling the native library are provided (see [BUILDING.md](BUILDING.md))
- The complete LGPL-2.1 license text is included in the app and in this repository

## License

The LGPL-2.1 license text can be found at:  
https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
