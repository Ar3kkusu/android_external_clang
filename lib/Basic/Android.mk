# Only use this on the device or emulator.
ifneq ($(TARGET_ARCH),arm)

LOCAL_PATH:= $(call my-dir)

# For the host only
# =====================================================
include $(CLEAR_VARS)
include $(CLEAR_TBLGEN_VARS)

TBLGEN_TABLES :=    \
	DiagnosticGroups.inc	\
	DiagnosticASTKinds.inc	\
	DiagnosticLexKinds.inc	\
	DiagnosticSemaKinds.inc	\
    DiagnosticCommonKinds.inc	\
	DiagnosticDriverKinds.inc	\
	DiagnosticParseKinds.inc	\
	DiagnosticAnalysisKinds.inc	\
	DiagnosticFrontendKinds.inc

clang_basic_SRC_FILES :=	\
	Builtins.cpp	\
	ConvertUTF.c	\
	Diagnostic.cpp	\
	FileManager.cpp	\
	IdentifierTable.cpp	\
	SourceLocation.cpp	\
	SourceManager.cpp	\
	TargetInfo.cpp	\
	Targets.cpp	\
	TokenKinds.cpp	\
	Version.cpp

LOCAL_SRC_FILES := $(clang_basic_SRC_FILES)

LOCAL_MODULE:= libclangBasic

include $(CLANG_HOST_BUILD_MK)
include $(CLANG_TBLGEN_RULES_MK)
include $(BUILD_HOST_STATIC_LIBRARY)

endif