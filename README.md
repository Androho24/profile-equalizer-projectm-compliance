# Profile Equalizer – projectM integration materials

This repository contains source and license materials related to the
projectM integration used in the Android app **Profile Equalizer**
Packages:
- `com.androho.profileequalizer`
- `com.androho.profileequalizerpro`

## Purpose

The purpose of this repository is to document the use of **libprojectM**
in Profile Equalizer and to provide the projectM-related integration and
license materials in a separate public repository.

This repository is focused on the projectM integration only.
It is **not** the full source code repository of the complete Android app.

## Application

- **App name:** Profile Equalizer
- **Package:** `com.androho.profileequalizer`
- **Developer:** Androho Software

## Third-party library

- **Library:** libprojectM
- **Version used:** 4.1.2
- **License:** LGPL-2.1

## Upstream source

The upstream projectM source used for this integration is documented in
[`UPSTREAM.md`](./UPSTREAM.md).

## Local modifications

At the time of publishing this repository, **no local modifications to
libprojectM itself** are documented here.

The application-specific integration code contained in this repository
covers only the bridge/build layer used to connect the Android app to
libprojectM.

## Included in this repository

This repository may include, depending on the integration state:

- build configuration files related to projectM integration
- native bridge code
- Kotlin bridge code
- notes about the upstream source version used
- build notes
- third-party notices
- a copy of the LGPL-2.1 license text

## Build notes

Information about rebuilding the projectM-related native integration is
provided in [`BUILDING.md`](./BUILDING.md).

## License information

A copy of the GNU Lesser General Public License v2.1 is included in this
repository:

- [`license_lgpl21.txt`](./license_lgpl21.txt)

## Notes

This repository is intended to make the projectM-related materials easier
to review and reference separately from the private main application
repository.

For the exact upstream reference used by this integration, see
[`UPSTREAM.md`](./UPSTREAM.md).
