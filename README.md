# Noveria Launcher

Fast application launcher for Arch Linux with Hyprland.
Written in C++ with Qt 6.  
It is not trying to be anything else than a launcher.  
Not a calculator.  
Not a dmenu.  
Just the Launcher.

## Screenshots

(WORK IN PROGRESS)

## Requirements

- Arch Linux
- Hyprland
- Qt 6
- CMake 3.16+
- C++17 compatible compiler

## Features

- **Search engine:** Simple but effective sequential fuzzy search by name, generic name, categories and keywords from .desktop files with scoring and penalty system.
- **UI:** Custom item delegate for QListView with hardcoded QSS styling.
- **Customization:** TOML config to make the launcher feel your own. (WORK IN PROGRESS)
- **Keyboard Focused:** Intuitive navigation with arrow keys. Launch your applications with 'Enter'. Close your launcher with 'Esc'.
- **Focus Management:** Proper focus handling keeps the cursor in the search bar to be able to type at any time.
- **layer-shell-qt:** (WORK IN PROGRESS)

## How to build

**Clone the repo:**
```bash
git clone https://github.com/Tojjin/noveria-launcher.git
cd noveria-launcher
```
**Configure and build:**
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
# Optional: Install to system path (required for hyprland shortcuts)
sudo cmake --install build --prefix /usr/local
```

## How to run

**Run:**
```bash
noveria-launcher
```
**Bind to Hyprland shortcut:**
```lua
--Add this to your hyprland.lua config
local mainMod = "SUPER"
hl.bind(mainMod .. " + SPACE", hl.dsp.exec_cmd("noveria-launcher"))
```

## How to use

**Use a keyboard**
- Start typing to search for an application.
- Use up and down arrow keys to navigate in the results.
- Press 'Enter' on a selected application to launch it.
- Press 'Esc' to close the launcher.

**Use a mouse**
- You can also use a mouse to launch an application with left click. 
- Scroll through the results with mouse wheel or by using scroll bar in the launcher.
- Click anywhere on your screen to close the launcher. (WORK IN PROGRESS)

## License

MIT — see [LICENSE](LICENSE) for details.
