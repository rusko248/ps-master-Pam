RuskoAdventures
~~~~~~~~~~~~~~
CREATED BY Pamela Martinez, Aaron Damashek, Alex Tamplin, and Potcharapol Suteparuk 


1. Installing on Mac with Xcode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

1.  Download and install OpenMesh.  OpenMesh can be found at openmesh.org
2.  Open the Xcode Project.  This will be in the folder "Rusko_adventures" and is called "Rusko_adventures.xcodeproj"
3.  To link OpenMesh with Xcode:  Go to the project on the navigator and click the "Build Phases" tab.  Add the OpenMesh library to the "Link Binary with Libraries" phase.  To do this click "add other", and you should be able to find the /lib folder wherever it was installed.  Now go to "Build Settings" tab, scroll through the "Search Paths" section and add the include header files for OpenMesh to the "Header Search Paths" Section.  Add the /lib or wherever the .dylib files are to "Library Search Paths" section.
4.  To include the fmod music library.  The libfmod.dylib should already be included in the packaged project.  On Xcode go to the top bar menu and select Product/Scheme/Edit Scheme…  Then go to the "Arguments" tab.  Under "Environment Variables" click the "+" and add under name "DYLD_LIBRARY_PATH" and under value add "../FMOD/lib".



2. Installing on PC
~~~~~~~~~~~~~~~~~~~
