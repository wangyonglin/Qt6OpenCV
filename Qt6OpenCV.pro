TEMPLATE = subdirs

 SUBDIRS = \
    Examples \
    libQt6OpenCV

 # where to find the sub projects - give the folders
 libQt6OpenCV.subdir = libQt6OpenCV
 Examples.subdir  = examples/test

 # what subproject depends on others
 Examples.depends = libQt6OpenCV
