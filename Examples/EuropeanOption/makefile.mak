
# makefile for EuropeanOption.cpp under Borland C++

.autodepend
.silent

!ifdef _DEBUG
!ifndef _RTLDLL
    _D = -sd
!else
    _D = -d
!endif
!else
!ifndef _RTLDLL
    _D = -s
!endif
!endif

!ifdef __MT__
    _mt = -mt
!endif

# Directories
QL_INCLUDE_DIR   = "$(QL_DIR)"
QL_LIB_DIR       = "$(QL_DIR)\lib"

# Options
CC_OPTS = -vi- -I$(QL_INCLUDE_DIR)

!ifdef _DEBUG
CC_OPTS = $(CC_OPTS) -v -D_DEBUG
!else
CC_OPTS = $(CC_OPTS) -O2 -DNDEBUG
!endif

!ifdef __MT__
    CC_OPTS = $(CC_OPTS) -tWM
!endif

!ifdef _RTLDLL
    CC_OPTS = $(CC_OPTS) -D_RTLDLL
!endif

!ifdef SAFE
CC_OPTS = $(CC_OPTS) -DQL_EXTRA_SAFETY_CHECKS
!endif

# Primary target:
EuropeanOption$(_mt)$(_D).exe: EuropeanOption.cpp
    bcc32 $(CC_OPTS) -L$(QL_LIB_DIR) \
    -o"EuropeanOption$(_mt)$(_D).obj" \
    -eEuropeanOption$(_mt)$(_D).exe EuropeanOption.cpp





# Clean up
clean::
    if exist *.obj*  del /q *.obj*
    if exist *.tds   del /q *.tds
    if exist *.exe   del /q *.exe
