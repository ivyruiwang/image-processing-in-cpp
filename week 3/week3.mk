##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=week3
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :="C:/Users/25812/Desktop/C++/week 3/AMIPractical/amipractical"
ProjectPath            :="C:/Users/25812/Desktop/C++/week 3/AMIPractical/amipractical/week3"
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/week3
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=25812
Date                   :=18/11/2024
CodeLitePath           :=C:/usr/local/opt/codelite-monthly
MakeDirCommand         :=mkdir
LinkerName             :=C:/usr/local/opt/gcc-14.2.0/bin/g++.exe
SharedObjectLinkerName :=C:/usr/local/opt/gcc-14.2.0/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=C:/Users/25812/Desktop/C++/week 3/AMIPractical/amipractical/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName).exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/usr/local/opt/gcc-14.2.0/bin/windres.exe
LinkOptions            := -lgdi32  -lniftiio  -lznz  -lzlib  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../nifticlib/niftilib $(IncludeSwitch)../nifticlib/znzlib $(IncludeSwitch)../bmpmini $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := C:/usr/local/opt/gcc-14.2.0/bin/ar.exe -r
CXX      := C:/usr/local/opt/gcc-14.2.0/bin/g++.exe
CC       := C:/usr/local/opt/gcc-14.2.0/bin/gcc.exe
CXXFLAGS := -std=c++20 -gdwarf-2 -O0 -Wall $(Preprocessors)
CFLAGS   :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/usr/local/opt/gcc-14.2.0/bin/as.exe


##
## User defined environment variables
##
UsrLocal:=C:\usr\local
OptSoftware:=$(UsrLocal)/opt
CodeLiteDir:=$(OptSoftware)\codelite-monthly
WXWIN:=$(UsrLocal)
WXCFG:=gcc_x64_dll/mswu
GCCVER:=14.2.0
PATH:=$(PATH);$(OptSoftware)/gcc-$(GCCVER)/bin;$(UsrLocal)/lib/gcc_x64_dll;$(UsrLocal)/lib;$(UsrLocal)/bin;
Objects0=$(IntermediateDirectory)/week3.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@if not exist "$(OutputDirectory)" $(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/week3.cpp$(ObjectSuffix): week3.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/25812/Desktop/C++/week 3/AMIPractical/amipractical/week3/week3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/week3.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/week3.cpp$(PreprocessSuffix): week3.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/week3.cpp$(PreprocessSuffix) week3.cpp

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


