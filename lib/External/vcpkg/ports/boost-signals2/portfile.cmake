# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/signals2
    REF boost-1.82.0
    SHA512 5452431b482b859e0d334bb6105301f781701a168aef2a2de596ff1c981008b357a53587135bd63ba060c55dea73a69b93a864401dd5cad04d21a5f1499e0533
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})
