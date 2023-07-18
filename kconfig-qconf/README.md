# kconfig-qconf

Linux kernel configuration system (Kconfig) graphical configurator based on
Qt.

# Development

Example initialization using system-installed Qt on Debian and Fedora (or
alike):

```
cd kconfig
bdep init --empty
bdep config create @gcc ../kconfig-gcc cc
bdep init @gcc -d liblkc -d kconfig-conf   # Answer Y to host config.
bdep init @gcc -d kconfig-qconf ?sys:Qt6Moc ?sys:libQt6Core ?sys:libQt6Gui ?sys:libQt6Widgets config.Qt6Moc=/usr/lib/qt6/libexec/moc
bdep init @gcc -d kconfig-qconf ?sys:Qt5Moc ?sys:libQt5Core ?sys:libQt5Gui ?sys:libQt5Widgets config.Qt5Moc=/usr/lib/qt5/bin/moc config.cxx.coptions+=-fPIC config.kconfig_qconf.qt=5
```
