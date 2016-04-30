TEMPLATE = subdirs
SUBDIRS = opengov-lib console gui
console.depends = opengov-lib
gui.depends = opengov-lib
