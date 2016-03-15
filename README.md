Main Terminal Windows GOTO (mtwg)
=================================

### Description
Main Terminal Windows GOTO (mtwg) enables you to map custom keyboard shortcuts to your most used X windows. mtwg is licensed under GPLv3.

mtwg is tested on Gnome Shell 3.18.

Project home page: 

### Version
0.8.0

### Contributors
Espen Hovind (creator, maintainer)

### Installation
Clone this repository and install dependencies.

### Dependencies
- Gnome 3
- libwnck3-devel
- glib-devel

### Compilation
make && sudo make install

### Usage

##### Prerequisites
mtwg requires that you have pre-defined 2 custom keyboard shortcuts (/custom0/ and /custom1/)

1. Open: gnome-control-center keyboard
2. Select "Custom Shortcuts"
3. Add shortcut 1:
    Name: remote
    Command: <empty>
    Click on "disabled" and set new accelerator
4. Add shortcut 2:
    Name: code
    Command: <empty>
    Click on "disabled" and set new accelerator

Warning: If you have already defined 2 shortcuts, mtwg will overwrite your <command> value. You can define different custom shortcuts by editing: PATH_REMOTE and PATH_CODE in src/mtwg_gsettings.h

##### Register key bindings
Run: mtwg -h
