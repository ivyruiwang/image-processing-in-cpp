##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=week_mt
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :="C:/Users/25812/Desktop/C++/week 4/week_mt_allprojects/amipractical"
ProjectPath            :="C:/Users/25812/Desktop/C++/week 4/week_mt_allprojects/amipractical/week_mt"
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/week_mt
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=25812
Date                   :=20/11/2024
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
OutputDirectory        :=C:/Users/25812/Desktop/C++/week 4/week_mt_allprojects/amipractical/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/usr/local/opt/gcc-14.2.0/bin/windres.exe
LinkOptions            := -lniftiio  -lznz  -lz  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)$(WorkspacePath)/nifticlib/niftilib $(IncludeSwitch)$(WorkspacePath)/nifticlib/znzlib $(IncludeSwitch)$(WorkspacePath)/bmpmini $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)$(WorkspacePath)/bin $(LibraryPathSwitch)$(WorkspacePath)/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := C:/usr/local/opt/gcc-14.2.0/bin/ar.exe -r
CXX      := C:/usr/local/opt/gcc-14.2.0/bin/g++.exe
CC       := C:/usr/local/opt/gcc-14.2.0/bin/gcc.exe
CXXFLAGS := -std=c++20  -Wno-narrowing   -gdwarf-2 -O0 -Wall $(Preprocessors)
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
Objects0=$(IntermediateDirectory)/week_mt.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/week_mt.cpp$(ObjectSuffix): week_mt.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/25812/Desktop/C++/week 4/week_mt_allprojects/amipractical/week_mt/week_mt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/week_mt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/week_mt.cpp$(PreprocessSuffix): week_mt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/week_mt.cpp$(PreprocessSuffix) week_mt.cpp

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


