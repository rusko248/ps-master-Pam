RuskoAdventures
~~~~~~~~~~~~~~
CREATED BY Pamela Martinez, Aaron Damashek, Alex Tamplin, and Potcharapol Suteparuk 


1. Installing on Mac with Xcode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

1.  Download and install OpenMesh.  OpenMesh can be found at openmesh.org
2.  Open the Xcode Project.  This will be in the folder "Rusko_adventures" and is called "Rusko_adventures.xcodeproj"
3.  To link OpenMesh with Xcode:  Go to the project on the navigator and click the "Build Phases" tab.  Add the OpenMesh library to the "Link Binary with Libraries" phase.  To do this click "add other", and you should be able to find the /lib folder wherever it was installed.  Now go to "Build Settings" tab, scroll through the "Search Paths" section and add the include header files for OpenMesh to the "Header Search Paths" Section.  Add the /lib or wherever the .dylib files are to "Library Search Paths" section.
4.  FMOD music library is used in the project.  The necessary library and dll files should already be bundled with the project in the folder "FMOD". The libfmod.dylib should already be included in the packaged Xcode project.  On Xcode go to the top bar menu and select Product/Scheme/Edit Scheme…  Then go to the "Arguments" tab.  Under "Environment Variables" click the "+" and add under name "DYLD_LIBRARY_PATH" and under value add "../FMOD/lib".  If the library is not working, you can download the API from their website and do a similar linking as in 3.



2. Installing on PC
~~~~~~~~~~~~~~~~~~~

1.  Download and install OpenMesh (for PC).  Please visit openmesh.org.
2.  To link with OpenMesh in Visual Studio, find the path to your installed OpenMesh.  Add the path to its include folder to your Additional Include Directories under the C/C++ tab in the project properties page.  Also under the Linker tab, add the path to OpenMesh/lib to your Additional Library.  Include all the library files in the OpenMesh/lib folder under Linker/Input/Additional Dependencies in your solution property page.  Finally, add the dll files either to your solution directory, or add them to your system folder (or add the path to system PATH variable).
3.  FMOD music library is used in this project.  You can find the necessary library and dll files in the folder.  (might need to relocate them if you want to change the path of your project).  If this is not working, you can download the API from their website.  Then do the same linking as in 2.
