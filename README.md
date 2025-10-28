# My build of dwl - dwm for Wayland

### My personal dwl build - modification and configuration
configure config.h to your liking

My other dotfiles are in https://github.com/ruano1983/dotfiles

![](/misc/1761656709_grim.png)

### Status bar
I use [eww](https://github.com/elkowar/eww) for the status bar, it shows various information such as cpu, temp, ram, disk, wifi, bluetooth, linux ver, volume, date, even kblayout provided by dwl's `kblayout patch`

### Patches applied
1. [cursortheme](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/cursortheme/cursortheme.patch)
2. [autostart](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/autostart/autostart-0.7.patch)
3. [pertag](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/pertag/pertag.patch)
4. [ipc](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/ipc/ipc.patch)
5. [ipctpertag](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/ipc/ipcpertag.patch)
6. [movestack](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/movestack/movestack.patch)
7. [switchtotag](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/switchtotag/switchtotag.patch)
8. [alwayscenter](https://github.com/ruano1983/dwl/blob/main/patches/alwayscenter.patch)
9. [focusdir](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/focusdir/focusdir.patch)
10. [kblayout](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/kblayout/kblayout.patch)

### Building dwl v0.7
dwl has the following dependencies:

    libinput
    wayland
    wlroots0.18 (compiled with the libinput backend)
    xkbcommon
    wayland-protocols (compile-time only)
    pkg-config (compile-time only)

dwl has the following additional dependencies if XWayland support is enabled:

    libxcb
    libxcb-wm
    wlroots0.18 (compiled with X11 support)

To enable XWayland, you should uncomment its flags in `config.mk`.

