##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=vector_week2
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/Users/25812/Desktop/C++/week2_workspace20221106/week2_workspace
ProjectPath            :=C:/Users/25812/Desktop/C++/week2_workspace20221106/week2_workspace/vector_week2
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/vector_week2
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=25812
Date                   :=07/11/2024
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
OutputDirectory        :=C:/Users/25812/Desktop/C++/week2_workspace20221106/week2_workspace/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/usr/local/opt/gcc-14.2.0/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
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
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
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
Objects0=$(IntermediateDirectory)/vector_week2.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/vector_week2.cpp$(ObjectSuffix): vector_week2.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/25812/Desktop/C++/week2_workspace20221106/week2_workspace/vector_week2/vector_week2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vector_week2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vector_week2.cpp$(PreprocessSuffix): vector_week2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vector_week2.cpp$(PreprocessSuffix) vector_week2.cpp

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


