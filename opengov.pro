TEMPLATE = subdirs
SUBDIRS = opengov-lib console gui
console.depends = opengov-lib
gui.depends = opengov-lib

 folder_01.source = config
 folder_01.target = ./config
 DEPLOYMENTFOLDERS = folder_01
